#include <stdio.h>
#include "actions.h"
#include "../io/Serializer.h"
#include "../io/Printer.h"
#include "Backtracking.h"
#include "ILP.h"

#define DEFAULT_SIZE (3)
#define UNUSED(x) (void)(x)

void set_change(Board *board, Change *change) {
    set_cell_value(board, change->actual_row, change->actual_column, change->value);
}

void reset_change(Board *board, Change *change) {
    set_cell_value(board, change->actual_row, change->actual_column, change->prev_value);
}

void make_change(Game *game, int row, int column, int new_value) {
    int actual_row = row - 1, actual_column = column - 1;
    int prev_value = get_cell_value(game->board, actual_row, actual_column);
    Change *change = add_change(game->states, row, column, prev_value, new_value);

    set_change(game->board, change);
}


/* The different plays */

void play_solve(Command *command, Game *game) {
    Board *board = load_from_file(command->data.solve->path, command->error, solve_mode);
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
        board = load_from_file(command->data.edit->path, command->error, edit_mode);
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

void play_mark_errors(Command *command, Game *game) {
    game->mark_errors = (bool) command->data.mark_errors->setting;
}

void play_print_board(Command *command, Game *game) {
    UNUSED(command);
    print(game);
}

void play_set(Command *command, Game *game) {
    add_new_move(game->states);
    make_change(game, command->data.set->row, command->data.set->column, command->data.set->value);
    print(game);

    /* Check if this is the last cell to be filled */
    if (game->mode == solve_mode && game->board->empty_count == 0) {
        if (game->board->errors_count == 0) {
            announce_game_won();
            game->mode = init_mode;
        } else {
            announce_game_erroneous();
        }
    }
}

void play_validate(Command *command, Game *game) {
    UNUSED(command);

    if (is_board_solvable(game->board)) {
        announce_game_solvable();
    } else {
        announce_game_not_solvable();
    }
}

void play_guess(Command *command, Game *game) {
    UNUSED(command);
    UNUSED(game);
}

void play_generate(Command *command, Game *game) {
    UNUSED(command);
    UNUSED(game);
}

void play_undo(Command *command, Game *game) {
    Move *current_move = (Move*) get_current_item(game->states->moves);
    Change *change;

    UNUSED(command);

    reset_head(current_move->changes);
    announce_changes_made();
    do {
        change = (Change*) get_current_item(current_move->changes);
        reset_change(game->board, change);
        print_change(change, true);
    }
    while (next(current_move->changes) == 0);

    prev(game->states->moves);
    print(game);
}

void play_redo(Command *command, Game *game) {
    Move *current_move;
    Change *change;

    UNUSED(command);

    next(game->states->moves);
    current_move = (Move*) get_current_item(game->states->moves);

    reset_head(current_move->changes);
    announce_changes_made();
    do {
        change = (Change*) get_current_item(current_move->changes);
        set_change(game->board, change);
        print_change(change, false);
    }
    while (next(current_move->changes) == 0);
    print(game);
}

void play_save(Command *command, Game *game) {
    UNUSED(command);
    UNUSED(game);
}

void play_hint(Command *command, Game *game) {
    UNUSED(command);
    UNUSED(game);
}

void play_guess_hint(Command *command, Game *game) {
    UNUSED(command);
    UNUSED(game);
}

void play_num_solutions(Command *command, Game *game) {
    UNUSED(command);

    announce_num_of_solutions(get_num_of_solutions(game->board));
}

void play_autofill(Command *command, Game *game) {
    UNUSED(command);
    UNUSED(game);
}

void play_reset(Command *command, Game *game) {
    Move *current_move;
    Change *change;

    UNUSED(command);

    while (has_prev(game->states->moves)) {
        current_move = (Move*) get_current_item(game->states->moves);
        reset_head(current_move->changes);
        do {
            change = (Change*) get_current_item(current_move->changes);
            reset_change(game->board, change);
        } while (next(current_move->changes) == 0);
        prev(game->states->moves);
    };

    print(game);
}

void play_exit_game(Command *command, Game *game) {
    UNUSED(command);

    game->over = true;
    announce_exit();
}
