#include <stdio.h>
#include <stdlib.h>

#include "LP.h"
#include "../MemoryError.h"
#include "solver.h"

#define UNUSED(x) (void)(x)


bool guess_solution(Board *board, States *states, double threshold) {
    return gurobi_solver(board, states, continuous, solve_board, NULL, threshold);
}

double* get_cell_guesses(Board *board, int row, int column) {
    SolutionData *data = malloc(sizeof(SolutionData));
    double *guesses;
    validate_memory_allocation("get_cell_guesses", data);

    data->row = row;
    data->column = column;
    data->guesses = NULL;

    if (!gurobi_solver(board, NULL, continuous, cell_hint, data, 1.0)) {
        free(data);
        return NULL;
    }
    guesses = data->guesses;
    free(data);
    return guesses;
}

