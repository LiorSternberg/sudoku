#include <stdlib.h>

#include "Game.h"
#include "../MemoryError.h"

Game* create_game() {
    Game *game = malloc(sizeof(Game));
    validate_memory_allocation("create_game", game);

    game->mark_errors=true;
    game->mode=init_mode;
    game->states=create_states_list();

    return game;

}

void destroy_game(Game *game) {
    destroy_states_list(game->states);
    free(game);
}
