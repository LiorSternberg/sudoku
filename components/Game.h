#ifndef FINAL_PROJECT_GAME_H
#define FINAL_PROJECT_GAME_H

#include <stdbool.h>
#include "StatesList.h"

typedef enum {
    edit_mode = 1,
    solve_mode = 2,
    init_mode = 4
} GameMode;

typedef struct {
    GameMode mode;
    bool mark_errors;
    States *states;
} Game;

Game* create_game();

void destroy_game(Game *game);


#endif
