#include <stdlib.h>

#include "gurobi_c.h"
#include "solver.h"
#include "../MemoryError.h"

#define VAR_NAME_LEN (100)
#define CELL_NAME_FORMAT "cell[%d,%d]"
#define ROW_NAME_FORMAT "row_val[%d,%d]"
#define COLUMN_NAME_FORMAT "column_val[%d,%d]"


/* Types of constraints of the same structure */
typedef enum {
    cell,
    row,
    column
} ConstraintType;

/* Gurobi ILP Model Solving */


/* Report error in gurobi and return error status */
bool handle_gurobi_error(GRBenv *env, char *func_name, int error_code) {
    printf("ERROR %d %s(): %s\n", error_code, func_name, GRBgeterrormsg(env));
    return false;
}


/* Free resources used in the gurobi solver */
void free_gurobi_resources(GRBenv *env, GRBmodel *model, int *vars_indices) {
    free(vars_indices);
    GRBfreemodel(model);
    GRBfreeenv(env);
}

/* Set the constraint indices and coefficients */
void set_constraint(int *constraint_indices, double *constraint_coefs, const int *vars_indices, int *vars_counter,
        int index) {
    constraint_indices[*vars_counter] = vars_indices[index];
    constraint_coefs[*vars_counter] = 1.0;
    (*vars_counter)++;

}

/* Add a constraint to the model */
bool add_constraints(GRBenv *env, GRBmodel *model, int dim, char *name, int *vars_indices,
        int *constraint_indices, double *constraint_coefs, int vars_counter) {
    int error, index;
    for (index = vars_counter; index < dim; index++) {
        constraint_indices[index] = 0;
        constraint_coefs[index] = 0.0;
    }

    error = GRBaddconstr(model, vars_counter, constraint_indices, constraint_coefs, GRB_EQUAL, 1.0, name);
    if (error) {
        free_gurobi_resources(env, model, vars_indices);
        return handle_gurobi_error(env, "GRBaddconstr", error);
    };

    return true;
}

/* Calculate the variable index based on the type of the constraint */
int calc_index_for_constraint(ConstraintType type, int primary, int secondary, int internal, int dim) {
    switch (type) {
        case cell:
            return primary*dim*dim + secondary*dim + internal;
        case row:
            return secondary*dim*dim + internal*dim + primary;
        case column:
            return internal*dim*dim + secondary*dim + primary;
    }
    return 0;
}

/* Format the name of constraint */
void format_constraint_name(ConstraintType type, int primary, int secondary, char *name) {
    switch (type) {
        case cell:
            sprintf(name, CELL_NAME_FORMAT, primary, secondary);
            return;
        case row:
            sprintf(name, ROW_NAME_FORMAT, secondary, primary + 1);
            return;
        case column:
            sprintf(name, COLUMN_NAME_FORMAT, secondary, primary + 1);
            return;
    }
}

/* Add constraints by type (cell, row, column):
 *  # 'cell' - make sure each cell has exactly one value */
/*  # 'row' - make sure each value appears exactly once in each row */
/*  # 'column' - make sure each value appears exactly once in each column */
bool add_constraints_by_type(GRBenv *env, GRBmodel *model, int dim, int *vars_indices, char *name,
                             int *constraint_indices, double *constraint_coefs, ConstraintType type) {
    int primary, secondary, internal, vars_counter;
    for (primary = 0; primary < dim; primary++) {
        for (secondary = 0; secondary < dim; secondary++) {
            vars_counter = 0;

            format_constraint_name(type, primary, secondary, name);
            for (internal = 0; internal < dim; internal++) {
                if (vars_indices[calc_index_for_constraint(type, primary, secondary, internal, dim)] == ERROR_VALUE){
                    continue;
                }
                set_constraint(constraint_indices, constraint_coefs, vars_indices, &vars_counter,
                               calc_index_for_constraint(type, primary, secondary, internal, dim));
            }

            if (vars_counter == 0) {
                continue;
            }

            if (!add_constraints(env, model, dim, name, vars_indices, constraint_indices,
                                 constraint_coefs, vars_counter)) {
                return false;
            };
        }
    }
    return true;
}

