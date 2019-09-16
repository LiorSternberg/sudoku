#include <stdlib.h>

#include "gurobi_c.h"
#include "solver.h"
#include "../MemoryError.h"
#include "random.h"
#include "../components/StatesList.h"

#define VAR_NAME_LEN (100)
#define RANGE_CONST (10)
#define CELL_NAME_FORMAT "cell[%d,%d]"
#define ROW_NAME_FORMAT "row_val[%d,%d]"
#define COLUMN_NAME_FORMAT "column_val[%d,%d]"


/* Types of constraints of the same structure */
typedef enum {
    cell,
    row,
    column
} ConstraintType;


/* Gurobi ILP/LP Model Solving */

/* Reports error in gurobi and return error status */
bool handle_gurobi_error(GRBenv *env, char *func_name, int error_code) {
    printf("ERROR %d %s(): %s\n", error_code, func_name, GRBgeterrormsg(env));
    return false;
}

/* Frees resources used in the gurobi solver */
void free_gurobi_resources(GRBenv *env, GRBmodel *model, int *vars_indices) {
    free(vars_indices);
    GRBfreemodel(model);
    GRBfreeenv(env);
}

/* Sets the constraint indices and coefficients */
void set_constraint(int *constraint_indices, double *constraint_coefs, const int *vars_indices, int *vars_counter,
        int index) {
    constraint_indices[*vars_counter] = vars_indices[index];
    constraint_coefs[*vars_counter] = 1.0;
    (*vars_counter)++;
}

/* Adds a constraint to the model */
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
    }
    return true;
}

/* Calculates the variable index based on the type of the constraint */
int calc_index_for_constraint(ConstraintType type, int primary, int secondary, int internal, int dim) {
    switch (type) {
        case cell:
            return primary*dim*dim + secondary*dim + internal;
        case row:
            return secondary*dim*dim + internal*dim + primary;
        case column:
            return internal*dim*dim + secondary*dim + primary;
        default:
            return 0;
    }
}

/* Formats the name of constraint */
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

/* Adds constraints by type (cell, row, column):
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
            }
        }
    }
    return true;
}

/* Adds constraints to make sure each value appears exactly once in each block */
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

/* Gets the objective function variable coefficient based on the given
 * VariableType. in case of a continuous variable (LP) randomly chooses a
 * coefficient in a range determined by the board dimension. */
double get_objective_coefficient(VariableType var_type, int dim) {
    switch (var_type) {
        case integer:
            return 1.0;
        case continuous:
            return get_rand_index(dim * dim * RANGE_CONST);
        default:
            return 1.0;
    }
}

/* Gets the Gurobi variable type based on the given VariableType. */
char get_gurobi_var_type(VariableType var_type) {
    switch (var_type) {
        case integer:
            return GRB_BINARY;
        case continuous:
            return GRB_CONTINUOUS;
        default:
            return GRB_BINARY;
    }
}

/* Adds a variable for each empty cell and legal value */
bool add_variables(GRBenv *env, GRBmodel *model, VariableType var_type, Board *board,
        int dim, char *name, int *vars_indices, int *vars_counter) {
    int i, j, v, error;
    double obj;
    char gurobi_var_type;
    bool has_possible_value, *marks;

    marks = malloc(dim * sizeof(bool));
    validate_memory_allocation("gurobi_solver: marks", marks);

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
                    obj = get_objective_coefficient(var_type, dim);
                    gurobi_var_type = get_gurobi_var_type(var_type);
                    error = GRBaddvar(model, 0, NULL, NULL, obj, 0.0, 1.0, gurobi_var_type, name);
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

/* Asserts some variables were added (otherwise no need for the solver), and
 * updates the model. */
bool assert_variables_added(GRBenv *env, GRBmodel *model, Board *board,
        int *vars_indices, const int *vars_counter) {
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

/* Sets up the gurobi environment and creates an empty model. */
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

/* Extracts the optimal solution probabilities for a single cell, and updates
 * the given guesses array accordingly. */
bool get_cell_guess_probabilities(GRBenv *env, GRBmodel *model, double *guesses,
        int row, int column, int dim, int *vars_indices) {
    int error, v, index;

    for (v = 0; v < dim; v++) {
        index = vars_indices[row * dim * dim + column * dim + v];
        if (index == ERROR_VALUE) {
            guesses[v] = 0.0;
            continue;
        }
        error = GRBgetdblattrelement(model, GRB_DBL_ATTR_X, index, &(guesses[v]));
        if (error) {
            free_gurobi_resources(env, model, vars_indices);
            return handle_gurobi_error(env, "GRBgetdblattrelement", error);
        }
    }
    return true;
}

/* Extracts the optimal solution probabilities for a single cell, and updates
 * the data's guesses array accordingly. */
bool fill_cell_guess_solution(GRBenv *env, GRBmodel *model, SolutionData *data,
        int dim, int *vars_indices) {
    double *guesses = malloc(dim * sizeof(double));
    validate_memory_allocation("fill_cell_guess_solution", guesses);

    if (!get_cell_guess_probabilities(env, model, guesses, data->row, data->column, dim, vars_indices)) {
        free(guesses);
        return false;
    }

    data->guesses = guesses;
    return true;
}

/* Clears illegal values created along the way from the probabilities so they won't
 * be considered */
void clear_illegal_probabilities(Board *board, double *guesses, bool *marks, int i, int j) {
    int v;
    mark_neighboring_values(board, marks, i, j);

    for (v = 0; v < board->dim; v++) {
        if (marks[v]) {
            guesses[v] = 0.0;
        }
    }
}

/* Extracts the optimal solution, and updates the board accordingly */
bool fill_board_guess_solution(GRBenv *env, GRBmodel *model, Board *board, States *states,
        double threshold, int *vars_indices, int vars_counter) {
    int error, i, j, value, dim = board->dim;
    double *solution, *guesses;
    bool *marks;

    solution = malloc(vars_counter * sizeof(double));
    validate_memory_allocation("fill_board_guess_solution", solution);
    guesses = malloc(dim * sizeof(double));
    validate_memory_allocation("fill_cell_guess_solution", guesses);
    marks = malloc(dim * sizeof(bool));
    validate_memory_allocation("gurobi_solver: marks", marks);

    error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, vars_counter, solution);
    if (error) {
        free(guesses);
        free(solution);
        free(marks);
        free_gurobi_resources(env, model, vars_indices);
        return handle_gurobi_error(env, "GRBgetdblattrarray", error);
    }

    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            if (!is_cell_empty(board, i, j)) {
                continue;
            }

            if (!get_cell_guess_probabilities(env, model, guesses, i, j, dim, vars_indices)) {
                continue;
            }

            clear_illegal_probabilities(board, guesses, marks, i, j);
            value = weighted_random_choice_with_threshold(guesses, dim, threshold);
            if (value == ERROR_VALUE) {
                continue;
            }
            make_change(board, states, i, j, value+1);
        }
    }
    free(guesses);
    free(solution);
    free(marks);
    return true;
}

