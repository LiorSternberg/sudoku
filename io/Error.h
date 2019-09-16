#ifndef FINAL_PROJECT_ERROR_H
#define FINAL_PROJECT_ERROR_H

#include <stdbool.h>

/** Error:
 *
 * A structure that hold information about the command's error status and message.
 * When updated, the level of the error is considered, so that the most critical
 * error is always the one that is kept.
 */


/* The possible error levels, by order */

typedef enum {
    invalid_command_length,
    invalid_command_name,
    invalid_command_for_mode,
    invalid_num_of_args,
    invalid_arg_range,
    invalid_state,
    execution_failure,
    no_error
} ErrorLevel;



typedef struct  {
    char* message;
    ErrorLevel level;
    bool _message_allocated;
} Error;


/**
 * Creates a new empty error.
 * @return: the new error that was created.
 */
Error* create_error();

/**
 * Set an error to a certain error level with an appropriate message.
 * Note that if the error is already set to a lower level (more critical) then
 * the current error message will be discarded, and the error won't change.
 * @param error: the error to update.
 * @param message: the error message to set to the error.
 * @param level: the error level to set the error to.
 * @param message_allocated: true if the message was allocated dynamic memory
 * and will need to be freed eventually, and false otherwise.
 */
void set_error(Error *error, char *message, ErrorLevel level, bool message_allocated);

/* Free all the resources used by the error */
/**
 * Destroys the given error (frees all related memory).
 * @param error: the error to destroy.
 */
void destroy_error(Error* error);

#endif
