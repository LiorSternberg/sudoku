#ifndef FINAL_PROJECT_PRINTER_H
#define FINAL_PROJECT_PRINTER_H

#include "../components/Game.h"
#include "Error.h"

/** Printer:
 *   this module is responsible for printing messages to the user.
 *   This includes printing the game board and the various announcements
 *   of the game. */


/**
 * Prints the sudoku board to stdout.
 * @param game: the game to print (print the game board according to the game
 * meta-data, such as the mark_errors flag).
 */
void print(Game *game);

/**
 * Announces to the user the game has started with a nice header.
 */
void announce_game_start();

/**
 * Announces to the user the game has been won.
 */
void announce_game_won();

/**
 * Announces to the user the game has ended with errors.
 */
void announce_game_erroneous();

/**
 * Announces to the user the game is solvable.
 */
void announce_game_solvable();

/**
 * Announces to the user the game is not solvable.
 */
void announce_game_not_solvable();

/**
 * Gives the user the information regarding the hint that was requested.
 * @param hint: the hint value to give to the user.
 */
void announce_hint(int hint);

/**
 * Tells the user how many solutions the current game has.
 * @param num_of_solutions: the number of solution of the current game.
 */
void announce_num_of_solutions(int num_of_solutions);

/**
 * Announces to the user that changes were made. Further information about the
 * specifics of the changes will be given separately.
 */
void announce_changes_made();

/**
 * Announces to the user that no changes were made.
 */
void announce_no_changes_made();

/**
 * Prints the information of a specific change to the user.
 * @param change: the change to inform the user of.
 * @param reverted: true in case the given change has been reverted, and false
 * if it was made. Affects the direction of the printed change.
 */
void print_change(Change *change, bool reverted);


/**
 * Announces to the user that a guess is available. Further information about the
 * specifics of the guess will be given separately.
 */
void announce_guesses_list();

/**
 * Prints the information of a specific guess value to the user.
 * @param value: the value of the guess.
 * @param score: the score of the given value.
 */
void print_guess(int value, double score);

/**
 * Prints the information of a specific autofill change to the user.
 * @param row: the index of the row that was autofilled (zero-based).
 * @param column: the index of the column that was autofilled (zero-based).
 * @param value: the value that was autofilled (1-based).
 */
void print_autofill(int row, int column, int value);

/**
 * Announces an error occurred using it's error message.
 * @param error: the error to announce.
 */
void announce_error(Error *error);

/**
 * Announces to the user that the game is exiting.
 */
void announce_exit();

#endif
