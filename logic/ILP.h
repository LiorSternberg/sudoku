#include <stdbool.h>
#include "../components/Board.h"
#include "../components/StatesList.h"

#ifndef FINAL_PROJECT_ILP_H
#define FINAL_PROJECT_ILP_H


/* Solves the board using ILP. Returns true if the board was solved
 * successfully, and false if it is not solvable. */
bool solve_puzzle(Board *board);

/* Returns true is the board has a solution (validated using ILP), and false
 * if it doesn't. This function does not change the board in any way. */
bool is_board_solvable(const Board *board);

/* This function generates a puzzle in the following way:
 *  - Chooses <num_to_fill> random empty cells.
 *  - Fills the chosen cells with legal values.
 *  - Solves the board using ILP (if it's unsolvable restart the process)
 *  - Clear all but <num_to_leave> cells (any cells, unrelated to the
 *    previously chosen cells, or the ones that were originally filled).
 *
 * Returns true if the puzzle was generated successfully, and false if 1000
 * iterations failed to generate a legal puzzle.
 *  */
bool generate_puzzle(Board *board, States *states, int num_to_fill, int num_to_leave);

#endif
