#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Command.h"
#include "../MemoryError.h"


Command* create_command() {
    Command *command = malloc(sizeof(Command));
    validate_memory_allocation("create_command", command);

    command->valid=true;
    command->error_message=NULL;
    command->type=empty;

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
    free(command);
}


void invalidate(Command *command, char *error_message) {
    if (command->valid == false) {
        return;
    }

    command->valid=false;
    command->error_message=error_message;
}