/* Add constraints to make sure each value appears exactly once in each block */
bool add_block_constraints(GRBenv *env, GRBmodel *model, Board *board, int *vars_indices, char *name,
                           int *constraint_indices, double *constraint_coefs) {
    int i, j, v, r_start, c_start, r_end, c_end, index, vars_counter, dim = board->dim;
    for (v = 0; v < dim; v++) {
        for (r_start = 0; r_start < dim; r_start += board->num_of_rows_in_block) {
            r_end = r_start + board->num_of_rows_in_block;

            for (c_start = 0; c_start < dim; c_start += board->num_of_columns_in_block) {
                c_end = c_start + board->num_of_columns_in_block;

                vars_counter = 0;
                sprintf(name, "block_val[(%d,%d),%d]", r_start, c_start, v+1);

                for (i = r_start; i < r_end; i++) {
                    for (j = c_start; j < c_end; j++) {
                        index = i * dim * dim + j * dim + v;
                        if (vars_indices[index] == ERROR_VALUE) {
                            continue;
                        }
                        set_constraint(constraint_indices, constraint_coefs, vars_indices, &vars_counter, index);
                    }
                }

                if (vars_counter == 0) {
                    continue;
                }

                if (!add_constraints(env, model, dim, name, vars_indices, constraint_indices,
                                     constraint_coefs, vars_counter)) {
                    return false;
                };
            }
        }
    }
    return true;
}


/* Add a variable for each empty cell and legal value */
bool add_variables(GRBenv *env, GRBmodel *model, Board *board, int dim, char *name,
        int *vars_indices, int *vars_counter) {
    int i, j, v, error;
    bool has_possible_value, *marks;

    marks = malloc(dim * sizeof(bool));
    validate_memory_allocation("gurobi_ILP_solver: marks", marks);

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
                }
                else {
                                        has_possible_value = true;
                    sprintf(name, "x[(%d,%d),%d]", i, j, v+1);
                                        error = GRBaddvar(model, 0, NULL, NULL, 1.0, 0.0, 1.0, GRB_BINARY, name);
                                        if (error) {
                        free(marks);
                        free_gurobi_resources(env, model, vars_indices);
                        return handle_gurobi_error(env, "GRBaddvar", error);
                    }

                    vars_indices[i * dim * dim + j * dim + v] = (*vars_counter);
                    (*vars_counter)++;
                                    }
            }

            if (!has_possible_value) {
                free(marks);
                free_gurobi_resources(env, model, vars_indices);
                return false;
            }

        }
    }

    free(marks);
    return true;
}

/* Assert some variables were added (otherwise no need for the solver), and update the model. */
bool assert_variables_added(GRBenv *env, GRBmodel *model, Board *board, int *vars_indices,
        const int *vars_counter) {
    int error;

    /* If no vars were needed, so the board is either solved or is unsolvable */
    if ((*vars_counter) == 0) {
        if (!is_board_erroneous(board) && board->empty_count == 0) {
            free_gurobi_resources(env, model, vars_indices);
            return true;
        } else {
            free_gurobi_resources(env, model, vars_indices);
            return false;
        }
    }

    error = GRBupdatemodel(model);
    if (error) {
        free_gurobi_resources(env, model, vars_indices);
        return handle_gurobi_error(env, "GRBupdatemodel", error);
    }
    return true;
}

/* Set up the gurobi environment and create empty model. */
bool set_environment(GRBenv **env, GRBmodel **model) {
    int error;

    error = GRBloadenv(env, "sudoku.log");
    if (error) {
        free_gurobi_resources(*env, *model, NULL);
        return handle_gurobi_error(*env, "GRBloadenv", error);
    }

    error = GRBsetintparam(*env, GRB_INT_PAR_LOGTOCONSOLE, 0);
    if (error) {
        free_gurobi_resources(*env, *model, NULL);
        return handle_gurobi_error(*env, "GRBsetintparam", error);
    }

    error = GRBnewmodel(*env, model, "sudoku_model", 0, NULL, NULL, NULL, NULL, NULL);
    if (error) {
        free_gurobi_resources(*env, *model, NULL);
        return handle_gurobi_error(*env, "GRBnewmodel", error);
    }

    return true;
}

