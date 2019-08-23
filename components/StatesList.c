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

void clear_states_list(States *states) {
    Move *move;
    while ((move = remove_last(states->moves)) != NULL) {
        destroy_move(move);
    }
}

void destroy_states_list(States *states) {
    clear_states_list(states);
    destroy_list(states->moves);
    free(states);
}

void clear_redo(States *states) {
    Move *move;
    while (states->moves->head != states->moves->end) {
        move = remove_last(states->moves);
        destroy_move(move);
    }
}

void add_new_move(States *states) {
    Move *move = create_move();
    add(states->moves, move);
}

void add_change(States *states, int row, int column, int prev_val, int new_val) {
    Change *change = create_change(row, column, prev_val, new_val);
    Move *current_move = get_current_item(states->moves);
    add(current_move->changes, change);
}

