#ifndef FINAL_PROJECT_USERHANDLER_H
#define FINAL_PROJECT_USERHANDLER_H

#include "components/Game.h"
#include "io/Command.h"


void announce_game_start();

void announce_game_won();

void announce_game_erroneous();

void get_user_command(Game *game, Command *command);

void announce_error(Error *error);

#endif

