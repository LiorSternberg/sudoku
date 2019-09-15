#include "Backtracking.h"
#include "../components/Stack.h"
#include "ILP.h"


void backtrack_to_stack_top(Stack *stack, int *row, int *column, int *val){
    StackNode* top_node = pop(stack);
    *row = top_node->row;
    *column = top_node->column;
    *val = top_node->val;
    destroy_stack_node(top_node);
}

void update_next_cell_coordinates(int *row, int *column, int N){
    if (*column == N-1){ /* The rightmost cell in the row */
        *row = *row + 1;
        *column = 0;
    }
    else { /* column < N-1 */
        *column = *column + 1; /* and row is not changing */
    }
}

int get_num_of_solutions(const Board *board) {
    int counter = 0, row = 0, column = 0, val = CLEAR, N = board->dim;
    bool backtrack = false;
    Board *board_copy;
    Stack *stack;

    if (N == 1) {
        return 1; /*if the board is 1x1 there is 1 solution*/
    }

    if (!is_board_solvable(board)) { /* The board is unsolvable (using ILP) */
        return 0;
    }

    stack = create_stack();
    board_copy = get_board_copy(board);
    fix_non_empty_board_cells(board_copy);

    while (1) {
        if (is_cell_fixed(board_copy, row, column)) {
            if (row == N - 1 && column == N - 1) { /* if last cell - increment the counter and then backtrack */
                counter++;
                if (is_stack_empty(stack)) {
                    break; /* can't backtrack  */
                }
                backtrack_to_stack_top(stack, &row, &column, &val);
                continue;
            }

            update_next_cell_coordinates(&row, &column, N);
            continue;
        } else {
            do {
                val++;
                if (val > N) {
                    backtrack = true; /* No legal values for the cell, need to backtrack*/
                    break;
                }
                set_cell_value(board_copy, row, column, val);
            } while (is_cell_erroneous(board_copy, row, column));

            if (backtrack) {
                if (is_stack_empty(stack)) {
                    break; /* can't backtrack  */
                }
                set_cell_value(board_copy, row, column, CLEAR); /* clear the cell */
                backtrack = false;
                backtrack_to_stack_top(stack, &row, &column, &val);
                continue;
            }

            if (row == N - 1 && column == N - 1) { /* if last cell - increment the counter and then backtrack */
                counter++;
                set_cell_value(board_copy, row, column, CLEAR); /* clear the cell */
                if (is_stack_empty(stack)) {
                    break; /* can't backtrack  */
                }
                backtrack_to_stack_top(stack, &row, &column, &val);
                continue;
            }

            push(row, column, val, stack);
            update_next_cell_coordinates(&row, &column, N);
            val = CLEAR;
            continue;
        }
    }

    destroy_board(board_copy);
    destroy_stack(stack);
    return counter;
}