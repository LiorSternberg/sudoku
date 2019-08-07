#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "validators.h"
#include "../components/Game.h"
#include "Command.h"

#define FIXED_ERROR "Error: cell is fixed\n"
#define INVALID_VALUE_ERROR "Error: value is invalid\n"
#define FILE_DOESNT_EXIST_ERROR "Error: The given file doesn't exist!\n"
#define FILE_NOT_READABLE_ERROR "Error: The given file cannot be read (no permission)\n"

#define MAX_ERROR_MESSAGE_LEN 1024

#define INVALID_COMMAND_FOR_MODE_ERROR "Error: command is not available in the current mode. Only available in:"
#define ALL_MODES "Init, Edit, Solve."
#define SOLVE_AND_EDIT_MODES "Solve, Edit."
#define SOLVE_MODE "Solve."
#define EDIT_MODE "Edit."


void assert_game_mode(Command *command, GameMode mode) {
    int res;
    char *error_message = calloc(MAX_ERROR_MESSAGE_LEN, sizeof(char));
    char *modes[8] = {0};

    modes[init_mode + solve_mode + edit_mode] = ALL_MODES;
    modes[solve_mode + edit_mode] = SOLVE_AND_EDIT_MODES;
    modes[solve_mode] = SOLVE_MODE;
    modes[edit_mode] = EDIT_MODE;

    /* bitwise 'and' to check mode compatibility */
    if ((command->modes & mode) == 0) {
        res = sprintf(error_message, "%s %s", INVALID_COMMAND_FOR_MODE_ERROR, modes[command->modes]);
        invalidate(command, error_message, invalid_command_for_mode);
    }
}

void assert_file_readable(Command *command, char *path) {
    if(access(path, F_OK) == -1) { /* file doesn't exist */
        invalidate(command, FILE_DOESNT_EXIST_ERROR, execution_failure);
    } else if (access(path, R_OK) == -1) { /* file doesn't have read permissions */
        invalidate(command, FILE_NOT_READABLE_ERROR, execution_failure);
    }
}

void base_validator(Command *command, Game *game) {
    assert_game_mode(command, game->mode);
}

void solve_validator(Command *command, Game *game) {
    assert_file_readable(command, command->data.solve->path);
}

void edit_validator(Command *command, Game *game) {
    if (command->data.edit->from_file == true) {
        assert_file_readable(command, command->data.edit->path);
    }
}

void mark_errors_validator(Command *command, Game *game) {
}

void print_board_validator(Command *command, Game *game) {
}

void set_validator(Command *command, Game *game) {
}

void validate_validator(Command *command, Game *game) {
}

void guess_validator(Command *command, Game *game) {
}

void generate_validator(Command *command, Game *game) {
}

void undo_validator(Command *command, Game *game) {
}

void redo_validator(Command *command, Game *game) {
}

void save_validator(Command *command, Game *game) {
}

void hint_validator(Command *command, Game *game) {
}

void guess_hint_validator(Command *command, Game *game) {
}

void num_solutions_validator(Command *command, Game *game) {
}

void autofill_validator(Command *command, Game *game) {
}

void reset_validator(Command *command, Game *game) {
}

void exit_validator(Command *command, Game *game) {
}

void validate_command(Command *command, Game *game) {
    base_validator(command, game);
    if (command->_validate != NULL) {
        command->_validate(command, game);
    }
}

