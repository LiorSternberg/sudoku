#include <stdio.h>
#include "validators.h"
#include "../components/Game.h"

#define FIXED_ERROR "Error: cell is fixed\n"
#define INVALID_VALUE_ERROR "Error: value is invalid\n"

#define MAX_ERROR_MESSAGE_LEN 2048

#define INVALID_COMMAND_FOR_MODE_ERROR "Error: command is not available in the current mode. Only available in:"
#define ALL_MODES "Init, Edit, Solve."
#define SOLVE_AND_EDIT_MODES "Init, Edit."
#define SOLVE_MODE "Solve."
#define EDIT_MODE "Edit."


void assert_game_mode(Command *command, GameMode mode) {
    int res;
    char error_message[MAX_ERROR_MESSAGE_LEN] = {0};
    char *modes[8] = {0};

    modes[init_mode + solve_mode + edit_mode] = ALL_MODES;
    modes[solve_mode + edit_mode] = SOLVE_AND_EDIT_MODES;
    modes[solve_mode] = SOLVE_MODE;
    modes[edit_mode] = EDIT_MODE;

    if ((command->modes & mode) == 0) {
        res = sprintf(error_message, "%s %s", INVALID_COMMAND_FOR_MODE_ERROR, modes[command->modes]);
        invalidate(command, error_message, invalid_command_for_mode);
    }
}

void base_validator(Command *command, Game *game) {
    assert_game_mode(command, game->mode);
}

void solve_validator(Command *command, Game *game) {
}

void edit_validator(Command *command, Game *game) {
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

void empty_validator(Command *command, Game *game) {}

void validate_command(Command *command, Game *game) {
    base_validator(command, game);
    command->_validate(command, game);
}

