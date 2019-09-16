#include "../components/Board.h"
#include "../components/Stack.h"

#ifndef FINAL_PROJECT_BACKTRACKING_H
#define FINAL_PROJECT_BACKTRACKING_H

#endif

/**
 * Removes the top from the stack and updates row, column and val accordingly
 * @param stack: the stack to remove the top from.
 * @param row: pointer to the row current value, to be updated.
 * @param column: pointer to the column current value, to be updated.
 * @param val: pointer to the val current value, to be updated.
 */
void backtrack_to_stack_top(Stack *stack, int *row, int *column, int *val);

/**
 * Updates row and column according to the next cell coordinates (assuming that
 * (row, column) is not the last cell).
 * @param row: pointer to the row current value, to be updated.
 * @param column: pointer to the column current value, to be updated.
 * @param N: the board dimension.
 */
void update_next_cell_coordinates(int *row, int *column, int N);

/**
 * Returns the number of solutions of the board, and -1 if there is no solution
 * (meaning the board is unsolvable).
 * @param board: the board to get the number of solutions for.
 * @return: the number of solutions for the given board.
 */
int get_num_of_solutions(const Board *board);


