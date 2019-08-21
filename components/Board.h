#ifndef FINAL_PROJECT_BOARD_H
#define FINAL_PROJECT_BOARD_H

#include <stdbool.h>

#define CLEAR (0)
#define MIN_INDEX (1)

typedef struct {
    int val;
    bool fixed;
    bool erroneous;
} BoardCell;

typedef struct {
    int dim;
    int num_of_rows_in_block;
    int num_of_columns_in_block;
    BoardCell ***cells_arr;
    bool solved;
    int _errors_count;
    bool erroneous;
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


/* Board manipulation functions */

void set_cell_value(Board *board, int row, int column, int value);

bool fix_cell(Board *board, int row, int column);

#endif
