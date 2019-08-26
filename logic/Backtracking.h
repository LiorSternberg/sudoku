#include "../components/Board.h"
#include "../components/Stack.h"

#ifndef FINAL_PROJECT_BACKTRACKING_H
#define FINAL_PROJECT_BACKTRACKING_H

#endif

/* Removes the top from the stack and updates i, j and val accordingly */
void execute_top_stack_node(Stack *stack, int *i, int *j, int *val);

/* Updates i and j according to the next cell coordinates (assuming that (i,j) is not the last cell) */
void update_next_cell_coordinates(int *i, int *j, int N);

/* Returns the number of solutions of the board, and -1 if there is no solution (meaning the board is erroneous)*/
int get_num_of_solutions(Board *board);


