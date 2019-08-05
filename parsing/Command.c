#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Command.h"

#define INVALID_COMMAND_ERROR "Error: invalid command\n"
#define INVALID_NUM_OF_ARGS_ERROR "Error: invalid number of arguments\n"
#define ARG_OUT_OF_RANGE_ERROR "Error: argument is not in the correct range\n"

#define SOLVE_ARGS 1
#define EDIT_MIN_ARGS 0
#define EDIT_MAX_ARGS 1
#define MARK_ERRORS_ARGS 1
#define SET_ARGS 3
#define GUESS_ARGS 1
#define GENERATE_ARGS 2
#define SAVE_ARGS 1
#define HINT_ARGS 2
#define GUESS_HINT_ARGS 2


void invalidate(Command *command, char *error_message) {
    if (!command->valid) {
        return;
    }

    command->valid=false;
    command->error_message=error_message;
}

void assert_num_of_args(Command *command, int expected, int actual) {
    if (expected != actual) {
        invalidate(command, INVALID_NUM_OF_ARGS_ERROR);
    }
}

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


/* Args parsers */

void parse_solve_args(Command *self, char **args, int num_of_args) {
    SolveCommand *data = malloc(sizeof(SolveCommand));
    assert_num_of_args(self, SOLVE_ARGS, num_of_args);

    if (!self->valid) {
        free(data);
        return;
    }

    data->path = args[0];
    self->data.solve = data;
}

void parse_edit_args(Command *self, char **args, int num_of_args) {
    EditCommand *data = malloc(sizeof(EditCommand));

    if (num_of_args < EDIT_MIN_ARGS || num_of_args > EDIT_MAX_ARGS) {
        invalidate(self, INVALID_NUM_OF_ARGS_ERROR);
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
    assert_num_of_args(self, MARK_ERRORS_ARGS, num_of_args);

    if (!self->valid) {
        free(data);
        return;
    }

    parse_bool_arg(self, args[0], &data->setting);
    self->data.mark_errors = data;
}

void parse_set_args(Command *self, char **args, int num_of_args) {
    SetCommand *data = malloc(sizeof(SetCommand));
    assert_num_of_args(self, SET_ARGS, num_of_args);

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
    assert_num_of_args(self, GUESS_ARGS, num_of_args);

    if (!self->valid) {
        free(data);
        return;
    }

    parse_double_arg(args[0], &data->threshold);
    self->data.guess = data;
}

void parse_generate_args(Command *self, char **args, int num_of_args) {
    GenerateCommand *data = malloc(sizeof(GenerateCommand));
    assert_num_of_args(self, GENERATE_ARGS, num_of_args);

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
    assert_num_of_args(self, SAVE_ARGS, num_of_args);

    if (!self->valid) {
        free(data);
        return;
    }

    data->path = args[0];
    self->data.save = data;
}

void parse_hint_args(Command *self, char **args, int num_of_args) {
    HintCommand *data = malloc(sizeof(HintCommand));
    assert_num_of_args(self, HINT_ARGS, num_of_args);

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
    assert_num_of_args(self, GUESS_HINT_ARGS, num_of_args);

    if (!self->valid) {
        free(data);
        return;
    }

    parse_int_arg(args[0], &data->column);
    parse_int_arg(args[1], &data->row);
    self->data.guess_hint = data;
}

void null_parser(Command *self, char **args, int num_of_args) {}


void parse_type(Command *command, char *token) {
    command->_parse_args = null_parser;

    if (strcmp(token, "solve") == 0) {
        command->type = solve;
        command->_parse_args = parse_solve_args;
    } else if (strcmp(token, "edit") == 0) {
        command->type = edit;
        command->_parse_args = parse_edit_args;
    } else if (strcmp(token, "mark_errors") == 0) {
        command->type = mark_errors;
        command->_parse_args = parse_mark_errors_args;
    } else if (strcmp(token, "print_board") == 0) {
        command->type = print_board;
    } else if (strcmp(token, "set") == 0) {
        command->type = set;
        command->_parse_args = parse_set_args;
    } else if (strcmp(token, "validate") == 0) {
        command->type = validate;
    } else if (strcmp(token, "guess") == 0) {
        command->type = guess;
        command->_parse_args = parse_guess_args;
    } else if (strcmp(token, "generate") == 0) {
        command->type = generate;
        command->_parse_args = parse_generate_args;
    } else if (strcmp(token, "undo") == 0) {
        command->type = undo;
    } else if (strcmp(token, "redo") == 0) {
        command->type = redo;
    } else if (strcmp(token, "save") == 0) {
        command->type = save;
        command->_parse_args = parse_save_args;
    } else if (strcmp(token, "hint") == 0) {
        command->type = hint;
        command->_parse_args = parse_hint_args;
    } else if (strcmp(token, "guess_hint") == 0) {
        command->type = guess_hint;
        command->_parse_args = parse_guess_hint_args;
    } else if (strcmp(token, "num_solutions") == 0) {
        command->type = num_solutions;
    } else if (strcmp(token, "autofill") == 0) {
        command->type = autofill;
    } else if (strcmp(token, "reset") == 0) {
        command->type = reset;
    } else if (strcmp(token, "exit") == 0) {
        command->type = exit_game;
    } else {
        invalidate(command, INVALID_COMMAND_ERROR);
    }
    command->valid=true;
}
