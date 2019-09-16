#include <stdlib.h>
#include <stdio.h>

#include "GameManager.h"
#include "io/Printer.h"
#include "logic/random.h"

/** main:
 *
 * Runs the game - creates a new game, announces it's starting, and plays turns
 * until the user wishes to quit.
 */


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