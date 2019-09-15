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

#define HEADLINE1 \
"         _____           _       _           ___  ___          _                     \n" \
"        /  ___|         | |     | |          |  \\/  |         | |                    \n" \
"        \\ `--. _   _  __| | ___ | | ___   _  | .  . | __ _  __| |_ __   ___  ___ ___ \n" \
"         `--. \\ | | |/ _` |/ _ \\| |/ / | | | | |\\/| |/ _` |/ _` | '_ \\ / _ \\/ __/ __|\n"

#define HEADLINE2 \
"        /\\__/ / |_| | (_| | (_) |   <| |_| | | |  | | (_| | (_| | | | |  __/\\__ \\__ \\\n" \
"        \\____/ \\__,_|\\__,_|\\___/|_|\\_\\\\__,_| \\_|  |_/\\__,_|\\__,_|_| |_|\\___||___/___/\n" \
"                                                                                     \n\n" \


/* Generate a separation row for printing between blocks of the board. */
char* generate_row_sep(Board *board) {
    int len = (4 * board->dim + board->num_of_rows_in_block + 1);
    char *str = malloc((len + 2) * sizeof(char));
    validate_memory_allocation("generate_row_sep", str);

    memset(str, '-', (len * sizeof(char)));
    str[len] = '\0';

    return str;
}

/* Prints the cell value in the given coordinates according to it's state. */
void print_cell(Board *board, int row, int column, bool mark_errors) {
    int value = get_cell_value(board, row, column);

    if (value == CLEAR) {
        printf(EMPTY_CELL_FORMAT);
    } else if (is_cell_fixed(board, row, column)) {
        printf(CELL_FORMAT, value, FIXED);
    } else if (is_cell_erroneous(board, row, column) && mark_errors) {
        printf(CELL_FORMAT, value, ERRONEOUS);
    } else {
        printf(CELL_FORMAT, value, NO_MARK);
    }
}

/* Prints a row of cells. */
void print_row(Board *board, int row, bool mark_errors) {
    int col;

    for (col=0; col < board->dim; col++) {
        if ((col % board->num_of_columns_in_block) == 0) {
            printf(COL_SEP);
        }
        print_cell(board, row, col, mark_errors);
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
    free(sep);
}

void announce_game_start() {
    printf(HEADLINE1);
    printf(HEADLINE2);
    printf("Welcome! Let the Games Begin!\n");
}

void announce_game_won() {
    printf("\n*~*~*~*~* Woo Hoo! You did it! *~*~*~*~* \nPlease load another game or exit.\n");
}

void announce_game_erroneous() {
    printf("Hmm this isn't quite right. You have some errors you need to fix in order to complete the game.\n");
}

void announce_game_solvable() {
    printf("The current state of the puzzle is indeed solvable.\n");
}

void announce_game_not_solvable() {
    printf("Unfortunately the current state of the puzzle is not solvable.\n");
}

void announce_hint(int hint) {
    printf("Your hint is: %d. Use it wisely!\n", hint);
}

void announce_num_of_solutions(int num_of_solutions) {
    printf("Number of solutions for the current state: %d\n", num_of_solutions);
}

void announce_changes_made() {
    printf("The following changes were made: \n-------------------------------\n");
}

void announce_no_changes_made() {
    printf("No changes were made.\n");
}

void print_change(Change *change, bool reverted) {
    int from_value, to_value;

    if (reverted) {
        from_value = change->value;
        to_value = change->prev_value;
    } else {
        to_value = change->value;
        from_value = change->prev_value;
    }
    printf(" @ Cell (%d, %d): [%d] --> [%d]\n", change->column, change->row, from_value, to_value);
}

void announce_guesses_list() {
    printf("Guess values and their scores:\n"
           "-----------------------------\n");
}

void print_guess(int value, double score) {
    printf(" @ Value %d: score %.2f \n", value, score);
}

void print_autofill(int row, int column, int value) {
    printf(" @ Cell (%d, %d) auto-filled: [%d] \n", column + 1, row + 1, value);
}

void announce_error(Error *error) {
    printf("%s\n", error->message);
}

void announce_exit() {
    printf("Exiting...\n");
}
