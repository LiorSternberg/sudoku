#include <stdlib.h>

#include "Move.h"
#include "../MemoryError.h"


Change* create_change(int row, int column, int prev_val, int new_val) {
    Change *change = malloc(sizeof(Change));
    validate_memory_allocation("create_change", change);

    change->row=row;
    change->col=column;
    change->val=new_val;
    change->prev_val=prev_val;

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

