#include <stdio.h>
#include <stdlib.h>

#include "GameManager.h"
#include "io/Parser.h"
#include "io/validators.h"
#include "io/Printer.h"

#define MAX_COMMAND_LEN 256
#define INPUT_LEN (MAX_COMMAND_LEN + 2)

#define COMMAND_TOO_LONG_ERROR "Error: command is too long.\n"


void handle_eof(Game *game, Command *command) {
    if (feof(stdin)) {
        announce_exit();
        destroy_command(command);
        destroy_game(game);
        exit(0);
    }
}

void get_user_command(Game *game, Command *command) {
    char raw_command[INPUT_LEN] = {0};

    printf("\nPlease enter a command:\n");
    fgets(raw_command, INPUT_LEN, stdin);
    handle_eof(game, command);
    if (raw_command[MAX_COMMAND_LEN] != 0) {
        invalidate(command, COMMAND_TOO_LONG_ERROR, invalid_command_length, false);
        fflush(stdin);
        return;
    }

    parse_command(raw_command,  command, game);
    if (command->type == empty) {
        return;
    }

    validate_command(command, game);
}

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

    if (command->type == empty) {
        destroy_command(command);
        return;
    }

    command->_play(command, game);
    if (!is_valid(command)) {
        dispose_of_command_on_error(command);
        return;
    }

    destroy_command(command);
}

