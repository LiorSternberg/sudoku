#ifndef FINAL_PROJECT_COMMAND_H
#define FINAL_PROJECT_COMMAND_H

#include <stdbool.h>
#include "../components/Game.h"

/* The possible types of commands (empty refers to a non-command that should be ignored) */
typedef enum { solve, edit, mark_errors, print_board, set, validate, guess, generate, undo, redo, save, hint,
    guess_hint, num_solutions, autofill, reset, exit_game, empty } CommandType;


/* The different commands: */

typedef struct {
    char* path;
} SolveCommand, SaveCommand;

typedef struct {
    char* path;
    bool from_file;
} EditCommand;

typedef struct {
    bool setting;
} MarkErrorsCommand;

typedef struct {
    int row;
    int column;
    int value;
} SetCommand;

typedef struct {
    double threshold;
} GuessCommand;

typedef struct {
    int num_to_fill;
    int num_to_leave;
} GenerateCommand;

typedef struct {
    int row;
    int column;
} HintCommand, GuessHintCommand;


/* The command information such as the type of the command, and the command-specific data. */
typedef struct Command_ {
    CommandType type;
    union {
        SolveCommand *solve;
        EditCommand *edit;
        MarkErrorsCommand *mark_errors;
        SetCommand *set;
        GuessCommand *guess;
        GenerateCommand *generate;
        SaveCommand *save;
        HintCommand *hint;
        GuessHintCommand *guess_hint;
    } data;
    void (*_parse_args)(struct Command_*, char**, int);
    void (*_validate)(struct Command_*, Game *game);
    char* error_message;
    bool valid;
} Command;


void invalidate(Command *command, char *error_message);

Command* create_command();

void destroy_command(Command* command);

#endif
