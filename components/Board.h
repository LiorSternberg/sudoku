#ifndef FINAL_PROJECT_BOARD_H
#define FINAL_PROJECT_BOARD_H

#include <stdbool.h>
#include "List.h"

#define CLEAR (0)
#define MIN_INDEX (1)
#define ERROR_VALUE (-1)

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

bool is_cell_fixed(const Board *board, int row, int column);

bool is_cell_empty(const Board *board, int row, int column);

int get_cell_value(const Board *board, int row, int column);

/* Returns true if the board is erroneous, meaning the board contains cell with illegal value */
bool is_board_erroneous(const Board *board);

/* Returns true if the (row, column) cell contains illegal value */
bool is_cell_erroneous(const Board *board, int row, int column);

/* Fill the marks array according to the values of the cell's neighbors (for
 * example, if there exists a neighbor with value 3, then cell 2 (value-1) will
 * be set to true. Additionally, if there's no neighbor with value 4, then cell
 * 3 will be set to false). */
void mark_neighboring_values(Board *board, bool *marks, int row, int column);

/* If the given cell has only one legal value, returns it. Otherwise, returns ERROR_VALUE. */
int get_obvious_value(Board *board, bool *marks, int row, int column);



/* Board manipulation functions */

void set_cell_value(Board *board, int row, int column, int value);

bool fix_cell(Board *board, int row, int column);

/* Returns a copy of the given board (deep copy) */
Board* get_board_copy(const Board *board);

/* Sets all non-empty cells in the given board to fixed. Returns true on success, and false on failure. */
bool fix_non_empty_board_cells(Board *board);

#endif
