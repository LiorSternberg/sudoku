#include "../components/Board.h"
#include "gurobi_c.h"

#ifndef FINAL_PROJECT_LP_H
#define FINAL_PROJECT_LP_H

typedef struct {
    int row;
    int column;
    int val;
    int var_index;
} Variable;

/*
 * LPSol struct holds the information received from "get_LP_solution".
 * "map_by_cell" is an array of Lists (node's item is Variable), the index (i, j) represents the variables list of the cell (i,j).
 * "sol" holds the solution values of the variables.
 * "solved" is set to 1 if LP found a solution to the board, 0 if there is no solution, and -1 if the LP solver encoutered an error.
 */
typedef struct {
    int dim;
    List **map_by_cell;
    double *sol;
    int solved;
} LPSol;

/* Guesses a solution for the given board using LP (not ILP!), and fills the
 * board so that only guesses over the threshold are considered.
 *
 * Note: if more than one possible value is found, randomly chooses a value,
 *       using the scores as weights for the random choice. */
void guess_solution(Board *board, int threshold);

/* Returns an array of scores that represents the possible values and their
 * score for the given cell (size of the array is always the board dimension).
 * For example, the array [0, 0.1, 0.33, 0, 0.2, ...] means that the value 2 has a
 * score of 0.1, and the value 3 has a score of 0.33, and so on. */
int* get_cell_guesses(Board *board, int row, int column);


/*
 * Solves the board using linear programming and returns a LPSol struct with the solution info.
 * The parameter "integer" - determines whether the solver will use LP (0) or ILP (1).
 */
LPSol* get_LP_solution(Board *board, int integer);


Variable* create_variable(int row, int column, int val, int var_index);

/* Assigns a variable to (row, col) List in "map_by_cell" field with value val and stores it's index */
void add_variable(LPSol *board_sol, int row, int column, int val, int index);

/* Returns the "var_index" of the variable Xijv */
int get_variable_index(LPSol *board_sol, i, j, v);

void destroy_variable(Variable *var);

LPSol* create_LP_sol(int dim);

void destroy_LP_sol(LPSol *board_sol);

void destroyGurobi(GRBenv *env, GRBmodel *model, int *ind, double *val, double *obj, char *vtype);
