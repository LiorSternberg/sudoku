#include "GameManager.h"
#include "UserHandler.h"

void dispose_of_command_on_error(Command *command) {
    announce_error(command->error);
    destroy_command(command);
}

void play_turn(Game *game, Command *command) {
    command = create_command();
    get_user_command(game, command);

    if (!is_valid(command)) {
        dispose_of_command_on_error(command);
        return;
    }

    command->_play(command, game);
    if (!is_valid(command)) {
        dispose_of_command_on_error(command);
        return;
    }

    destroy_command(command);
}

