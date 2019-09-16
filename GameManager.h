#ifndef FINAL_PROJECT_GAMEMANAGER_H
#define FINAL_PROJECT_GAMEMANAGER_H

#include "io/Command.h"

/**
 * Plays a turn in the game:
 *  - Gets a command from the user.
 *  - Validates the command.
 *  - Executes the command.
 * In case the command is found to invalid at some point, an error message will
 * be printed to the user, and the turn will be terminated.
 *
 * @param game: the current game.
 */
void play_turn(Game *game);

#endif
