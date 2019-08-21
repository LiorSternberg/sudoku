#include "actions.h"
#include "../io/Command.h"
#include "../io/Serializer.h"
#include "../UserHandler.h"
#include "../io/Printer.h"

#define DEFAULT_SIZE (3)

void play_solve(Command *command, Game *game) {
    Board *board = load_from_file(command->data.solve->path, command->error);
    if (is_valid(command)) {
        destroy_board(game->board);
        game->board = board;
        game->mode = solve_mode;
        clear_states_list(game->states);
        print(game);
    }
}

void play_edit(Command *command, Game *game) {
    Board *board;
    if (command->data.edit->from_file == true) {
        board = load_from_file(command->data.edit->path, command->error);
    } else {
        board = create_board(DEFAULT_SIZE, DEFAULT_SIZE);
    }

    if (is_valid(command)) {
        destroy_board(game->board);
        game->board = board;
        game->mode = edit_mode;
        clear_states_list(game->states);
        print(game);
    }
}

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
