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
    State* end;
} StatesList;


void add(StatesList* states, Board* board);

int next(StatesList* states);

int prev(StatesList* states);

void clear_all(StatesList* states);

void clear_next(StatesList* states);


#endif
