#include <stdio.h>
#include <stdlib.h>
#include "UserHandler.h"
#include "parsing/Command.h"
#include "parsing/Parser.h"
#include "parsing/validation.h"


#define MAX_COMMAND_LEN 256
#define INPUT_LEN (MAX_COMMAND_LEN + 2)

#define COMMAND_TOO_LONG_ERROR "Error: command is too long\n"



void get_user_command(Game *game, Command *command) {
    char raw_command[INPUT_LEN] = {0};

    fgets(raw_command, INPUT_LEN, stdin);
    if (raw_command[MAX_COMMAND_LEN] != 0) {
        invalidate(command, COMMAND_TOO_LONG_ERROR);
        return;
    }

    parse_command(raw_command,  command);
    if (!command->valid) {
        return;
    }

    validate_command(command, game);
}

