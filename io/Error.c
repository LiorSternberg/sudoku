#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "../MemoryError.h"

Error* create_error() {
    Error *error = malloc(sizeof(Error));
    validate_memory_allocation("create_error", error);

    error->message = NULL;
    error->level = no_error;
    error->_message_allocated = false;
    return error;
}

void set_error(Error *error, char *message, ErrorLevel level, bool message_allocated) {
    /* free the existing error message first if needed */
    if (error->_message_allocated) {
        free(error->message);
        error->_message_allocated = false;
    }

    error->message = message;
    error->level = level;
    error->_message_allocated = message_allocated;
}

void destroy_error(Error* error) {
    if (error->_message_allocated) {
        free(error->message);
    }
    free(error);
}
