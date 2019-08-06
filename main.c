#include <stdlib.h>
#include <stdio.h>
#include "parsing/Parser.h"
#include "UserHandler.h"

int main() {
    Command *command;
    Game *game = create_game();

    announce_game_start();

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
        command = create_command();
        get_user_command(game, command);

        if (!command->valid) {
            printf("%s\n", command->error_message);
        }
        destroy_command(command);
    }
#pragma clang diagnostic pop

    destroy_game(game);
    return 0;
}