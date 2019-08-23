#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Printer.h"
#include "../MemoryError.h"

#define COL_SEP "|"
#define EMPTY_CELL_FORMAT "    "
#define CELL_FORMAT " %2d%s"
#define FIXED "."
#define ERRONEOUS "*"
#define NO_MARK " "

char* generate_row_sep(Board *board) {
    int len = (4 * board->dim + board->num_of_rows_in_block + 1);
    char *str = malloc((len + 2) * sizeof(char));
    validate_memory_allocation("generate_row_sep", str);

    memset(str, '-', (len * sizeof(char)));
    str[len] = '\0';

    return str;
}

void print_cell(BoardCell *cell, bool mark_errors) {
    if (cell->val == CLEAR) {
        printf(EMPTY_CELL_FORMAT);
    } else if (cell->fixed) {
        printf(CELL_FORMAT, cell->val, FIXED);
    } else if (cell->erroneous && mark_errors) {
        printf(CELL_FORMAT, cell->val, ERRONEOUS);
    } else {
        printf(CELL_FORMAT, cell->val, NO_MARK);
    }
}

void print_row(Board *board, int row, bool mark_errors) {
    int col;

    for (col=0; col < board->dim; col++) {
        if ((col % board->num_of_columns_in_block) == 0) {
            printf(COL_SEP);
        }
        print_cell(board->cells_arr[row][col], mark_errors);
    }
    printf("|\n");
}

void print(Game *game) {
    int row;
    char *sep = generate_row_sep(game->board);
    bool mark_errors = game->mark_errors || game->mode == edit_mode;

    printf("\n");
    for (row=0; row < game->board->dim; row++) {
        if ((row % game->board->num_of_rows_in_block) == 0) {
            printf("%s\n", sep);
        }
        print_row(game->board, row, mark_errors);
    }
    printf("%s\n", sep);
}