/* Extract the optimal solution, and update the board accordingly */
bool fill_solution(GRBenv *env, GRBmodel *model, Board *board, int *vars_indices, int vars_counter) {
    int error, i, j, v, dim = board->dim;

    double *solution = malloc(vars_counter * sizeof(double));
    validate_memory_allocation("gurobi_ILP_solver: solution", solution);

    error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, vars_counter, solution);
    if (error) {
        free(solution);
        free_gurobi_resources(env, model, vars_indices);
        return handle_gurobi_error(env, "GRBwrite", error);
    }

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
    return true;
}

/* The main ILP board solving function. Solves the board if possible using ILP, and returns true on
 * success, or false on error. */
bool gurobi_ILP_solver(Board *board) {
    GRBenv   *env = NULL;
    GRBmodel *model = NULL;
    int       error = 0;
    char      name[VAR_NAME_LEN];

    int       dim = board->dim;
    int       optstatus, vars_counter = 0;

    int      *vars_indices = NULL;
    int      *constraint_indices = NULL;
    double   *constraint_coefs = NULL;


    /* Create environment & model */

    set_environment(&env, &model);



    /* Add variables */

    vars_indices = malloc(dim * dim * dim * sizeof(int));
    validate_memory_allocation("gurobi_ILP_solver: vars_indices", vars_indices);
    if (!add_variables(env, model, board, dim, name, vars_indices, &vars_counter)) {
        return false;
    };


    assert_variables_added(env, model, board, vars_indices, &vars_counter);



    /* Add constraints */

    constraint_indices = malloc(dim * sizeof(int));
    validate_memory_allocation("gurobi_ILP_solver: constraint_indices", constraint_indices);
    constraint_coefs = malloc(dim * sizeof(double));
    validate_memory_allocation("gurobi_ILP_solver: constraint_coefs", constraint_coefs);

    if (!add_constraints_by_type(env, model, dim, vars_indices, name, constraint_indices, constraint_coefs, cell)
     || !add_constraints_by_type(env, model, dim, vars_indices, name, constraint_indices, constraint_coefs, row)
     || !add_constraints_by_type(env, model, dim, vars_indices, name, constraint_indices, constraint_coefs, column)
     || !add_block_constraints(env, model, board, vars_indices, name, constraint_indices, constraint_coefs)) {
        free(constraint_indices);
        free(constraint_coefs);
        return false;
    }

    free(constraint_indices);
    free(constraint_coefs);


    error = GRBupdatemodel(model);
    if (error) {
        free_gurobi_resources(env, model, vars_indices);
        return handle_gurobi_error(env, "GRBupdatemodel", error);
    }

    /* Write model to 'sudoku.lp'*/

    error = GRBwrite(model, "sudoku.lp");
    if (error) {
        free_gurobi_resources(env, model, vars_indices);
        return handle_gurobi_error(env, "GRBwrite", error);
    }

    /* Solve */

    error = GRBoptimize(model);
    if (error) {
        free_gurobi_resources(env, model, vars_indices);
        return handle_gurobi_error(env, "GRBoptimize", error);
    }

    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optstatus);
    if (error) {
        free_gurobi_resources(env, model, vars_indices);
        return handle_gurobi_error(env, "GRBgetintattr", error);
    }

    /* Handle solution */

    if (optstatus != GRB_OPTIMAL) {
        free_gurobi_resources(env, model, vars_indices);
        return false;
    }

    fill_solution(env, model, board, vars_indices, vars_counter);

    /* Check if the board is solved */
    if (!is_board_erroneous(board) && board->empty_count == 0) {
        free_gurobi_resources(env, model, vars_indices);
        return true;
    } else {
        free_gurobi_resources(env, model, vars_indices);
        return false;
    }
}
