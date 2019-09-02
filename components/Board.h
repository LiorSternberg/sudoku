#ifndef FINAL_PROJECT_BOARD_H
#define FINAL_PROJECT_BOARD_H

#include <stdbool.h>
#include "List.h"

#define CLEAR (0)
#define MIN_INDEX (1)

typedef struct BoardCell BoardCell;

typedef struct {
    int dim;
    int num_of_rows_in_block;
    int num_of_columns_in_block;
    BoardCell ***_cells_arr;
    bool solved;
    int errors_count;
    int empty_count;
} Board;


/* Initialize the given board:
 * set the dimension fields.
 * set the cells values to CLEAR, which means that the board is empty.
 * */
Board* create_board(int rows_in_block, int columns_in_block);

void destroy_board(Board *board);


/* Query functions */

bool is_cell_fixed(Board *board, int row, int column);

bool is_cell_empty(Board *board, int row, int column);

int get_cell_value(Board *board, int row, int column);

/* Returns true if the board is erroneous, meaning the board contains cell with illegal value */
bool is_board_erroneous(Board *board);

/* Returns true if the (row, column) cell contains illegal value */
bool is_cell_erroneous(Board *board, int row, int column);


/* Board manipulation functions */

void set_cell_value(Board *board, int row, int column, int value);

bool fix_cell(Board *board, int row, int column);

/* Returns a copy of the given board (deep copy) */
Board* get_board_copy(Board *board);

/* Sets all non-empty cells in the given board to fixed. Returns true on success, and false on failure. */
bool fix_non_empty_board_cells(Board *board);

#endif
