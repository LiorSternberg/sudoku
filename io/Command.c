#include <stdio.h>
#include <stdlib.h>

#include "Command.h"
#include "../MemoryError.h"


Command* create_command() {
    Command *command = malloc(sizeof(Command));
    validate_memory_allocation("create_command", command);

    command->type = empty;
    command->format = NULL;
    command->modes = 0;
    command->error = create_empty_error();
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
    destroy_error(command->error);
    free(command);
}


void invalidate(Command *command, char *error_message, int error_level) {
    if (command->error->level <= error_level) {
        return;
    }

    command->error->message = error_message;
    command->error->level = error_level;
}

