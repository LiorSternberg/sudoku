#include <stdlib.h>
#include <stdio.h>
#include "io/Parser.h"
#include "UserHandler.h"
#include "io/validators.h"

int main() {
    Command *command;
    Game *game = create_game();

    announce_game_start();

    while (true) {
        command = create_command();
        get_user_command(game, command);

        if (command->error->level < no_error) {
            announce_error(command->error);
        }
        destroy_command(command);
    }

    destroy_game(game);
    return 0;
}