#include <stdlib.h>
#include <stdio.h>
#include "parsing/Parser.h"
#include "UserHandler.h"
#include "parsing/validators.h"

int main() {
    Command *command;
    Game *game = create_game();

    announce_game_start();

    while (true) {
        command = create_command();
        get_user_command(game, command);

        if (!command->valid) {
            printf("%s\n", command->error_message);
        }
        destroy_command(command);
    }

    destroy_game(game);
    return 0;
}