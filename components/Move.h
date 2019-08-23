#ifndef FINAL_PROJECT_MOVE_H
#define FINAL_PROJECT_MOVE_H

#include "List.h"

typedef struct {
    int row;
    int actual_row;
    int column;
    int actual_column;
    int value;
    int prev_value;
} Change;

typedef struct {
    List *changes;
} Move;

Change* create_change(int row, int column, int prev_value, int new_value);

void destroy_change(Change *change);

Move* create_move();

void destroy_move(Move *move);

#endif
