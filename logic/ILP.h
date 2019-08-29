#include <stdbool.h>
#include "../components/Board.h"

#ifndef FINAL_PROJECT_ILP_H
#define FINAL_PROJECT_ILP_H


/* Solves the board using ILP. Returns true if the board was solved
 * successfully, and false if it is not solvable. */
bool solve(Board *board);

/* Returns true is the board has a solution (validated using ILP), and false
 * if it doesn't. This function does not change the board in any way. */
bool is_board_solvable(const Board *board);


#endif
