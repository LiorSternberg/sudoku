#include "Backtracking.h"
#include "../components/Stack.h"


void execute_top_stack_node(Stack *stack, int *i, int *j, int *val){
    StackNode* top_node = pop(stack);
    *i = top_node->i;
    *j = top_node->j;
    *val = top_node->val;
}

void update_next_cell_coordinates(int *i, int *j, int N){
    if (*j == N-1){ /* The rightmost cell in the row */
        *i = *i+1;
        *j = 0;
    }
    else { /* j < N-1 */
        *j = *j+1; /*and i is not changing */
    }
}

int get_num_of_solutions(Board *board) {
    int counter = 0, i = 0, j = 0, val = 0, backtrack = 0, N;
    Board *board_copy;
    Stack *stack;
    N = board->dim;

    if (is_board_erroneous(board)) {
        return -1; /* for Tslil: Maybe also print error*/
    }

    if (N == 1) {
        return 1; /*if the board is 1x1 there is 1 solution*/
    }

    /* TODO: add the validate function, and reinstate this portion of code
     * if (validate(board) != 1) { *//*The board is unsolveable (using ILP)*//*
        return 0;
    }*/

    stack = create_stack();
    board_copy = get_board_copy(board);
    fix_non_empty_board_cells(board_copy);

    while (1) {
        if (!is_cell_fixed(board, i, j)) { /* unfixed cell */
            do {
                val++;
                if (val > N) {
                    backtrack = 1; /* No legal val for the cell, need to backtrack*/
                    break;
                }
                set_cell_value(board_copy, i, j, val);
            } while (is_cell_erroneous(board_copy, i, j));

            if (backtrack == 1) {
                if (i == 0 && j == 0) {
                    break; /* can't backtrack from first cell */
                }
                set_cell_value(board_copy, i, j, 0); /* clean the cell */
                backtrack = 0;
                execute_top_stack_node(stack, &i, &j, &val);
                continue;
            }

            if (i == N - 1 && j == N - 1) { /* if last cell - increment the counter and then backtrack */
                counter++;
                set_cell_value(board_copy, i, j, 0); /* clean the cell */
                execute_top_stack_node(stack, &i, &j, &val);
                continue;
            }

            push(i, j, val, stack);
            update_next_cell_coordinates(&i, &j, N);
            val = 0;
            continue;
        } else { /*fixed cell. In this case we'll use val as an indicator to backtrack next time */
            if (!is_cell_erroneous(board_copy, i, j) && val == 0) {
                if (i == N - 1 && j == N - 1) { /* if last cell - increment the counter and then backtrack */
                    counter++;
                    execute_top_stack_node(stack, &i, &j, &val);
                    continue;
                }
                push(i, j, 1, stack); /*val==1 to backtrack from this cell next time */
                update_next_cell_coordinates(&i, &j, N);
                continue;
            }

            else { /* need to backtrack if cell is erroneous or val == 0 */
                if (i == 0 && j == 0) {
                    break; /* can't backtrack from first cell */
                }
                execute_top_stack_node(stack, &i, &j, &val);
                continue;
            }
        }
    }

    destroy_board(board_copy);
    destroy_stack(stack);
    return counter;
}