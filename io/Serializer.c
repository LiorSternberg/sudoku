#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Serializer.h"
#include "../UserHandler.h"

#define SUCCESS (0)
#define FAILURE (1)

#define INT_BASE (10)

#define FIXED_MARK "."
#define EMPTY ""

#define CANT_OPEN_FILE_ERROR "Error: The given file could not be opened."
#define CANT_CLOSE_FILE_ERROR "Error: The file could not be closed."
#define CANT_PARSE_DIMENSIONS_ERROR "Error: Could not parse the board dimensions, please make sure the file format is correct."
#define CANT_PARSE_VALUE_ERROR "Error: Could not parse values, please make sure the file format " \
                               "is correct and contains the correct number of values."
#define CLEAR_FIXED_ERROR "Error: An empty cell cannot be fixed, please make sure the file format is correct."
#define CONFLICTING_FIXED_ERROR "Error: Found conflicting fixed cells, please make sure the file format is correct."
#define LARGE_VALUE_ERROR "Error: Found a value that is too large for the given board dimensions, please make " \
                          "sure the file format is correct."
#define TOO_MANY_VALUES_ERROR "Error: Too many values found, please make sure the file format is correct " \
                              "and contains the correct number of values."
#define ILLEGAL_BOARD_SIZE_ERROR "Error: Board size is not legal."
#define CANT_WRITE_ERROR "Error: Writing to the file failed."

#define MAX_ERROR_MESSAGE_LEN 1024
#define MAX_VALUE_LEN 5
#define MAX_BOARD_SIZE 99
#define MIN_BOARD_SIZE 1


/* Parse a cell (value and fixed indicator) from a given token.
 * Returns SUCCESS if the cell data was parsed and FAILURE if an
 * error occurred. */
int parse_value(char *token, int *p_int, bool *fixed) {
    int num;
    char *end_p;
    bool success;

    errno = 0;
    num = strtol(token, &end_p, INT_BASE);

    /* check if token is a valid positive integer */
    success = num >= 0 && token != end_p && errno == 0;

    if (success && *end_p == '\0') {
        *p_int = num;
        *fixed = false;

    } else if (success && strcmp(end_p, FIXED_MARK) == 0) {
        *p_int = num;
        *fixed = true;

    } else {
        return FAILURE;
    }
    return SUCCESS;
}

/* Read the next token from the file (ignore whitespace).
 * Returns SUCCESS if one token was read and FAILURE if an
 * error occurred (token too long, or EOF for example). */
int read_next(FILE *file, char *token) {
    /* Assert one value was successfully parsed, and that the char before-last is null
     * (the last one is always null, but the one before might differ if the value is too long)*/
    if (fscanf(file, "%4s", token) != 1 || token[MAX_VALUE_LEN - 2] != '\0') {
        return FAILURE;
    }

    return SUCCESS;
}

/* Read and parse the dimensions of the board (#rows & #columns).
 * Returns SUCCESS if the dimensions were parsed and found to be of legal format
 * (i.e. not fixed for example), and FAILURE if an error occurred. */
int read_dimensions(FILE *file, int *rows, int *columns, Error *error) {
    char m[MAX_VALUE_LEN] = {0}, n[MAX_VALUE_LEN] = {0};
    bool m_fixed, n_fixed;

    /* Read dimension tokens */
    if (read_next(file, m) == FAILURE || read_next(file, n) == FAILURE) {
        set_error(error, CANT_PARSE_DIMENSIONS_ERROR, execution_failure);
        return FAILURE;
    }

    /* Parse dimensions */
    if (parse_value(m, rows, &m_fixed) == FAILURE || parse_value(n, columns, &n_fixed) == FAILURE) {
        set_error(error, CANT_PARSE_DIMENSIONS_ERROR, execution_failure);
        return FAILURE;
    }

    /* Assert dimensions are not marked as fixed (bad format) */
    if (m_fixed == true || n_fixed == true) {
        set_error(error, CANT_PARSE_DIMENSIONS_ERROR, execution_failure);
        return FAILURE;
    }

    return SUCCESS;
}

