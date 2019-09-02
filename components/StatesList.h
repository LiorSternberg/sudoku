#ifndef FINAL_PROJECT_STATESLIST_H
#define FINAL_PROJECT_STATESLIST_H

#include "List.h"
#include "Move.h"
#include "Board.h"

typedef struct {
    List *moves;
} States;

States* create_states_list();

void destroy_states_list(States *states);

void clear_states_list(States *states);

void add_new_move(States *states);

Change* add_change(States *states, int row, int column, int prev_val, int new_val);

void clear_redo(States *states);

void set_change(Board *board, Change *change);

void reset_change(Board *board, Change *change);

void make_change(Board *board, States *states, int row, int column, int new_value);

#endif
