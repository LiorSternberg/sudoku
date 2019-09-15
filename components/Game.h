#ifndef FINAL_PROJECT_GAME_H
#define FINAL_PROJECT_GAME_H

#include <stdbool.h>
#include "StatesList.h"
#include "Board.h"

/** Game:
 *
 *  The component is used to manage the state of the game. It includes the
 *  puzzle's board, the states list, and general information such as the
 *  mark_errors flag, the game's mode, and a flag that says if the game is
 *  still running, or if it's over.
 */


/**
 * GameModes are used to determine which commands can be used at any
 * given moment in the game. The values are set as such to allow for
 * simplified use in binary operations. */
typedef enum {
    edit_mode = 1,
    solve_mode = 2,
    init_mode = 4
} GameMode;

typedef struct {
    GameMode mode;
    bool mark_errors;
    bool over;
    States *states;
    Board *board;
} Game;

/**
 * Creates a new game, and initializes the various fields.
 * @return: the new game that was created.
 */
Game* create_game();

/**
 * Destroys the game (frees all related memory).
 * @param game: the game to destroy.
 */
void destroy_game(Game *game);


#endif
