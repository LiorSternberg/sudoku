#include <stdio.h>
#include <stdlib.h>

#include "LP.h"
#include "../MemoryError.h"

#define UNUSED(x) (void)(x)


void guess_solution(Board *board, States *states, double threshold) {
    /* TODO: Tslil please make sure that when you make the actual changes to
     * the board you do it by using the "make_change" function, and not just
     * by setting the value to the board cell. This is needed in order to be
     * able to undo/redo the move of the 'guess' command. Note that you don't
     * need to do anything else to support the undo/redo list, the rest will
     * happen automatically :) */

    /* TODO: actually implement this, and then remove the UNUSED :) */
    UNUSED(board);
    UNUSED(states);
    UNUSED(threshold);

}

double* get_cell_guesses(const Board *board, int row, int column) {
    double *guesses = calloc(board->dim, sizeof(double));
    validate_memory_allocation("create_stack", guesses);

    /* TODO: actually implement this, and then remove the UNUSED :) */
    UNUSED(row);
    UNUSED(column);

    /* In case of an error:
     *
     * if (*//* had an error running LP *//*) {
        free(guesses);
        return NULL;
    }
    */

    return guesses;
}

/*
Variable* create_variable(int row, int column, int val, int var_index){
    Variable *var = (Variable*)malloc(sizeof(Variable));
    validate_memory_allocation("create_variable", var);

    var->row = row;
    var->column = column;
    var->val = val;
    var->var_index = var_index;

    return var;
}

void add_variable(LPSol *board_sol, int row, int column, int val, int index){
    */
/* TODO *//*

}

int get_variable_index(LPSol *board_sol, int row, int column, int val){
    */
/* TODO *//*

}

void destroy_variable(Variable *var){
    free(var);
}

LPSol* create_LP_sol(int dim){
    int i, j;
    LPSol *board_sol = (LPSol*) malloc(sizeof(LPSol));
    validate_memory_allocation("create_LP_sol", board_sol);

    board_sol->dim = dim;
    board_sol->map_by_cell = (List) malloc(dim * dim * sizeof(List));
    validate_memory_allocation("create_LP_sol", board_sol->map_by_cell);

    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            board_sol->map_by_cell[i * dim + j] = NULL;
        }
    }
    board_sol->sol = NULL;
    board_sol->solved = -1; */
/* Default. *//*

    return board_sol;
}

void destroy_LP_sol(LPSol *board_sol) {
    int i, j, dim = board_sol->dim;
    List **map_by_cell = board_sol->map_by_cell;

    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            if (map_by_cell[i * dim + j] != NULL) {
                destroy_list(map_by_cell[i * dim + j]); */
/*for Tslil: need to destroy all nodes and variables fields before*//*

            }
        }
    }

    free(map_by_cell);

    if (board_sol->sol != NULL) {
        free(board_sol->sol);
    }

    free(board_sol);
}

void destroyGurobi(GRBenv *env, GRBmodel *model, int *ind, double *val, double *obj, char *vtype) {
    GRBfreemodel(model);
    GRBfreeenv(env);
    free(ind);
    free(val);
    if (obj != NULL) {
        free(obj);
    }
    if (vtype != NULL) {
        free(vtype);
    }
    */
/* LPSolution will be freed outside *//*

}

LPSol* get_LP_solution(Board *board, int integer){
    GRBenv *env = NULL;
    GRBmodel *model = NULL;
    LPSol *board_sol;
    int i, j, v, k, l, n = board->num_of_rows_in_block, m = board->num_of_columns_in_block,
            N = board->dim, index = 0, valid;
    int constraints = 0, vars_in_constraint , found_val = 0;
    int error = 0;
    double *sol = NULL; */
/* The solution values of the variables *//*

    int *ind = malloc(N * sizeof(int)); */
/* Which variables participate in the constraint *//*

    double *val = malloc(N * sizeof(double)); */
