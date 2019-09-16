#include <stdlib.h>
#include <stdio.h>

#include "GameManager.h"
#include "io/Printer.h"
#include "logic/random.h"

int main() {
    Game *game = create_game();
    initialize_random();
    announce_game_start();

    while (!game->over) {
        play_turn(game);
    }

    destroy_game(game);
    return 0;
}