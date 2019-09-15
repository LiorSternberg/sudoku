#ifndef FINAL_PROJECT_BOARD_H
#define FINAL_PROJECT_BOARD_H

#include <stdbool.h>
#include "List.h"

#define CLEAR (0)
#define MIN_INDEX (1)
#define ERROR_VALUE (-1)

/** Board:
 *
 *  The component is used to manage the puzzle's board.
 *  It contains the board's cells, and general information about the state of
 *  the board, such as the number of empty and erroneous cells, the board's
 *  dimensions, and whether or not it is solved.
 */

/* BoardCells are not to be used directly by external modules. See query and
 * board manipulation functions for further usage information. */
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


/**
 * Creates a new empty board of the given dimensions, and initializes the
 * various fields.
 * @param rows_in_block: the number of rows in a single block.
 * @param columns_in_block: the number of columns in a single block.
 * @return: the new board that was created.
 */
Board* create_board(int rows_in_block, int columns_in_block);

/**
 * Destroys the board (frees all related memory).
 * @param board: the board to destroy.
 */
void destroy_board(Board *board);


/* Query functions */

/**
 * Checks if the cell at the given coordinates (row and column) is fixed.
 * @param board: the board to check.
 * @param row: the index of the cell's row (zero-based).
 * @param column: the index of the cell's column (zero-based).
 * @return: true if the cell is fixed, and false otherwise.
 */
bool is_cell_fixed(const Board *board, int row, int column);

/**
 * Checks if the cell at the given coordinates (row and column) is empty.
 * @param board: the board to check.
 * @param row: the index of the cell's row (zero-based).
 * @param column: the index of the cell's column (zero-based).
 * @return: true if the cell is empty, and false otherwise.
 */
bool is_cell_empty(const Board *board, int row, int column);

/**
 * Gets the value of the cell at the given coordinates (row and column).
 * @param board: the board to check.
 * @param row: the index of the cell's row (zero-based).
 * @param column: the index of the cell's column (zero-based).
 * @return: the value of the cell (1-based), or CLEAR if it's empty.
 */
int get_cell_value(const Board *board, int row, int column);

/**
 * Checks if the board is erroneous (i.e. the board contains a cell with an
 * illegal value).
 * @param board: the board to check.
 * @return: true if the board is erroneous, and false otherwise.
 */
bool is_board_erroneous(const Board *board);

/**
 * Checks if the the cell at the given coordinates (row and column) is
 * erroneous (i.e. it's value conflicts with a neighboring cell's value).
 * @param board: the board to check.
 * @param row: the index of the cell's row (zero-based).
 * @param column: the index of the cell's column (zero-based).
 * @return: true if the cell is erroneous, and false otherwise.
 */
bool is_cell_erroneous(const Board *board, int row, int column);

/**
 * Fill the marks array according to the values of the cell's neighbors (for
 * example, if there exists a neighbor with value 3, then cell 2 (value-1) will
 * be set to true. Additionally, if there's no neighbor with value 4, then cell
 * 3 will be set to false).
 * @param board: the board to get the cells data from.
 * @param marks: an array of size board.dim to be filled according to the
 * neighbors' values (true means there is a neighbor with that value, and false
 * means there isn't). Note the indices are shifted by 1 as explained above.
 * @param row: the index of the cell's row (zero-based).
 * @param column: the index of the cell's column (zero-based).
 */
void mark_neighboring_values(Board *board, bool *marks, int row, int column);

/**
 * If the given cell has only one legal value, returns it. Otherwise, returns ERROR_VALUE.
 * @param board: the board to get the cells data from.
 * @param marks: an array of size board.dim to be filled according to the
 * neighbors' values, and used to determine the legal values for the given cell.
 * @param row: the index of the cell's row (zero-based).
 * @param column: the index of the cell's column (zero-based).
 * @return: the only legal value if one exists, and ERROR_VALUE otherwise.
 */
int get_obvious_value(Board *board, bool *marks, int row, int column);



/* Board manipulation functions */

/**
 * Sets the value of the cell at the given coordinates (row and column).
 * @param board: the board to update.
 * @param row: the index of the cell's row (zero-based).
 * @param column: the index of the cell's column (zero-based).
 * @param value: the value to set for the cell.
 */
void set_cell_value(Board *board, int row, int column, int value);

/**
 * Fix the cell at the given coordinates (row and column).
 * @param board: the board to update.
 * @param row: the index of the cell's row (zero-based).
 * @param column: the index of the cell's column (zero-based).
 * @return
 */
bool fix_cell(Board *board, int row, int column);

/**
 * Returns a copy of the given board (deep copy)
 * @param board: the board to copy.
 * @return: the copy of the given board.
 */
Board* get_board_copy(const Board *board);

/**
 * Sets all non-empty cells in the given board to fixed. Returns
 * @param board: the board to update.
 * @return: true on success, and false on failure.
 */
bool fix_non_empty_board_cells(Board *board);

#endif