/* The coefficients of the variables that participate in the constraint *//*

    double *obj = NULL; */
/* The coefficients of the target function *//*

    char *vtype = NULL; */
/* The variables types *//*

    int optimstatus;
    double objval;

    validate_memory_allocation("get_LP_solution", ind);
    validate_memory_allocation("get_LP_solution", val);

    board_sol = create_LP_sol(N);

    */
/* Create environment - log file is board.log *//*

    error = GRBloadenv(&env, "board.log");
    if (error) {
        printf("ERROR %d GRBloadenv(): %s\n", error, GRBgeterrormsg(env));
        destroyGurobi(env, model, ind, val, obj, vtype);
        return board_sol;
    }

    error = GRBsetintparam(env, GRB_INT_PAR_LOGTOCONSOLE, 0);
    if (error) {
        printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
        destroyGurobi(env, model, ind, val, obj, vtype);
        return board_sol;
    }

    */
/* Create an empty model named "board" *//*

    error = GRBnewmodel(env, &model, "board", 0, NULL, NULL, NULL, NULL, NULL);
    if (error) {
        printf("ERROR %d GRBnewmodel(): %s\n", error, GRBgeterrormsg(env));
        destroyGurobi(env, model, ind, val, obj, vtype);
        return board_sol;
    }

    */
/* Determine which variables should be defined *//*


    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (get_cell_value(board, i, j) != 0) { */
/* Cell is not empty *//*

                continue;
            }

            valid = 0;

            for (v = 1; v <= N; v++) {
                set_cell_value(board, i, j, v);
                if (!is_cell_erroneous(board, i, j)) { */
/* Value v is legal for cell (i,j), assign a variable and save it's index *//*

                    valid = 1; */
/* Indicates we found a possible value for cell (i,j) *//*

                    add_variable(board_sol, i, j, v, index);
                    index++;
                }
            }
            set_cell_value(board, i, j, 0); */
/*Clean the cell, as it was before *//*


            if (!valid) { */
/* An empty cell without any legal values *//*

                add_variable(board_sol, i, j, -1, -1); */
/* Indicates that cell (i,j) is empty (not to mistake with non-empty cells later) *//*

            }
        }
    }

    sol = malloc(index * sizeof(double));
    vtype = malloc(index * sizeof(char));
    obj = malloc(index * sizeof(double));
    validate_memory_allocation("get_LP_solution", sol);
    validate_memory_allocation("get_LP_solution", vtype);
    validate_memory_allocation("get_LP_solution", obj);
    board_sol ->sol = sol;

    */
/* Set the coefficients of the target function & variable types *//*


    if (integer == 1) {
        for (i = 0; i < index; i++) {
            obj[i] = 0; */
/* Target function is zero (we only need to find a feasible solution) *//*

            vtype[i] = GRB_BINARY;
        }
    }

    else {
        for (i = 0; i < index; i++) {
            obj[i] = 1 + rand()%10; */
/* Assign random weight from 1 to 10 to each variable *//*

            vtype[i] = GRB_CONTINUOUS;
        }
    }


    */
/* add variables to model *//*

    error = GRBaddvars(model, index, 0, NULL, NULL, NULL, obj, NULL, NULL,
                       vtype, NULL);
    if (error) {
        printf("ERROR %d GRBaddvars(): %s\n", error, GRBgeterrormsg(env));
        destroyGurobi(env, model, ind, val, obj, vtype);
        return board_sol;
    }

    */
/* Change objective sense to maximization *//*

    error = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
    if (error) {
        printf("ERROR %d GRBsetintattr(): %s\n", error, GRBgeterrormsg(env));
        destroyGurobi(env, model, ind, val, obj, vtype);
        return board_sol;
    }

    */
/* update the model - to integrate new variables *//*

    error = GRBupdatemodel(model);
    if (error) {
        printf("ERROR %d GRBupdatemodel(): %s\n", error, GRBgeterrormsg(env));
        destroyGurobi(env, model, ind, val, obj, vtype);
        return board_sol;
    }

    */
