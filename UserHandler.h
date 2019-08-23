#ifndef FINAL_PROJECT_USERHANDLER_H
#define FINAL_PROJECT_USERHANDLER_H

#include "components/Game.h"
#include "io/Command.h"


void announce_game_start();

void announce_game_won();

void announce_game_erroneous();

void announce_changes_made();

void print_change(Change *change, bool reverted);

void get_user_command(Game *game, Command *command);

void announce_error(Error *error);

void announce_exit();

#endif

