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

int* get_cell_guesses(const Board *board, int row, int column) {
    int *guesses = calloc(board->dim, sizeof(int));
    validate_memory_allocation("create_stack", guesses);

    /* TODO: actually implement this, and then remove the UNUSED :) */
    UNUSED(row);
    UNUSED(column);

    return guesses;
}