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
    List changes;
} Move;

#endif
