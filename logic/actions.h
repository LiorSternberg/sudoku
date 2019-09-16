#ifndef FINAL_PROJECT_COMMANDS_H
#define FINAL_PROJECT_COMMANDS_H

#include "../components/Game.h"
#include "../io/Command.h"

/** actions:
 *
 * This module is responsible for the specific actions each command requires.
 * It contains a 'play' function for each command type, that executes the turn
 * determined by the command data.
 */

/**
 * Plays the turn of a solve command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_solve(Command *command, Game *game);

/**
 * Plays the turn of a edit command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_edit(Command *command, Game *game);

/**
 * Plays the turn of a mark_errors command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_mark_errors(Command *command, Game *game);

/**
 * Plays the turn of a print_board command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_print_board(Command *command, Game *game);

/**
 * Plays the turn of a set command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_set(Command *command, Game *game);

/**
 * Plays the turn of a validate command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_validate(Command *command, Game *game);

/**
 * Plays the turn of a guess command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_guess(Command *command, Game *game);

/**
 * Plays the turn of a generate command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_generate(Command *command, Game *game);

/**
 * Plays the turn of a undo command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_undo(Command *command, Game *game);

/**
 * Plays the turn of a redo command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_redo(Command *command, Game *game);

/**
 * Plays the turn of a save command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_save(Command *command, Game *game);

/**
 * Plays the turn of a hint command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_hint(Command *command, Game *game);

/**
 * Plays the turn of a guess_hint command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_guess_hint(Command *command, Game *game);

/**
 * Plays the turn of a num_solutions command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_num_solutions(Command *command, Game *game);

/**
 * Plays the turn of a autofill command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_autofill(Command *command, Game *game);

/**
 * Plays the turn of a reset command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_reset(Command *command, Game *game);

/**
 * Plays the turn of a exit_game command based on the command's arguments.
 * If a command execution fails, it invalidates the command with an appropriate
 * error message and level.
 * @param command: the command to be executed.
 * @param game: the current game.
 */
void play_exit_game(Command *command, Game *game);

#endif
