#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "GameManager.h"
#include "io/Parser.h"
#include "io/validators.h"
#include "io/Printer.h"

#define MAX_COMMAND_LEN 256
#define INPUT_LEN (MAX_COMMAND_LEN + 2)

#define COMMAND_TOO_LONG_ERROR "Error: command is too long.\n"
#define COMMAND_NOT_READ_ERROR "Error: command could not be read.\n"


void handle_eof(Game *game, Command *command) {
    if (feof(stdin)) {
        announce_exit();
        destroy_command(command);
        destroy_game(game);
        exit(0);
    }
}

void get_user_command(Game *game, Command *command) {
    char raw_command[INPUT_LEN];
    char *res;

    printf("\nPlease enter a command:\n");
    do {
        memset(raw_command, 0, INPUT_LEN);
        res = fgets(raw_command, INPUT_LEN, stdin);
        handle_eof(game, command);
        if (res == NULL) {
            invalidate(command, COMMAND_NOT_READ_ERROR, invalid_command_length, false);
            fflush(stdin);
            return;
        }

        if (raw_command[MAX_COMMAND_LEN] != 0) {
            invalidate(command, COMMAND_TOO_LONG_ERROR, invalid_command_length, false);
            fflush(stdin);
            return;
        }

        parse_command(raw_command,  command, game);
    } while (command->type == empty && is_valid(command));

    if (command->type == empty) {
        return;
    }

    validate_command(command, game);
}

void dispose_of_command_on_error(Command *command) {
    announce_error(command->error);
    destroy_command(command);
}

void play_turn(Game *game) {
    Command *command = create_command();
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