/* Read and parse a cell (value and fixed indicator), then set it to the board.
 * Returns SUCCESS if the cell data was parsed and FAILURE if an error occurred. */
int read_cell_data(FILE *file, Board *board, int row, int column, Error *error, GameMode mode) {
    char cell_token[MAX_VALUE_LEN] = {0};
    int value;
    bool fixed;

    if (read_next(file, cell_token) == FAILURE || parse_value(cell_token, &value, &fixed) == FAILURE) {
        set_error(error, CANT_PARSE_VALUE_ERROR, execution_failure);
        return FAILURE;
    }

    /* Assert value is in the allowed range for board size */
    if (value > board->dim) {
        set_error(error, LARGE_VALUE_ERROR, execution_failure);
        return FAILURE;
    }

    set_cell_value(board, row, column, value);
    if (fixed == true && mode == solve_mode) {

        /* Assert empty cells are not marked as fixed */
        if (value == CLEAR) {
            set_error(error, CLEAR_FIXED_ERROR, execution_failure);
            return FAILURE;
        }

        /* Assert cell is not conflicting with another fixed neighbor */
        if (fix_cell(board, row, column) == false) {
            set_error(error, CONFLICTING_FIXED_ERROR, execution_failure);
            return FAILURE;
        }
    }
    return SUCCESS;
}

Board* load_from_file(char *path, Error *error, GameMode mode) {
    FILE *file;
    Board *board;
    int rows, columns, i, j;
    char token[MAX_VALUE_LEN] = {0};

    /* Open the file */
    if ((file = fopen(path, "r")) == NULL) {
        set_error(error, CANT_OPEN_FILE_ERROR, execution_failure);
        return NULL;
    }

    /* Read the board dimensions */
    if (read_dimensions(file, &rows, &columns, error) == FAILURE) {
        return NULL;
    }

    if (rows * columns > MAX_BOARD_SIZE || rows * columns < MIN_BOARD_SIZE) {
        set_error(error, ILLEGAL_BOARD_SIZE_ERROR, execution_failure);
        return NULL;
    }

    /* Read the board data */
    board = create_board(rows, columns);
    for (i=0; i < board->dim; i++) {
        for (j=0; j < board->dim; j++) {
            if (read_cell_data(file, board, i, j, error, mode) == FAILURE) {
                destroy_board(board);
                return NULL;
            }
        }
    }

    /* Assert there isn't another token in the file (i.e. file contains correct number of values) */
    if (read_next(file, token) == SUCCESS) {
        set_error(error, TOO_MANY_VALUES_ERROR, execution_failure);
        destroy_board(board);
        return NULL;
    }

    /* Close file */
    if (fclose(file) == EOF) {
        set_error(error, CANT_CLOSE_FILE_ERROR, execution_failure);
        destroy_board(board);
        return NULL;
    }

    return board;
}


void save_to_file(Game *game, char *path, Error *error) {
    FILE *file;
    int i, j;
    char *format, *fixed;

    /* Open the file */
    if ((file = fopen(path, "w")) == NULL) {
        set_error(error, CANT_OPEN_FILE_ERROR, execution_failure);
        return;
    }

    /* Write dimensions */
    if (fprintf(file, "%d %d\n", game->board->num_of_rows_in_block, game->board->num_of_columns_in_block) < 0) {
        set_error(error, CANT_WRITE_ERROR, execution_failure);
        return;
    }

    /* Write values */
    for (i=0; i < game->board->dim; i++) {
        for (j=0; j < game->board->dim; j++) {
            if (j == (game->board->dim - 1)) {
                format = "%d%s\n";
            } else {
                format = "%d%s ";
            }

            fixed = (game->mode == edit_mode || is_cell_fixed(game->board, i, j)) ? FIXED_MARK : EMPTY;

            if (fprintf(file, format, get_cell_value(game->board, i, j), fixed) < 0) {
                set_error(error, CANT_WRITE_ERROR, execution_failure);
                return;
            }
        }
    }

    /* Close file */
    if (fclose(file) == EOF) {
        set_error(error, CANT_CLOSE_FILE_ERROR, execution_failure);
    }
}
