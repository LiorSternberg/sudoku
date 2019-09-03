#include "../components/Board.h"
#include "../components/Stack.h"

#ifndef FINAL_PROJECT_BACKTRACKING_H
#define FINAL_PROJECT_BACKTRACKING_H

#endif

/* Removes the top from the stack and updates row, column and val accordingly */
void backtrack_to_stack_top(Stack *stack, int *row, int *column, int *val);

/* Updates row and column according to the next cell coordinates (assuming that (row, column) is not the last cell) */
void update_next_cell_coordinates(int *row, int *column, int N);

/* Returns the number of solutions of the board, and -1 if there is no solution (meaning the board is erroneous)*/
int get_num_of_solutions(const Board *board);


