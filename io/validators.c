#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "validators.h"
#include "../components/Game.h"
#include "Command.h"

#define FILE_DOESNT_EXIST_ERROR "Error: The given file doesn't exist!"
#define FILE_NOT_READABLE_ERROR "Error: The given file cannot be read (no permission)."
#define FILE_NOT_WRITABLE_ERROR "Error: The given file cannot be written to (no permission)."
#define FIXED_ERROR "Error: cell is fixed."
#define NOT_EMPTY_ERROR "Error: cell is not empty."
#define BOARD_ERRONEOUS_ERROR "Error: this command is not available when the board is erroneous."
#define NO_UNDO_MOVES_ERROR "Error: there are no moves available to undo."
#define NO_REDO_MOVES_ERROR "Error: there are no moves available to redo."

#define MAX_ERROR_MESSAGE_LEN 1024

#define INVALID_COMMAND_FOR_MODE_ERROR "Error: command is not available in the current mode. Only available in: "
#define ALL_MODES "Init, Edit, Solve."
#define SOLVE_AND_EDIT_MODES "Solve, Edit."
#define SOLVE_MODE "Solve."
#define EDIT_MODE "Edit."

#define ARG_OUT_OF_RANGE_ERROR "Error: argument <%s> is not valid. "
#define BOOL_RANGE "Must be either 0 or 1."
#define INT_RANGE "Must be a valid integer between %d and %d."
#define DOUBLE_RANGE "Must be a valid floating point number between %.1f and %.1f."


/* Generic assertions */

/* Assert that the command is available in the current game mode. */
void assert_game_mode(Command *command, GameMode mode) {
    char *error_message;
    char *modes[8] = {0};

    modes[init_mode + solve_mode + edit_mode] = ALL_MODES;
    modes[solve_mode + edit_mode] = SOLVE_AND_EDIT_MODES;
    modes[solve_mode] = SOLVE_MODE;
    modes[edit_mode] = EDIT_MODE;

    /* bitwise 'and' to check mode compatibility */
    if ((command->modes & mode) == 0) {
        error_message = calloc(MAX_ERROR_MESSAGE_LEN, sizeof(char));
        strcat(strcpy(error_message, INVALID_COMMAND_FOR_MODE_ERROR), modes[command->modes]);
        invalidate(command, error_message, invalid_command_for_mode);
    }
}

/* Assert that the given file exists and is readable. */
void assert_file_readable(Command *command, char *path) {
    if(access(path, F_OK) == -1) { /* file doesn't exist */
        invalidate(command, FILE_DOESNT_EXIST_ERROR, execution_failure);
    } else if (access(path, R_OK) == -1) { /* file doesn't have read permissions */
        invalidate(command, FILE_NOT_READABLE_ERROR, execution_failure);
    }
}

/* Assert that the given file exists and is writable. */
void assert_file_writable(Command *command, char *path) {
    if (access(path, W_OK) == -1) { /* file doesn't have write permissions */
        invalidate(command, FILE_NOT_WRITABLE_ERROR, execution_failure);
    }
}

/* Assert that an int argument was parsed successfully, and contains a legal boolean value (0/1). */
void assert_bool_arg(Command *command, char *arg_name, int value) {
    char *error_message, error_format[MAX_ERROR_MESSAGE_LEN] = {0};
    int res;

    if (value == 0 || value == 1) {
        return; /* valid */
    }

    error_message = calloc(MAX_ERROR_MESSAGE_LEN, sizeof(char));
    strcat(strcpy(error_format, ARG_OUT_OF_RANGE_ERROR), BOOL_RANGE);
    res = sprintf(error_message, error_format, arg_name);
    invalidate(command, error_message, invalid_arg_range);
}

/* Assert that an int argument was parsed successfully, and contains a legal value in the allowed range. */
void assert_int_arg_in_range(Command *command, char *arg_name, int value, int min, int max) {
    char *error_message, error_format[MAX_ERROR_MESSAGE_LEN] = {0};
    int res;

    if (value >= min && value <= max) {
        return; /* valid */
    }

    error_message = calloc(MAX_ERROR_MESSAGE_LEN, sizeof(char));
    strcat(strcpy(error_format, ARG_OUT_OF_RANGE_ERROR), INT_RANGE);
    res = sprintf(error_message, error_format, arg_name, min, max);
    invalidate(command, error_message, invalid_arg_range);
}

/* Assert that a double argument was parsed successfully, and contains a legal value in the allowed range. */
void assert_double_arg_in_range(Command *command, char *arg_name, double value, double min, double max) {
    char *error_message, error_format[MAX_ERROR_MESSAGE_LEN] = {0};
    int res;

    if (value >= min && value <= max) {
        return; /* valid */
    }

    error_message = calloc(MAX_ERROR_MESSAGE_LEN, sizeof(char));
    strcat(strcpy(error_format, ARG_OUT_OF_RANGE_ERROR), DOUBLE_RANGE);
    res = sprintf(error_message, error_format, arg_name, min, max);
    invalidate(command, error_message, invalid_arg_range);
}

