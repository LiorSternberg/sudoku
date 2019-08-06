#ifndef FINAL_PROJECT_USERHANDLER_H
#define FINAL_PROJECT_USERHANDLER_H

#include "components/Game.h"
#include "parsing/Command.h"


void announce_game_start();

void get_user_command(Game *game, Command *command);

#endif

