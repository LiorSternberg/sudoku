#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "../MemoryError.h"

Error* create_error() {
    Error *error = malloc(sizeof(Error));
    validate_memory_allocation("create_error", error);

    error->message = NULL;
    error->level = no_error;
    return error;
}

void set_error(Error *error, char *message, ErrorLevel level) {
    error->message = message;
    error->level = level;
}

void destroy_error(Error* error) {
    /*free(error->message);*/
    free(error);
}
