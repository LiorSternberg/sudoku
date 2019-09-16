#include <stdlib.h>
#include <stdio.h>

#include "GameManager.h"
#include "io/Printer.h"
#include "logic/ILP.h"
#include "io/Serializer.h"
#include "logic/random.h"

int main() {
    Game *game = create_game();
    initialize_random();

    announce_game_start();

    /* Ty running:
     *
     * solve ../test_files/boards/board_2_5_with_fixed.txt
     * solve ../test_files/boards/board_2_2_almost_full.txt
     * solve ../test_files/boards/board_2_2_four_solutions_with_fixed.txt
     * solve ../test_files/boards/board_5_5_two_solutions.txt
     * solve test_files/boards/board_5_5_two_solutions.txt
     * solve test_files/boards/board_2_5_with_fixed.txt
     * solve test_files/boards/board_2_2_invalid.txt
     */

    while (!game->over) {
        play_turn(game);
    }

    destroy_game(game);
    return 0;
}