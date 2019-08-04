#ifndef FINAL_PROJECT_GAME_H
#define FINAL_PROJECT_GAME_H

#include <stdbool.h>
#include "StatesList.h"

typedef enum { edit, solve, init } GameMode;

typedef struct {
    GameMode mode;
    bool mark_errors;
    StatesList *states;
} Game;


#endif
