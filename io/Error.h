#ifndef FINAL_PROJECT_ERROR_H
#define FINAL_PROJECT_ERROR_H

/* The possible error levels */

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
} Error;


/* Initialize a new Error.
 * There are two options:
 *   - an empty error
 *   - an error with a message and a matching error level */

Error* create_empty_error();

Error* create_error(char *message, ErrorLevel level);


/* Free all the resources used by the error */
void destroy_error(Error* error);

#endif
