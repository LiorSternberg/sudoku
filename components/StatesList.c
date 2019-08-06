#include <stdlib.h>

#include "StatesList.h"
#include "../MemoryError.h"
#include "Move.h"


States* create_states_list() {
    States *states = malloc(sizeof(States));
    validate_memory_allocation("create_states_list", states);

    states->moves = create_list();

    return states;
}

void destroy_states_list(States *states) {
    Move *move;
    while ((move = remove_last(states->moves)) != NULL) {
        destroy_move(move);
    }
    destroy_list(states->moves);
    free(states);
}
