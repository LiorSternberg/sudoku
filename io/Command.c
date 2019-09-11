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
    command->error = create_error();
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
    if (command->type == solve && command->data.solve != NULL) {
        free(command->data.solve->path);
        free(command->data.solve);
    }
    else if (command->type == edit && command->data.edit != NULL) {
        free(command->data.edit->path);
        free(command->data.edit);
    }
    else if (command->type == save && command->data.save != NULL) {
        free(command->data.save->path);
        free(command->data.save);
    }
    else if (command->type == mark_errors) {
        free(command->data.mark_errors);
    }
    else if (command->type == set) {
        free(command->data.set);
    }
    else if (command->type == guess) {
        free(command->data.guess);
    }
    else if (command->type == generate) {
        free(command->data.generate);
    }
    else if (command->type == hint) {
        free(command->data.hint);
    }
    else if (command->type == guess_hint) {
        free(command->data.guess_hint);
    }
    destroy_error(command->error);
    free(command);
}


void invalidate(Command *command, char *error_message, int error_level, bool message_allocated) {
    if ((signed int) command->error->level <= error_level) {
        return;
    }

    set_error(command->error, error_message, error_level, message_allocated);
}

bool is_valid(Command *command) {
    return command->error->level >= no_error;
}
