#include "validation.h"
#include "../components/Game.h"

#define FIXED_ERROR "Error: cell is fixed\n"
#define INVALID_VALUE_ERROR "Error: value is invalid\n"
#define INVALID_VALUE_ERROR "Error: value is invalid\n"

void null_validator(Command *command, Game *game) {}

void validate_solve(Command *command, Game *game) {}

void validate_edit(Command *command, Game *game) {}

void validate_mark_errors(Command *command, Game *game) {}

void validate_print_board(Command *command, Game *game) {}

void validate_set(Command *command, Game *game) {}

void validate_validate(Command *command, Game *game) {}

void validate_guess(Command *command, Game *game) {}

void validate_generate(Command *command, Game *game) {}

void validate_undo(Command *command, Game *game) {}

void validate_redo(Command *command, Game *game) {}

void validate_save(Command *command, Game *game) {}

void validate_hint(Command *command, Game *game) {}

void validate_guess_hint(Command *command, Game *game) {}

void validate_num_solutions(Command *command, Game *game) {}

void validate_autofill(Command *command, Game *game) {}

void validate_reset(Command *command, Game *game) {}

void validate_exit(Command *command, Game *game) {}

void validate_command(Command *command, Game *game) {
    command->_validate(command, game);
}