/* Set constraints *//*


    */
/* cell constraints (exactly one value in each cell) *//*

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (get_variable_index(board_sol, i, j, 1) == -1) { */
/* The cell is not empty *//*

                continue;
            }

            vars_in_constraint = 0; */
/* Count how many variables participate in each constraint *//*


            for (v = 1; v <= N; v++) {
                if (get_variable_index(board_sol, i, j, v) == -2) { */
/* value v is not available for this cell (e.g. doesn't have a variable) *//*

                    continue;
                }
                ind[vars_in_constraint] = get_variable_index(board_sol, i, j, v);
                val[vars_in_constraint] = 1.0;
                vars_in_constraint++;
            }

            if (vars_in_constraint == 0) {
                */
/* An empty cell with no legal values - means the board is unsolveable (constraint of sum of variables on cell (i,j) == 1 can't be fulfilled *//*

                destroyGurobi(env, model, ind, val, obj, vtype);
                board_sol->solved = 0; */
/* There is no solution *//*

                return board_sol;
            }

            constraints++;

            error = GRBaddconstr(model, vars_in_constraint, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) {
                printf("ERROR %d 1st GRBaddconstr(): %s\n", error, GRBgeterrormsg(env));
                destroyGurobi(env, model, ind, val, obj, vtype);
                return board_sol;
            }
        }
    }

    */
/* row constraints *//*


    for (v = 1; v <= N; v++) {
        for (i = 0; i < N; i++) {

            vars_in_constraint = 0;

            for (j = 0; j < N; j++) {
                if (get_cell_value(board, i, j) == v) {
                    found_val = 1; */
/* Indicates we found value v in row i, therefore no need to set this constraint *//*

                    break;
                }

                if (get_variable_index(board_sol, i, j, v) == -1 || get_variable_index(board_sol, i, j, v) == -2) { */
/* Cell (i,j) already contains a number, or value v is not legal for (i,j) *//*

                    continue;
                }

                ind[vars_in_constraint] = get_variable_index(board_sol, i, j, v);
                val[vars_in_constraint] = 1.0;
                vars_in_constraint++;

            }

            if (found_val == 1) {
                found_val = 0;
                continue;
            }

            if (vars_in_constraint == 0) {
                continue;
            }

            constraints++;
            error = GRBaddconstr(model, vars_in_constraint, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) {
                printf("ERROR %d 1st GRBaddconstr(): %s\n", error,
                       GRBgeterrormsg(env));
                destroyGurobi(env, model, ind, val, obj, vtype);
                return board_sol;
            }
        }
    }

    */
/* column constraints *//*


    for (v = 1; v <= N; v++) {
        for (j = 0; j < N; j++) {

            vars_in_constraint = 0;

            for (i = 0; i < N; i++) {
                if (get_cell_value(board, i, j) == v) {
                    found_val = 1; */
/* Indicates we found value v in column j, therefore no need to set a constraint *//*

                    break;
                }

                if (get_variable_index(board_sol, i, j, v) == -1 || get_variable_index(board_sol, i, j, v) == -2) { */
/* Cell (i,j) already contains a number, or value v is not legal for (i,j) *//*

                    continue;
                }

                ind[vars_in_constraint] = get_variable_index(board_sol, i, j, v);
                val[vars_in_constraint] = 1.0;
                vars_in_constraint++;
            }

            if (found_val == 1) {
                found_val = 0;
                continue;
            }

            if (vars_in_constraint == 0) {
                continue;
            }

            constraints++;

            error = GRBaddconstr(model, vars_in_constraint, ind, val, GRB_EQUAL, 1.0, NULL);
            if (error) {
                printf("ERROR %d 1st GRBaddconstr(): %s\n", error,
                       GRBgeterrormsg(env));
                destroyGurobi(env, model, ind, val, obj, vtype);
                return board_sol;
            }
        }
    }

    */
