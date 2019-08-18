#ifndef FINAL_PROJECT_LOADER_H
#define FINAL_PROJECT_LOADER_H

#include "../components/Board.h"
#include "Error.h"
#include "../components/Game.h"

/* Load a board from file. Also validates the format is correct.
 * Additional validations such as the legality of the values themselves, and
 * that there are no collisions of fixed cells are to be done separately. */
Board* load_from_file(char *path, Error *error);


/* Save a board to a file.
 * If the game is in Edit mode, all values are saved as fixed.
 * This function does not validate the board, this should be done before
 * calling it. */
void save_to_file(Game *game, char *path, Error *error);

#endif
