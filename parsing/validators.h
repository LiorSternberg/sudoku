#ifndef FINAL_PROJECT_VALIDATION_H
#define FINAL_PROJECT_VALIDATION_H

#include "Command.h"
#include "../components/Game.h"


void base_validator(Command *command, Game *game);

void solve_validator(Command *command, Game *game);

void edit_validator(Command *command, Game *game);

void mark_errors_validator(Command *command, Game *game);

void print_board_validator(Command *command, Game *game);

void set_validator(Command *command, Game *game);

void validate_validator(Command *command, Game *game);

void guess_validator(Command *command, Game *game);

void generate_validator(Command *command, Game *game);

void undo_validator(Command *command, Game *game);

void redo_validator(Command *command, Game *game);

void save_validator(Command *command, Game *game);

void hint_validator(Command *command, Game *game);

void guess_hint_validator(Command *command, Game *game);

void num_solutions_validator(Command *command, Game *game);

void autofill_validator(Command *command, Game *game);

void reset_validator(Command *command, Game *game);

void exit_validator(Command *command, Game *game);

void validate_command(Command *command, Game *game);

#endif