/* block constraints *//*


    for (k = 0; k < n; k++) { */
/* k and l iterate over blocks, i and j over cells in each block *//*

        for (l = 0; l < m; l++) {
            for (v = 1; v <= N; v++) {
                vars_in_constraint = 0;
                for (i = k * m; i < (k + 1) * m; i++) {
                    for (j = l * n; j < (l + 1) * n; j++) {
                        if (get_cell_value(board, i, j) == v) {
                            found_val = 1; */
/* Indicates we found value v in block (i,j), therefore no need to set a constraint *//*

                            break;
                        }

                        if (get_variable_index(board_sol, i, j, v) == -1
                            || get_variable_index(board_sol, i, j, v) == -2) { */
/* Cell (i,j) already contains a number, or value v is not legal for (i,j) *//*

                            continue;
                        }

                        ind[vars_in_constraint] = get_variable_index(board_sol, i, j, v);
                        val[vars_in_constraint] = 1.0;
                        vars_in_constraint++;
                    }
                }

                if (found_val == 1) {
                    found_val = 0;
                    continue;
                }

                if (vars_in_constraint == 0) {
                    continue;
                }

                constraints++;
                error = GRBaddconstr(model, vars_in_constraint, ind, val, GRB_EQUAL, 1.0, NULL);
                if (error) {
                    printf("ERROR %d 1st GRBaddconstr(): %s\n", error,
                           GRBgeterrormsg(env));
                    return board_sol;
                }

            }
        }
    }

    */
/* Optimize model - need to call this before calculation *//*

    error = GRBoptimize(model);
    if (error) {
        printf("ERROR %d GRBoptimize(): %s\n", error, GRBgeterrormsg(env));
        destroyGurobi(env, model, ind, val, obj, vtype);
        return board_sol;
    }

    */
/* Write model to 'board.lp' - this is not necessary but very helpful *//*

    error = GRBwrite(model, "board.lp");
    if (error) {
        printf("ERROR %d GRBwrite(): %s\n", error, GRBgeterrormsg(env));
        destroyGurobi(env, model, ind, val, obj, vtype);
        return board_sol;
    }

    */
/* Get solution information *//*


    error = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &optimstatus);
    if (error) {
        printf("ERROR %d GRBgetintattr(): %s\n", error, GRBgeterrormsg(env));
        destroyGurobi(env, model, ind, val, obj, vtype);
        return board_sol;
    }

    */
/* get the objective - the optimal result of the function *//*

    error = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &objval);
    if (error) {
        destroyGurobi(env, model, ind, val, obj, vtype);
        board_sol->solved = 0;
        */
/*printf("ERROR %d GRBgettdblattr(): %s\n", error, GRBgeterrormsg(env));*//*

        return board_sol;
    }

    */
/* get the solution - the assignment to each variable *//*

    */
/* 3-- number of variables, the size of "sol" should match *//*

    error = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, index, sol);
    if (error) {
        printf("ERROR %d GRBgetdblattrarray(): %s\n", error,
               GRBgeterrormsg(env));
        destroyGurobi(env, model, ind, val, obj, vtype);
        return board_sol;
    }

    */
/* print results *//*

    */
/*printf("\nOptimization complete\n");*//*


    */
/* solution found *//*

    if (optimstatus == GRB_OPTIMAL) {
        board_sol->solved = 1;
    }

        */
/* no solution found *//*

    else if (optimstatus == GRB_INF_OR_UNBD) {
        board_sol->solved = 0;
    }
        */
/* error or calculation stopped *//*

    else {
        printf("Optimization was stopped early\n");
    }

    */
/* IMPORTANT !!! - Free model and environment *//*

    destroyGurobi(env, model, ind, val, obj, vtype);
    board_sol->sol = sol;

    return board_sol;
}
*/
