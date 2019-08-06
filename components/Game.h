#ifndef FINAL_PROJECT_GAME_H
#define FINAL_PROJECT_GAME_H

#include <stdbool.h>
#include "StatesList.h"

typedef enum { edit_mode, solve_mode, init_mode } GameMode;

typedef struct {
    GameMode mode;
    bool mark_errors;
    States *states;
} Game;

Game* create_game();

void destroy_game(Game *game);


#endif
