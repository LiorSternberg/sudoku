#include <stdlib.h>
#include <stdio.h>
#include "io/Parser.h"
#include "UserHandler.h"
#include "io/validators.h"
#include "io/Serializer.h"
#include "GameManager.h"

int main() {
    Command *command;
    Game *game = create_game();
    announce_game_start();

    /* Ty runnning:
     *
     * solve ../test_files/boards/board_2_5_with_fixed.txt
     * solve ../test_files/boards/board_2_2_almost_full.txt
     *
     */

    while (true) {
        play_turn(game, command);
    }

    return 0;
}