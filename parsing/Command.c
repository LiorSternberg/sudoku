#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Command.h"
#include "../MemoryError.h"


Command* create_command() {
    Command *command = malloc(sizeof(Command));
    validate_memory_allocation("create_command", command);

    command->type = empty;
    command->format = NULL;
    command->modes = 0;
    command->valid = true;
    command->error_message = NULL;
    command->error_level = 0;
    command->data.solve = NULL;
    command->data.edit = NULL;
    command->data.mark_errors = NULL;
    command->data.set = NULL;
    command->data.guess = NULL;
    command->data.generate = NULL;
    command->data.save = NULL;
    command->data.hint = NULL;
    command->data.guess_hint = NULL;

    return command;
}

void destroy_command(Command* command) {
    free(command->data.solve);
    free(command->data.edit);
    free(command->data.mark_errors);
    free(command->data.set);
    free(command->data.guess);
    free(command->data.generate);
    free(command->data.save);
    free(command->data.hint);
    free(command->data.guess_hint);
    free(command->error_message);
    free(command);
}


void invalidate(Command *command, char *error_message, int error_level) {
    if (command->valid == false && command->error_level <= error_level) {
        return;
    }

    command->valid = false;
    command->error_message = error_message;
    command->error_level = error_level;
}

