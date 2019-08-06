#ifndef FINAL_PROJECT_MOVE_H
#define FINAL_PROJECT_MOVE_H

#include "List.h"

typedef struct {
    int row;
    int col;
    int val;
    int prev_val;
} Change;

typedef struct {
    List *changes;
} Move;

Change* create_change(int row, int column, int prev_val, int new_val);

void destroy_change(Change *change);

Move* create_move();

void destroy_move(Move *move);

#endif
