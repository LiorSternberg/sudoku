#include <stdlib.h>

#include "Move.h"
#include "../MemoryError.h"


Change* create_change(int row, int column, int prev_value, int new_value) {
    Change *change = malloc(sizeof(Change));
    validate_memory_allocation("create_change", change);

    change->row = row;
    change->actual_row = row - 1;
    change->column = column;
    change->actual_column = column - 1;
    change->value = new_value;
    change->prev_value = prev_value;

    return change;
}

void destroy_change(Change *change) {
    free(change);

}

Move* create_move() {
    Move *move = malloc(sizeof(Move));
    validate_memory_allocation("create_move", move);

    move->changes = create_list();

    return move;

}

void destroy_move(Move *move) {
    Change *change;
    while ((change = remove_last(move->changes)) != NULL) {
        destroy_change(change);
    }
    destroy_list(move->changes);
    free(move);
}

