#ifndef FINAL_PROJECT_VALIDATION_H
#define FINAL_PROJECT_VALIDATION_H

#include "Command.h"
#include "../components/Game.h"

/** validators:
 *   this module is responsible for the validation of structured commands.
 *   It contains the type-specific validators for commands that require custom
 *   validations, and the main validation function used to validate a Command. */


/* Command-specific validators (used by the Parser at the configuration stage) */

void solve_validator(Command *command, Game *game);

void edit_validator(Command *command, Game *game);

void mark_errors_validator(Command *command, Game *game);

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

/* Validates the command - adds a relevant error message and error level
 * if the command is found to be invalid. */
void validate_command(Command *command, Game *game);

#endif
