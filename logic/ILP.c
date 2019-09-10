#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ILP.h"
#include "../MemoryError.h"

#define UNUSED(x) (void)(x)
#define VAR_NAME_LEN (13)


bool solve_puzzle(Board *board) {
    /* TODO: actually implement this, and then remove the UNUSED and
     * change return value to be meaningful :) */
    UNUSED(board);
    return true;
}

int get_cell_solution(const Board *board, int row, int column) {
    Board* copy = get_board_copy(board);
    int cell_solution = 0;

    if (!solve_puzzle(copy)) {
        return ERROR_VALUE;
    }

    cell_solution = get_cell_value(copy, row, column);
    destroy_board(copy);
    return cell_solution;
}

bool is_board_solvable(const Board *board) {
    /* TODO: actually implement this, and then remove the UNUSED and
     * change return value to be meaningful :) */
    UNUSED(board);
    return true;
}

bool generate_puzzle(Board *board, States *states, int num_to_fill, int num_to_leave) {
    /* TODO: Tslil please make sure that when you make the actual changes to
     * the board you do it by using the "make_change" function, and not just
     * by setting the value to the board cell. This is needed in order to be
     * able to undo/redo the move of the 'guess' command. Note that you don't
     * need to do anything else to support the undo/redo list, the rest will
     * happen automatically.
     * Also, for undoing all the changes you've made (and resetting the board
     * to it's original state (before trying to generate a puzzle) you should
     * use the "reset_move" function. it will do all the work for you and also
     * maintain the undo/redo list.
     * So your flow should be: "make_change", "make_change",
     * "make_change"... oops! there's a problem with this puzzle: "reset_move",
     * and now you can "make_change", "make_change"... again :) */

    /* TODO: actually implement this, and then remove the UNUSED and
     * change return value to be meaningful :) */
    UNUSED(board);
    UNUSED(states);
    UNUSED(num_to_fill);
    UNUSED(num_to_leave);
    return true;
}


bool handle_gurobi_error(GRBenv *env, char *func_name, int error_code) {
    printf("ERROR %d %s(): %s\n", error_code, func_name, GRBgeterrormsg(env));
    return false;
}

bool gurobi_solver(Board *board) {
    GRBenv   *env;
    GRBmodel *model;
    int       error = 0;
    char      name[VAR_NAME_LEN];

    int       dim   = board->dim;
    int       i, j, v;
    bool     *marks, has_possible_value;

    printf("1\n");

    /* Create environment */

    printf("2\n");
    error = GRBloadenv(&env, "sudoku.log");
    if (error) {
        return handle_gurobi_error(env, "GRBloadenv", error);
    }

    printf("3\n");

    /* Create new model */

    error = GRBnewmodel(env, &model, "sudoku", 0, NULL, NULL, NULL, NULL, NULL);
    if (error) {
        return handle_gurobi_error(env, "GRBloadenv", error);
    }
    printf("4\n");

    marks = malloc(dim * sizeof(bool));
    validate_memory_allocation("gurobi_solver: marks", marks);

    printf("5\n");
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {

            /* only add variables for empty cells */
            if (!is_cell_empty(board, i, j)) {
                continue;
            }

            /* don't add variables for obvious values */
            if ((v = get_obvious_value(board, marks, i, j)) != ERROR_VALUE) {
                set_cell_value(board, i, j, v);
                continue;
            }

            has_possible_value = false;
            mark_neighboring_values(board, marks, i, j);
            for (v = 0; v < dim; v++) {
                if (!marks[v]) { /* no conflicting neighbor, so this is a possible value */
                    has_possible_value = true;
                    sprintf(name, "x[%d,%d,%d]", i, j, v+1);
                    GRBaddvar(model, 0, NULL, NULL, 1, 0, 1, GRB_BINARY, name);
                }
            }
            if (!has_possible_value) {
                return false;
            }
        }
    }

    printf("6\n");

    GRBupdatemodel(model);
    free(marks);

    printf("7\n");



    printf("8\n");


    return 0;
}