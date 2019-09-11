#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ILP.h"
#include "../MemoryError.h"

#define UNUSED(x) (void)(x)
#define VAR_NAME_LEN (100)

bool gurobi_ILP_solver(Board *board);

bool solve_puzzle(Board *board) {
    return gurobi_ILP_solver(board);
}

int get_cell_solution(const Board *board, int row, int column) {
    Board* copy = get_board_copy(board);
    int cell_solution;

    if (!solve_puzzle(copy)) {
        return ERROR_VALUE;
    }

    cell_solution = get_cell_value(copy, row, column);
    destroy_board(copy);
    return cell_solution;
}

bool is_board_solvable(const Board *board) {
    Board* copy = get_board_copy(board);
    bool solvable = solve_puzzle(copy);

    destroy_board(copy);
    return solvable;
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


void free_gurobi_solver_resources(GRBenv *env, GRBmodel *model, bool *marks,
        int *vars_indices, int *constraint_indices, double *constraint_coefs) {
    free(constraint_coefs);
    free(constraint_indices);
    free(vars_indices);
    free(marks);
    GRBfreemodel(model);
    GRBfreeenv(env);
}


bool gurobi_ILP_solver(Board *board) {
    GRBenv   *env = NULL;
    GRBmodel *model = NULL;
    int       error = 0;
    char      name[VAR_NAME_LEN];

    int       dim = board->dim;
    int       i, j, v, r_start, c_start, r_end, c_end, optstatus, vars_counter = 0, total_vars;
    bool     *marks = NULL, has_possible_value;
    double   *solution;

    int      *vars_indices = malloc(dim * dim * dim * sizeof(int));
    int      *constraint_indices = malloc(dim * sizeof(int));
    double   *constraint_coefs = malloc(dim * sizeof(double));

    validate_memory_allocation("gurobi_ILP_solver: vars_indices", vars_indices);
    validate_memory_allocation("gurobi_ILP_solver: constraint_indices", constraint_indices);
    validate_memory_allocation("gurobi_ILP_solver: constraint_coefs", constraint_coefs);

    printf("1\n");

    /* Create environment */

    printf("2\n");
    error = GRBloadenv(&env, "sudoku.log");
    if (error) {
        free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
        return handle_gurobi_error(env, "GRBloadenv", error);
    }

    error = GRBsetintparam(env, GRB_INT_PAR_LOGTOCONSOLE, 0);
    if (error) {
        free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
        return handle_gurobi_error(env, "GRBsetintparam", error);
    }

    printf("3\n");

    /* Create new model */

    error = GRBnewmodel(env, &model, "sudoku_model", 0, NULL, NULL, NULL, NULL, NULL);
    if (error) {
        free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
        return handle_gurobi_error(env, "GRBnewmodel", error);
    }
    printf("4\n");

    /* Add variables */

    marks = malloc(dim * sizeof(bool));
    validate_memory_allocation("gurobi_ILP_solver: marks", marks);

    printf("5\n");
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {

            /* Only add variables for empty cells. */
            if (!is_cell_empty(board, i, j)) {
                for (v = 0; v < dim; v++) {
                    vars_indices[i * dim * dim + j * dim + v] = ERROR_VALUE;
                }
                continue;
            }

            has_possible_value = false;
            mark_neighboring_values(board, marks, i, j);
            for (v = 0; v < dim; v++) {
                if (marks[v]) { /* found conflicting neighbor, so this is not a possible value */
                    vars_indices[i * dim * dim + j * dim + v] = ERROR_VALUE;
                } else {
                    has_possible_value = true;
                    sprintf(name, "x[(%d,%d),%d]", i, j, v+1);
                    error = GRBaddvar(model, 0, NULL, NULL, 1.0, 0.0, 1.0, GRB_BINARY, name);
                    if (error) {
                        free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
                        return handle_gurobi_error(env, "GRBaddvar", error);
                    }

                    vars_indices[i * dim * dim + j * dim + v] = vars_counter;
                    vars_counter++;
                }
            }
            if (!has_possible_value) {
                free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
                return false;
            }
        }
    }

    /* No vars were needed, so the board is either solved or is unsolvable */
    if (vars_counter == 0) {
        if (!is_board_erroneous(board) && board->empty_count == 0) {
            free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
            return true;
        } else {
            free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
            return false;
        }
    }
    total_vars = vars_counter;

    printf("6\n");

    error = GRBupdatemodel(model);
    if (error) {
        free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
        return handle_gurobi_error(env, "GRBupdatemodel", error);
    }

    printf("7\n");

    /* Add constraints: each cell has exactly one value */

    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            vars_counter = 0;
            sprintf(name, "cell[%d,%d]", i, j);

            for (v = 0; v < dim; v++) {
                if (vars_indices[i*dim*dim + j*dim + v] == ERROR_VALUE){
                    continue;
                }

                constraint_indices[vars_counter] = vars_indices[i*dim*dim + j*dim + v];
                constraint_coefs[vars_counter] = 1.0;
                vars_counter++;
            }

            if (vars_counter == 0) {
                continue;
            }

            for (v = vars_counter; v < dim; v++) {
                constraint_indices[v] = 0;
                constraint_coefs[v] = 0.0;
            }

            error = GRBaddconstr(model, vars_counter, constraint_indices, constraint_coefs, GRB_EQUAL, 1.0, name);
            if (error) {
                free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
                return handle_gurobi_error(env, "GRBaddconstr", error);
            };
        }
    }

    printf("8\n");

    /* Add constraints: each value appears exactly once in each row */

    for (v = 0; v < dim; v++) {
        for (i = 0; i < dim; i++) {
            vars_counter = 0;
            sprintf(name, "row_val[%d,%d]", i, v+1);

            for (j = 0; j < dim; j++) {
                if (vars_indices[i*dim*dim + j*dim + v] == ERROR_VALUE){
                    continue;
                }

                constraint_indices[vars_counter] = vars_indices[i*dim*dim + j*dim + v];
                constraint_coefs[vars_counter] = 1.0;
                vars_counter++;
            }

            if (vars_counter == 0) {
                continue;
            }

            for (j = vars_counter; j < dim; j++) {
                constraint_indices[j] = 0;
                constraint_coefs[j] = 0.0;
            }

            error = GRBaddconstr(model, vars_counter, constraint_indices, constraint_coefs, GRB_EQUAL, 1.0, name);
            if (error) {
                free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
                return handle_gurobi_error(env, "GRBaddconstr", error);
            };
        }
    }

    printf("9\n");

    /* Add constraints: each value appears exactly once in each column */

    for (v = 0; v < dim; v++) {
        for (j = 0; j < dim; j++) {
            vars_counter = 0;
            sprintf(name, "column_val[%d,%d]", j, v+1);

            for (i = 0; i < dim; i++) {
                if (vars_indices[i*dim*dim + j*dim + v] == ERROR_VALUE){
                    continue;
                }

                constraint_indices[vars_counter] = vars_indices[i*dim*dim + j*dim + v];
                constraint_coefs[vars_counter] = 1.0;
                vars_counter++;
            }

            if (vars_counter == 0) {
                continue;
            }

            for (i = vars_counter; i < dim; i++) {
                constraint_indices[i] = 0;
                constraint_coefs[i] = 0.0;
            }

            error = GRBaddconstr(model, vars_counter, constraint_indices, constraint_coefs, GRB_EQUAL, 1.0, name);
            if (error) {
                free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
                return handle_gurobi_error(env, "GRBaddconstr", error);
            };
        }
    }

    printf("10\n");

    /* Add constraints: each value appears exactly once in each block */

    for (v = 0; v < dim; v++) {
        for (r_start = 0; r_start < dim; r_start += board->num_of_rows_in_block) {
            r_end = r_start + board->num_of_rows_in_block;

            for (c_start = 0; c_start < dim; c_start += board->num_of_columns_in_block) {
                c_end = c_start + board->num_of_columns_in_block;


                vars_counter = 0;
                sprintf(name, "block_val[(%d,%d),%d]", r_start, c_start, v+1);

                for (i = r_start; i < r_end; i++) {
                    for (j = c_start; j < c_end; j++) {
                        if (vars_indices[i * dim * dim + j * dim + v] == ERROR_VALUE) {
                            continue;
                        }
                        constraint_indices[vars_counter] = vars_indices[i * dim * dim + j * dim + v];
                        constraint_coefs[vars_counter] = 1.0;
                        vars_counter++;
                    }
                }

                if (vars_counter == 0) {
                    continue;
                }

                for (i = vars_counter; i < dim; i++) {
                    constraint_indices[i] = 0;
                    constraint_coefs[i] = 0.0;
                }

                error = GRBaddconstr(model, vars_counter, constraint_indices, constraint_coefs, GRB_EQUAL, 1.0, name);
                if (error) {
                    free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
                    return handle_gurobi_error(env, "GRBaddconstr", error);
                };

            }
        }
    }

    printf("11\n");

    error = GRBupdatemodel(model);
    if (error) {
        free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
        return handle_gurobi_error(env, "GRBupdatemodel", error);
    }

    /* Solve */

    error = GRBoptimize(model);
    if (error) {
        free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
        return handle_gurobi_error(env, "GRBoptimize", error);
    }

    printf("12\n");

    /* Write model to 'sudoku.lp'*/

    error = GRBwrite(model, "sudoku.lp");
    if (error) {
        free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
        return handle_gurobi_error(env, "GRBwrite", error);
    }

    printf("13\n");

    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optstatus);
    if (error) {
        free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
        return handle_gurobi_error(env, "GRBgetintattr", error);
    }

    printf("14\n");

    /* Handle solution */

    if (optstatus != GRB_OPTIMAL) {
        free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
        return false;
    }

    solution = malloc(total_vars * sizeof(double));
    validate_memory_allocation("gurobi_ILP_solver: solution", solution);

    error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, total_vars, solution);
    if (error) {
        free(solution);
        free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
        return handle_gurobi_error(env, "GRBwrite", error);
    }

    printf("15\n");

    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            for (v = 0; v < dim; v++) {
                if (vars_indices[i * dim * dim + j * dim + v] == ERROR_VALUE) {
                    continue;
                }

                if (solution[vars_indices[i * dim * dim + j * dim + v]] == 1.0) {
                    set_cell_value(board, i, j, v+1);
                }
            }
        }
    }
    free(solution);

    /* Check if the board is solved */

    if (!is_board_erroneous(board) && board->empty_count == 0) {
        free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
        printf("true!\n");
        return true;
    } else {
        printf("false! %d, %d\n", is_board_erroneous(board), board->empty_count);
        free_gurobi_solver_resources(env, model, marks, vars_indices, constraint_indices, constraint_coefs);
        return false;
    }
}