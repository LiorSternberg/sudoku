#include "actions.h"
#include "../io/Command.h"
#include "../io/Serializer.h"
#include "../UserHandler.h"
#include "../io/Printer.h"


void play_solve(Command *command, Game *game) {
    game->board = load_from_file(command->data.solve->path, command->error);
    if (is_valid(command)) {
        game->mode = solve_mode;
        print(game->board, game->mark_errors);
    }
}

void play_edit(Command *command, Game *game) {}

void play_mark_errors(Command *command, Game *game) {}

void play_print_board(Command *command, Game *game) {}

void play_set(Command *command, Game *game) {}

void play_validate(Command *command, Game *game) {}

void play_guess(Command *command, Game *game) {}

void play_generate(Command *command, Game *game) {}

void play_undo(Command *command, Game *game) {}

void play_redo(Command *command, Game *game) {}

void play_save(Command *command, Game *game) {}

void play_hint(Command *command, Game *game) {}

void play_guess_hint(Command *command, Game *game) {}

void play_num_solutions(Command *command, Game *game) {}

void play_autofill(Command *command, Game *game) {}

void play_reset(Command *command, Game *game) {}

void play_exit_game(Command *command, Game *game) {}
