#ifndef FINAL_PROJECT_COMMAND_H
#define FINAL_PROJECT_COMMAND_H

#include <stdbool.h>
#include "../components/Game.h"
#include "Error.h"

/** Command:
 *   this module defines the structured commands and their configurations. */

/* Number of arguments per command type */
#define NO_ARGS 0
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

/* Command format per command type */
#define SOLVE_FORMAT "solve <path>"
#define EDIT_FORMAT "edit [<path>]"
#define MARK_ERRORS_FORMAT "mark_errors <set>"
#define PRINT_BOARD_FORMAT "print_board"
#define SET_FORMAT "set <column> <row> <value>"
#define VALIDATE_FORMAT "validate"
#define GUESS_FORMAT "guess <threshold>"
#define GENERATE_FORMAT "generate <#cells to fill> <#cells to leave>"
#define UNDO_FORMAT "undo"
#define REDO_FORMAT "redo"
#define SAVE_FORMAT "save <path>"
#define HINT_FORMAT "hint <column> <row>"
#define GUESS_HINT_FORMAT "guess_hint <column> <row>"
#define NUM_SOLUTIONS_FORMAT "num_solutions"
#define AUTOFILL_FORMAT "autofill"
#define RESET_FORMAT "reset"
#define EXIT_FORMAT "exit"

/* Numeric arguments' limits */
#define MIN_THRESHOLD 0
#define MAX_THRESHOLD 1
#define MIN_CELLS 1

/* Allowed game modes per command type */
#define SOLVE_MODES (solve_mode + edit_mode + init_mode)
#define EDIT_MODES (solve_mode + edit_mode + init_mode)
#define MARK_ERRORS_MODES (solve_mode)
#define PRINT_BOARD_MODES (solve_mode + edit_mode)
#define SET_MODES (solve_mode + edit_mode)
#define VALIDATE_MODES (solve_mode + edit_mode)
#define GUESS_MODES (solve_mode)
#define GENERATE_MODES (edit_mode)
#define UNDO_MODES (solve_mode + edit_mode)
#define REDO_MODES (solve_mode + edit_mode)
#define SAVE_MODES (solve_mode + edit_mode)
#define HINT_MODES (solve_mode)
#define GUESS_HINT_MODES (solve_mode)
#define NUM_SOLUTIONS_MODES (solve_mode + edit_mode)
#define AUTOFILL_MODES (solve_mode)
#define RESET_MODES (solve_mode + edit_mode)
#define EXIT_MODES (solve_mode + edit_mode + init_mode)


/* The possible types of commands ('empty' refers to a non-command that should be ignored) */
typedef enum { solve, edit, mark_errors, print_board, set, validate, guess, generate, undo, redo, save, hint,
    guess_hint, num_solutions, autofill, reset, exit_game, empty } CommandType;


/* The different commands' additional data */
typedef struct {
    char* path;
} SolveCommand, SaveCommand;

typedef struct {
    char* path;
    bool from_file;
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
    char* format;
    unsigned short modes;
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
    void (*_play)(struct Command_*, Game *game);
    Error *error;
} Command;


/**
 * Sets a command's error message and error level, and by doing so, invalidating it.
 * @param command: the command to invalidate.
 * @param error_message: the error message to set for the error.
 * @param error_level: the error level to set the error to.
 * @param message_allocated: true if the error message was allocated dynamic memory
 * and will need to be freed eventually, and false otherwise.
 */
void invalidate(Command *command, char *error_message, int error_level, bool message_allocated);

/**
 * Creates a new command.
 * @return: the command that was created.
 */
Command* create_command();

/**
 * Destroys the given command (frees all related memory).
 * @param command: the command to destroy.
 */
void destroy_command(Command* command);

/**
 * Checks if the command is valid.
 * @param command: the command to check.
 * @return: true if the command is valid and no error has been set, and false
 * otherwise.
 */
bool is_valid(Command *command);

#endif
