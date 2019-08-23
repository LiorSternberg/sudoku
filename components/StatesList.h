#ifndef FINAL_PROJECT_STATESLIST_H
#define FINAL_PROJECT_STATESLIST_H

#include "List.h"

typedef struct {
    List *moves;
} States;

States* create_states_list();

void destroy_states_list(States *states);

void clear_states_list(States *states);

void clear_redo(States *states);

void add_new_move(States *states);

void add_change(States *states, int row, int column, int prev_val, int new_val);

#endif
