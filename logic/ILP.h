#ifndef FINAL_PROJECT_ILP_H
#define FINAL_PROJECT_ILP_H

#include <stdbool.h>
#include "../components/Board.h"
#include "../components/StatesList.h"

#define ERROR_VALUE (-1)


/**
 * Solves the board using ILP. Returns true if the board was solved
 * successfully, and false if it is not solvable.
 * @param board: the board to solve.
 * @param states: the states list to update with the solution. Can be NULL in
 * case the solution doesn't need to be represented in the state.
 * @return: true if the board was solved successfully, and false if it is not
 * solvable.
 */
bool solve_puzzle(Board *board, States *states);

/**
 * Emulates solving the board using ILP. Returns the value of the solution
 * for the given cell. If the board is not solvable -1 is returned.
 * @param board: the board to solve.
 * @param row: the index of the cell's row (zero-based).
 * @param column: the index of the cell's column (zero-based).
 * @return: the solution found for the cell, or -1 if the board is unsolvable.
 */
int get_cell_solution(const Board *board, int row, int column);

/**
 * Returns true is the board has a solution (validated using ILP), and false
 * if it doesn't. This function does not change the board in any way.
 * @param board: the board to check.
 * @return: true is the board has a solution, and false if it doesn't.
 */
bool is_board_solvable(const Board *board);

/**
 * This function generates a puzzle in the following way:
 *  - Chooses <num_to_fill> random empty cells.
 *  - Fills the chosen cells with random legal values.
 *  - Solves the board using ILP (if it's unsolvable restart the process)
 *  - Clear all but <num_to_leave> cells (any cells, unrelated to the
 *    previously chosen cells, or the ones that were originally filled).
 *
 * @param board: the board to generate the puzzle based on.
 * @param states: the states list to be updated according to the changes.
 * @param num_to_fill: the number of cells to fill.
 * @param num_to_leave: the number of cell to leave after the board is solved.
 * @return: true if the puzzle was generated successfully, and false if 1000
 * iterations failed to generate a legal puzzle.
 */
bool generate_puzzle(Board *board, States *states, int num_to_fill, int num_to_leave);

#endif
