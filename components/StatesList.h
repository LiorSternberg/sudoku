#ifndef FINAL_PROJECT_STATESLIST_H
#define FINAL_PROJECT_STATESLIST_H

#include "List.h"

typedef struct {
    List *moves;
} States;

States* create_states_list();

void clear_states_list(States *states);

void destroy_states_list(States *states);


#endif
