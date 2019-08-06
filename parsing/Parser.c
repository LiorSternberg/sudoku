#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parser.h"
#include "validation.h"

#define MAX_ARGS 4
#define WHITESPACE " \t\r\n"

#define INVALID_COMMAND_INIT_ERROR "Error: invalid command. Available commands are: solve, edit, exit."
#define INVALID_COMMAND_EDIT_ERROR "Error: invalid command. Available commands are: solve, edit, print_board, set, " \
                                   "validate, generate, undo, redo, save, num_solutions, reset, exit."
#define INVALID_COMMAND_SOLVE_ERROR "Error: invalid command. Available commands are: solve, edit, mark_errors, " \
                                    "print_board, set, validate, guess, undo, redo, save, hint, guess_hint, exit" \
                                    "num_solutions, autofill, reset, "
#define TOO_MANY_ARGS_ERROR "Error: too many arguments were given."
#define TOO_FEW_ARGS_ERROR "Error: not enough arguments were given."
#define ARG_OUT_OF_RANGE_ERROR "Error: argument is not in the correct range."

#define MAX_ERROR_MESSAGE_LEN 2048


void assert_num_of_args(Command *command, int min_expected, int max_expected, int actual) {
    char error_message[MAX_ERROR_MESSAGE_LEN] = {0};
    int res;

    if (actual > max_expected) {
        res = sprintf(error_message, "%s Correct command format: %s", TOO_MANY_ARGS_ERROR, command->format);
        invalidate(command, error_message);
    }
    else if (actual < min_expected) {
        res = sprintf(error_message, "%s Correct command format: %s", TOO_FEW_ARGS_ERROR, command->format);
        invalidate(command, error_message);
    }
}

/* parsers for specific types of args */

void parse_int_arg(char *token, int *p_int) {
    *p_int = atoi(token);
}

void parse_double_arg(char *token, double *p_double) {
    *p_double = atof(token);
}

void parse_bool_arg(Command *command, char *token, bool *p_bool) {
    int bool_value;

    parse_int_arg(token, &bool_value);

    if (bool_value == 0) {
        *p_bool = false;
    } else if (bool_value == 1) {
        *p_bool = true;
    } else {
        invalidate(command, ARG_OUT_OF_RANGE_ERROR);
    }
}


/* command-specific arg parsers */

void parse_solve_args(Command *self, char **args, int num_of_args) {
    SolveCommand *data = malloc(sizeof(SolveCommand));
    assert_num_of_args(self, SOLVE_ARGS, SOLVE_ARGS, num_of_args);

    if (!self->valid) {
        free(data);
        return;
    }

    data->path = args[0];
    self->data.solve = data;
}

void parse_edit_args(Command *self, char **args, int num_of_args) {
    EditCommand *data = malloc(sizeof(EditCommand));
    assert_num_of_args(self, EDIT_MIN_ARGS, EDIT_MAX_ARGS, num_of_args);

    if (!self->valid) {
        free(data);
        return;
    }

    if (num_of_args == EDIT_MAX_ARGS) {
        data->from_file = true;
        data->path = args[0];
    } else if (num_of_args == EDIT_MIN_ARGS) {
        data->from_file = false;
        data->path = NULL;
    }

    self->data.edit = data;
}

void parse_mark_errors_args(Command *self, char **args, int num_of_args) {
    MarkErrorsCommand *data = malloc(sizeof(MarkErrorsCommand));
    assert_num_of_args(self, MARK_ERRORS_ARGS, MARK_ERRORS_ARGS, num_of_args);

    if (!self->valid) {
        free(data);
        return;
    }

    parse_bool_arg(self, args[0], &data->setting);
    self->data.mark_errors = data;
}

void parse_set_args(Command *self, char **args, int num_of_args) {
    SetCommand *data = malloc(sizeof(SetCommand));
    assert_num_of_args(self, SET_ARGS, SET_ARGS, num_of_args);

    if (!self->valid) {
        free(data);
        return;
    }

    parse_int_arg(args[0], &data->column);
    parse_int_arg(args[1], &data->row);
    parse_int_arg(args[2], &data->value);
    self->data.set = data;
}

void parse_guess_args(Command *self, char **args, int num_of_args) {
    GuessCommand *data = malloc(sizeof(GuessCommand));
    assert_num_of_args(self, GUESS_ARGS, GUESS_ARGS, num_of_args);

    if (!self->valid) {
        free(data);
        return;
    }

    parse_double_arg(args[0], &data->threshold);
    self->data.guess = data;
}

void parse_generate_args(Command *self, char **args, int num_of_args) {
    GenerateCommand *data = malloc(sizeof(GenerateCommand));
    assert_num_of_args(self, GENERATE_ARGS, GENERATE_ARGS, num_of_args);

    if (!self->valid) {
        free(data);
        return;
    }

    parse_int_arg(args[0], &data->num_to_fill);
    parse_int_arg(args[1], &data->num_to_leave);
    self->data.generate = data;
}

void parse_save_args(Command *self, char **args, int num_of_args) {
    SaveCommand *data = malloc(sizeof(SaveCommand));
    assert_num_of_args(self, SAVE_ARGS, SAVE_ARGS, num_of_args);

    if (!self->valid) {
        free(data);
        return;
    }

    data->path = args[0];
    self->data.save = data;
}

