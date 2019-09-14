#ifndef FINAL_PROJECT_SOLVER_H
#define FINAL_PROJECT_SOLVER_H


#include <stdbool.h>
#include "../components/Board.h"
#include "../components/StatesList.h"

typedef enum {
    continuous,
    integer
} VariableType;

typedef enum {
    cell_hint,
    solve_board
} SolutionType;

typedef struct {
    int row;
    int column;
    double *guesses;
} SolutionData;

bool gurobi_solver(Board *board, States *states, VariableType var_type, SolutionType sol_type,
                   SolutionData *data, double threshold);


#endif
