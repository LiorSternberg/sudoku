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
    Error *error = create_error();
    announce_game_start();
//    game->board = load_from_file("../test_files/boards/board_2_5_with_fixed.txt", error);
//    save_to_file(game, "../test_files/boards/test.txt", error);
//    announce_error(error);
//    ../test_files/boards/board_2_2_almost_full.txt

    while (true) {
        play_turn(game, command);
    }

    return 0;
}