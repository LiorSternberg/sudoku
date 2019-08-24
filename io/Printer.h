#ifndef FINAL_PROJECT_PRINTER_H
#define FINAL_PROJECT_PRINTER_H

#include "../components/Game.h"
#include "Error.h"

/** Printer:
 *   this module is responsible for printing messages to the user.
 *   This includes printing the game board and the various announcements
 *   of the game. */


/* Prints the sudoku board to stdout. */
void print(Game *game);

void announce_game_start();

void announce_game_won();

void announce_game_erroneous();

void announce_changes_made();

void print_change(Change *change, bool reverted);

void announce_error(Error *error);

void announce_exit();

#endif
