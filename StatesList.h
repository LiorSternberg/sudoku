#ifndef FINAL_PROJECT_STATESLIST_H
#define FINAL_PROJECT_STATESLIST_H

#include "Board.h"

typedef struct State_ {
    Board* board;
    struct State_* next;
    struct State_* prev;
} State;


typedef struct {
    State* head;
} StatesList;

#endif
