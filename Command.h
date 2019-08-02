#ifndef FINAL_PROJECT_COMMAND_H
#define FINAL_PROJECT_COMMAND_H

#include <stdbool.h>

/* The possible types of commands (empty refers to a non-command that should be ignored) */
typedef enum { solve, edit, mark_errors, print_board, set, validate, guess, generate, undo, redo, save, hint,
    guess_hint, num_solutions, autofill, reset, exit_game, empty } CommandType;


/* The different commands: */

typedef struct {
    char* path;
} SolveCommand;

typedef struct {
    char* path;
} EditCommand;

typedef struct {
    int setting;
} MarkErrorsCommand;

typedef struct {
    int row;
    int column;
    int value;
} SetCommand;

typedef struct {
    float threshold;
} GuessCommand;

typedef struct {
    int num_to_fill;
    int num_to_leave;
} GenerateCommand;

typedef struct {
    char* path;
} SaveCommand;

typedef struct {
    int row;
    int column;
} HintCommand;

typedef struct {
    int row;
    int column;
} GuessHintCommand;


/* The command information such as the type of the command, and the command-specific data. */
typedef struct {
    CommandType type;
    union {
        SolveCommand solve;
        EditCommand edit;
        MarkErrorsCommand mark_errors;
        SetCommand set;
        GuessCommand guess;
        GenerateCommand generate;
        SaveCommand save;
        HintCommand hintCommand;
        GuessHintCommand guess_hint;
    } data;
    char* error_message;
    bool valid;

} Command;


#endif
