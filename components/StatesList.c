#include <stdlib.h>

#include "StatesList.h"
#include "../MemoryError.h"


States* create_states_list() {
    States *states = malloc(sizeof(States));
    validate_memory_allocation("create_states_list", states);

    states->moves = create_list();

    /* add dummy first move to allow for more convenient work
     * with the states list */
    add_new_move(states);

    return states;
}

void clear_states_list(States *states) {
    Move *move;

    /* clear all moves but the dummy */
    while (has_prev(states->moves)) {
        move = remove_last(states->moves);
        destroy_move(move);
    }
}

void destroy_states_list(States *states) {
    Move *dummy;
    clear_states_list(states);
    dummy = remove_last(states->moves);
    destroy_move(dummy);
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
    clear_redo(states);
    add(states->moves, move);
    next(states->moves);
}

Change* add_change(States *states, int row, int column, int prev_val, int new_val) {
    Change *change = create_change(row, column, prev_val, new_val);
    Move *current_move = get_current_item(states->moves);
    add(current_move->changes, change);
    return change;
}

void set_change(Board *board, Change *change) {
    set_cell_value(board, change->actual_row, change->actual_column, change->value);
}

void reset_change(Board *board, Change *change) {
    set_cell_value(board, change->actual_row, change->actual_column, change->prev_value);
}

void make_change(Board *board, States *states, int row, int column, int new_value) {
    int actual_row = row - 1, actual_column = column - 1;
    int prev_value = get_cell_value(board, actual_row, actual_column);
    Change *change = add_change(states, row, column, prev_value, new_value);

    set_change(board, change);
}
