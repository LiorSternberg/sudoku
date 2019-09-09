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

void announce_game_solvable();

void announce_game_not_solvable();

void announce_hint(int hint);

void announce_num_of_solutions(int num_of_solutions);

void announce_changes_made();

void announce_no_changes_made();

void print_change(Change *change, bool reverted);

void announce_guesses_list();

void print_guess(int value, double score);

void print_autofill(int row, int column, int value);

void announce_error(Error *error);

void announce_exit();

#endif