void parse_hint_args(Command *self, char **args, int num_of_args) {
    HintCommand *data = malloc(sizeof(HintCommand));
    assert_num_of_args(self, HINT_ARGS, HINT_ARGS, num_of_args);

    if (!self->valid) {
        free(data);
        return;
    }

    parse_int_arg(args[0], &data->column);
    parse_int_arg(args[1], &data->row);
    self->data.hint = data;
}

void parse_guess_hint_args(Command *self, char **args, int num_of_args) {
    GuessHintCommand *data = malloc(sizeof(GuessHintCommand));
    assert_num_of_args(self, GUESS_HINT_ARGS, GUESS_HINT_ARGS, num_of_args);

    if (!self->valid) {
        free(data);
        return;
    }

    parse_int_arg(args[0], &data->column);
    parse_int_arg(args[1], &data->row);
    self->data.guess_hint = data;
}

void null_parser(Command *self, char **args, int num_of_args) {
    assert_num_of_args(self, NO_ARGS, NO_ARGS, num_of_args);
}



void configure_by_type(Command *command, char *type_str, GameMode mode) {
    command->_parse_args = null_parser;
    command->_validate = null_validator;

    if (strcmp(type_str, "solve") == 0) {
        command->type = solve;
        command->format = SOLVE_FORMAT;
        command->_parse_args = parse_solve_args;
        command->_validate = validate_solve;

    } else if (strcmp(type_str, "edit") == 0) {
        command->type = edit;
        command->format = EDIT_FORMAT;
        command->_parse_args = parse_edit_args;
        command->_validate = validate_edit;

    } else if (strcmp(type_str, "mark_errors") == 0) {
        command->type = mark_errors;
        command->format = MARK_ERRORS_FORMAT;
        command->_parse_args = parse_mark_errors_args;
        command->_validate = validate_mark_errors;

    } else if (strcmp(type_str, "print_board") == 0) {
        command->type = print_board;
        command->format = PRINT_BOARD_FORMAT;
        command->_validate = validate_print_board;

    } else if (strcmp(type_str, "set") == 0) {
        command->type = set;
        command->format = SET_FORMAT;
        command->_parse_args = parse_set_args;
        command->_validate = validate_set;

    } else if (strcmp(type_str, "validate") == 0) {
        command->type = validate;
        command->format = VALIDATE_FORMAT;
        command->_validate = validate_validate;

    } else if (strcmp(type_str, "guess") == 0) {
        command->type = guess;
        command->format = GUESS_FORMAT;
        command->_parse_args = parse_guess_args;
        command->_validate = validate_guess;

    } else if (strcmp(type_str, "generate") == 0) {
        command->type = generate;
        command->format = GENERATE_FORMAT;
        command->_parse_args = parse_generate_args;
        command->_validate = validate_generate;

    } else if (strcmp(type_str, "undo") == 0) {
        command->type = undo;
        command->format = UNDO_FORMAT;
        command->_validate = validate_undo;

    } else if (strcmp(type_str, "redo") == 0) {
        command->type = redo;
        command->format = REDO_FORMAT;
        command->_validate = validate_redo;

    } else if (strcmp(type_str, "save") == 0) {
        command->type = save;
        command->format = SAVE_FORMAT;
        command->_parse_args = parse_save_args;
        command->_validate = validate_save;

    } else if (strcmp(type_str, "hint") == 0) {
        command->type = hint;
        command->format = HINT_FORMAT;
        command->_parse_args = parse_hint_args;
        command->_validate = validate_hint;

    } else if (strcmp(type_str, "guess_hint") == 0) {
        command->type = guess_hint;
        command->format = GUESS_HINT_FORMAT;
        command->_parse_args = parse_guess_hint_args;
        command->_validate = validate_guess_hint;

    } else if (strcmp(type_str, "num_solutions") == 0) {
        command->type = num_solutions;
        command->format = NUM_SOLUTIONS_FORMAT;
        command->_validate = validate_num_solutions;

    } else if (strcmp(type_str, "autofill") == 0) {
        command->type = autofill;
        command->format = AUTOFILL_FORMAT;
        command->_validate = validate_autofill;

    } else if (strcmp(type_str, "reset") == 0) {
        command->type = reset;
        command->format = RESET_FORMAT;
        command->_validate = validate_reset;

    } else if (strcmp(type_str, "exit") == 0) {
        command->type = exit_game;
        command->format = EXIT_FORMAT;
        command->_validate = validate_exit;

    } else {
        if (mode == init_mode) {
            invalidate(command, INVALID_COMMAND_INIT_ERROR);
        } else if (mode == edit_mode) {
            invalidate(command, INVALID_COMMAND_EDIT_ERROR);
        } else if (mode == solve_mode) {
            invalidate(command, INVALID_COMMAND_SOLVE_ERROR);
        }
    }
}


/* main parsing function */

void parse_command(char *raw_command, Command *command, Game *game) {
    char *token;
    char* tokens[MAX_ARGS];
    int num_of_args = 0;


    /* get the first token (the type of the command, if exists) */
    token = strtok(raw_command, WHITESPACE);
    if (token == NULL) {
        command->type = empty;
        return;
    }

    configure_by_type(command, token, game->mode);

    /* walk through other tokens */
    token = strtok(NULL, WHITESPACE);
    while (token != NULL && num_of_args < MAX_ARGS) {
        tokens[num_of_args] = token;
        num_of_args++;
        token = strtok(NULL, WHITESPACE);
    }

    command->_parse_args(command, tokens, num_of_args);
}
