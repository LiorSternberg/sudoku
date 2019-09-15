#ifndef FINAL_PROJECT_LOADER_H
#define FINAL_PROJECT_LOADER_H

#include "Error.h"
#include "../components/Game.h"

/**
 * Load a board from file. Also validates the format is correct.
 * In addition, performs basic validations of the legality of the values
 * themselves, and asserts that there are no collisions of fixed cells.
 * @param path: the path of the input file. Must be an existing file with data
 * in the correct format of a sudoku board.
 * @param error: the error to set in case there is a problem loading the file.
 * @param mode: the current mode of the game.
 * @return: the loaded board in case of success, and NULL in case of error.
 */
Board* load_from_file(char *path, Error *error, GameMode mode);

/**
 * Save a board to a file.
 * If the game is in Edit mode, all values are saved as fixed.
 * This function does not validate the board, this should be done before
 * calling it.
 * @param game: the game to save (save the game board, according to the game mode).
 * @param path: the path of the output file.
 * @param error: the error to set in case there is a problem saving the file.
 */
void save_to_file(Game *game, char *path, Error *error);

#endif