/* Extracts the optimal solution, and updates the board accordingly */
bool fill_board_solution(GRBenv *env, GRBmodel *model, Board *board, States *states,
        int *vars_indices, int vars_counter) {
    int error, i, j, v, dim = board->dim;

    double *solution = malloc(vars_counter * sizeof(double));
    validate_memory_allocation("fill_board_solution", solution);

    error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, vars_counter, solution);
    if (error) {
        free(solution);
        free_gurobi_resources(env, model, vars_indices);
        return handle_gurobi_error(env, "GRBgetdblattrarray", error);
    }

    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            for (v = 0; v < dim; v++) {
                if (vars_indices[i * dim * dim + j * dim + v] == ERROR_VALUE) {
                    continue;
                }

                if (solution[vars_indices[i * dim * dim + j * dim + v]] == 1.0) {
                    if (states != NULL) {
                        make_change(board, states, i, j, v+1);
                    } else {
                        set_cell_value(board, i, j, v+1);
                    }
                }
            }
        }
    }
    free(solution);

    /* Check if the board is solved */
    if (!is_board_erroneous(board) && board->empty_count == 0) {
        return true;
    } else {
        return false;
    }
}

/* Fills the optimal solution that was found based on the type of variable (determines
 * LP/ILP), and the solution type (whole board or single cell). */
bool fill_solution(GRBenv *env, GRBmodel *model, Board *board, States *states, VariableType var_type,
        SolutionType sol_type, SolutionData *data, double threshold, int *vars_indices, int vars_counter) {
    switch (var_type) {
        case integer:
            return fill_board_solution(env, model, board, states, vars_indices, vars_counter);
        case continuous:
            switch (sol_type) {
                case cell_hint:
                    return fill_cell_guess_solution(env, model, data, board->dim, vars_indices);
                case solve_board:
                    return fill_board_guess_solution(env, model, board, states, threshold, vars_indices, vars_counter);
                default:
                    return false;
            }
        default:
            return false;
    }
}


/* The main board solving function. Solves the board if possible using ILP/LP, and returns true on
 * success, or false on error. */
bool gurobi_solver(Board *board, States *states, VariableType var_type, SolutionType sol_type,
                   SolutionData *data, double threshold) {
    GRBenv   *env = NULL;
    GRBmodel *model = NULL;
    int       error = 0;
    char      name[VAR_NAME_LEN];
    int       dim = board->dim;
    int       optstatus, vars_counter = 0;
    bool      success;
    int      *vars_indices = NULL;
    int      *constraint_indices = NULL;
    double   *constraint_coefs = NULL;

    /* Create environment & model */
    set_environment(&env, &model);

    /* Add variables */
    vars_indices = malloc(dim * dim * dim * sizeof(int));
    validate_memory_allocation("gurobi_solver: vars_indices", vars_indices);
    if (!add_variables(env, model, var_type, board, dim, name, vars_indices, &vars_counter)) {
        return false;
    };
    assert_variables_added(env, model, board, vars_indices, &vars_counter);

    /* Add constraints */
    constraint_indices = malloc(dim * sizeof(int));
    validate_memory_allocation("gurobi_solver: constraint_indices", constraint_indices);
    constraint_coefs = malloc(dim * sizeof(double));
    validate_memory_allocation("gurobi_solver: constraint_coefs", constraint_coefs);

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

    success = fill_solution(env, model, board, states, var_type, sol_type, data, threshold,
            vars_indices, vars_counter);
    free_gurobi_resources(env, model, vars_indices);
    return success;
}