/* Assert that the board is not currently erroneous. */
void assert_board_not_erroneous(Command *command, Board *board) {
    if (board != NULL && board->erroneous == true) {
        invalidate(command, BOARD_ERRONEOUS_ERROR, invalid_state);
    }
}

/* Assert that the given cell is not fixed. */
void assert_cell_not_fixed(Command *command, Board *board, int row, int column) {
    if (board != NULL && is_cell_fixed(board, row, column)) {
        invalidate(command, FIXED_ERROR, invalid_state);
    }
}

/* Assert that the given cell is empty. */
void assert_cell_empty(Command *command, Board *board, int row, int column) {
    if (board != NULL && !is_cell_empty(board, row, column)) {
        invalidate(command, NOT_EMPTY_ERROR, invalid_state);
    }
}

/* Validators */

void base_validator(Command *command, Game *game) {
    assert_game_mode(command, game->mode);
}


/* Command-specific validators
 * Note: for validation of errors at the same level, the order of validations
 * within the function IS IMPORTANT and should not be changed. */

void solve_validator(Command *command, Game *game) {
    if (command->data.solve == NULL) {
        return;
    }

    assert_file_readable(command, command->data.solve->path);
}

void edit_validator(Command *command, Game *game) {
    if (command->data.edit == NULL) {
        return;
    }

    if (command->data.edit->from_file == true) {
        assert_file_readable(command, command->data.edit->path);
    }
}

void mark_errors_validator(Command *command, Game *game) {
    if (command->data.mark_errors == NULL) {
        return;
    }

    assert_bool_arg(command, "set", command->data.mark_errors->setting);
}

void set_validator(Command *command, Game *game) {
    if (command->data.set == NULL || game->board == NULL) {
        return;
    }

    /* Check argument range by order of entry */
    assert_int_arg_in_range(command, "column", command->data.set->column, MIN_INDEX, game->board->dim);
    assert_int_arg_in_range(command, "row", command->data.set->row, MIN_INDEX, game->board->dim);
    assert_int_arg_in_range(command, "value", command->data.set->value, CLEAR, game->board->dim);

    if (game->mode == solve_mode) {
        assert_cell_not_fixed(command, game->board, command->data.set->row, command->data.set->column);
    }
}

void validate_validator(Command *command, Game *game) {
    assert_board_not_erroneous(command, game->board);
}

void guess_validator(Command *command, Game *game) {
    if (command->data.guess == NULL) {
        return;
    }

    assert_double_arg_in_range(command, "threshold", command->data.guess->threshold, MIN_THRESHOLD, MAX_THRESHOLD);
    assert_board_not_erroneous(command, game->board);
}

void generate_validator(Command *command, Game *game) {
    if (command->data.guess == NULL || game->board == NULL) {
        return;
    }

    /* Check argument range by order of entry */
    assert_int_arg_in_range(command, "#cells to fill", command->data.generate->num_to_fill,
                            MIN_CELLS, game->board->empty_count);
    assert_int_arg_in_range(command, "#cells to leave", command->data.generate->num_to_leave,
                            MIN_CELLS, game->board->dim * game->board->dim);
}

void undo_validator(Command *command, Game *game) {
    if (has_prev(game->states->moves) == false) {
        invalidate(command, NO_UNDO_MOVES_ERROR, execution_failure);
    }
}

void redo_validator(Command *command, Game *game) {
    if (has_next(game->states->moves) == false) {
        invalidate(command, NO_REDO_MOVES_ERROR, execution_failure);
    }
}

void save_validator(Command *command, Game *game) {
    if (command->data.save == NULL) {
        return;
    }

    assert_file_writable(command, command->data.solve->path);
    if (game->mode == edit_mode){
        assert_board_not_erroneous(command, game->board);
    }
}

void hint_base_validator(Command *command, Board *board, int row, int column) {
    /* Check argument range by order of entry */
    assert_int_arg_in_range(command, "column", column, MIN_INDEX, board->dim);
    assert_int_arg_in_range(command, "row", row, MIN_INDEX, board->dim);

    /* Check state related errors by the required order */
    assert_board_not_erroneous(command, board);
    assert_cell_not_fixed(command, board, row, column);
    assert_cell_empty(command, board, row, column);
}

void hint_validator(Command *command, Game *game) {
    if (command->data.hint == NULL || game->board == NULL) {
        return;
    }

    hint_base_validator(command, game->board, command->data.hint->row, command->data.hint->column);
}

void guess_hint_validator(Command *command, Game *game) {
    if (command->data.guess_hint == NULL || game->board == NULL) {
        return;
    }

    hint_base_validator(command, game->board, command->data.guess_hint->row, command->data.guess_hint->column);
}

void num_solutions_validator(Command *command, Game *game) {
    assert_board_not_erroneous(command, game->board);
}

void autofill_validator(Command *command, Game *game) {
    assert_board_not_erroneous(command, game->board);
}


/* main validation function */

/* Validates the command first with the basic validator that's relevant
 * for all command types, and then using the command-specific validator
 * if one exists for that command type. */
void validate_command(Command *command, Game *game) {
    base_validator(command, game);
    if (command->_validate != NULL) {
        command->_validate(command, game);
    }
}

