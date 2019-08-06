#ifndef FINAL_PROJECT_VALIDATION_H
#define FINAL_PROJECT_VALIDATION_H

#include "Command.h"
#include "../components/Game.h"


void null_validator(Command *command, Game *game);

void validate_solve(Command *command, Game *game);

void validate_edit(Command *command, Game *game);

void validate_mark_errors(Command *command, Game *game);

void validate_print_board(Command *command, Game *game);

void validate_set(Command *command, Game *game);

void validate_validate(Command *command, Game *game);

void validate_guess(Command *command, Game *game);

void validate_generate(Command *command, Game *game);

void validate_undo(Command *command, Game *game);

void validate_redo(Command *command, Game *game);

void validate_save(Command *command, Game *game);

void validate_hint(Command *command, Game *game);

void validate_guess_hint(Command *command, Game *game);

void validate_num_solutions(Command *command, Game *game);

void validate_autofill(Command *command, Game *game);

void validate_reset(Command *command, Game *game);

void validate_exit(Command *command, Game *game);

void validate_command(Command *command, Game *game);

#endif
