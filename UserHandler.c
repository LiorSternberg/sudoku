#include <stdio.h>
#include <stdlib.h>
#include "UserHandler.h"
#include "io/Command.h"
#include "io/Parser.h"
#include "io/validators.h"


#define MAX_COMMAND_LEN 256
#define INPUT_LEN (MAX_COMMAND_LEN + 2)

#define COMMAND_TOO_LONG_ERROR "Error: command is too long\n"

#define HEADLINE \
"         _____           _       _           ___  ___          _                     \n" \
"        /  ___|         | |     | |          |  \\/  |         | |                    \n" \
"        \\ `--. _   _  __| | ___ | | ___   _  | .  . | __ _  __| |_ __   ___  ___ ___ \n" \
"         `--. \\ | | |/ _` |/ _ \\| |/ / | | | | |\\/| |/ _` |/ _` | '_ \\ / _ \\/ __/ __|\n" \
"        /\\__/ / |_| | (_| | (_) |   <| |_| | | |  | | (_| | (_| | | | |  __/\\__ \\__ \\\n" \
"        \\____/ \\__,_|\\__,_|\\___/|_|\\_\\\\__,_| \\_|  |_/\\__,_|\\__,_|_| |_|\\___||___/___/\n" \
"                                                                                     \n\n" \


void handle_eof(Game *game) {
    if (feof(stdin)) {
//        announce_exit();
        destroy_game(game);
        exit(0);
    }
}

void get_user_command(Game *game, Command *command) {
    char raw_command[INPUT_LEN] = {0};

    printf("Please enter a command:\n");
    fgets(raw_command, INPUT_LEN, stdin);
    if (raw_command[MAX_COMMAND_LEN] != 0) {
        invalidate(command, COMMAND_TOO_LONG_ERROR, invalid_command_length);
        return;
    }

    parse_command(raw_command,  command, game);
    if (command->type == empty) {
        return;
    }

    validate_command(command, game);
}


void announce_game_start() {
    printf("%s Welcome! Let the Games Begin!\n\n", HEADLINE);
}

void announce_error(Error *error) {
    printf("%s\n", error->message);
}