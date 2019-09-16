#ifndef FINAL_PROJECT_SOLVER_H
#define FINAL_PROJECT_SOLVER_H


#include <stdbool.h>
#include "../components/Board.h"
#include "../components/StatesList.h"

/** solver:
 *
 * This module is responsible for the logic of the ILP and LP algorithms using
 * Gurobi. It contains multiple configurations of solving, each to be used for
 * a slightly different purpose.
 */

/* The different types of variables supported:
 *  - continuous for LP
 *  - integer for ILP
 *  */
typedef enum {
    continuous,
    integer
} VariableType;

/* The different types of solutions suppported:
 *  - cell_hint will only fill the SolutionData for a single cell
 *  - solve_board will fill the given board with the solution
 *  */
typedef enum {
    cell_hint,
    solve_board
} SolutionType;

/* SolutionData to be filled in case only a single cell hint is required. */
typedef struct {
    int row;
    int column;
    double *guesses;
} SolutionData;

/**
 * The main ILP/LP model solving function. Solves the given board using LP/ILP based
 * on the variable type, and fills the board or the SolutionData based on the given
 * solution type and threshold. In case where a states list is provided, and the
 * solution type supports it, also updates the state list according to the solution.
 * @param board: the board to solve.
 * @param states: a states list to update with the solution. can be NULL.
 * @param var_type: the type of variables (determines ILP/LP, see VariableType).
 * @param sol_type: the type of solution (see SolutionType).
 * @param data: the solution data to be filled in case of a cell_hint solution.
 * @param threshold: the threshold to be used in case of running LP solving, with
 * the solve_board option.
 * @return: true if the model solving succeeded, and a solution was updated, and false
 * otherwise.
 */
bool gurobi_solver(Board *board, States *states, VariableType var_type, SolutionType sol_type,
                   SolutionData *data, double threshold);


#endif
