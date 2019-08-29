#include <stdlib.h>
#include "LP.h"
#include "../MemoryError.h"

#define UNUSED(x) (void)(x)


void guess_solution(Board *board, int threshold) {
    UNUSED(board);
    UNUSED(threshold);
}

int* get_cell_guesses(Board *board, int row, int column) {
    int *guesses = calloc(board->dim, sizeof(int));
    validate_memory_allocation("create_stack", guesses);

    /* TODO: actually implement this, and then remove the UNUSED :) */
    UNUSED(row);
    UNUSED(column);

    return guesses;
}