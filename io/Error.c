#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "../MemoryError.h"

Error* create_empty_error() {
    Error *error = malloc(sizeof(Error));
    validate_memory_allocation("create_empty_error", error);

    error->message = NULL;
    error->level = no_error;
    return error;
}

Error* create_error(char *message, ErrorLevel level) {
    Error *error = malloc(sizeof(Error));
    validate_memory_allocation("create_error", error);

    error->message = message;
    error->level = level;
    return error;
}

void destroy_error(Error* error) {
    free(error->message);
    free(error);
}
