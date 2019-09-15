#ifndef FINAL_PROJECT_MOVE_H
#define FINAL_PROJECT_MOVE_H

#include "List.h"

/** Move:
 *
 *  The component is used to store the changes made in a single turn.
 *  A Move is an item in the StatesList moves list, and a Change is an item
 *  in the changes list of a Move.
 */

typedef struct {
    int row;
    int actual_row;
    int column;
    int actual_column;
    int value;
    int prev_value;
} Change;

typedef struct {
    List *changes;
} Move;

/**
 * Creates a new change.
 * @param row: the row of the cell of the change.
 * @param column: the column of the cell of the change.
 * @param prev_value: the previous value of the cell of the change.
 * @param new_value: the new value of the cell of the change.
 * @return: the change that was created.
 */
Change* create_change(int row, int column, int prev_value, int new_value);

/**
 * Destroys the given change (frees all related memory).
 * @param change: the change to destroy.
 */
void destroy_change(Change *change);

/**
 * Creates a new empty move.
 * @return: the move that was created.
 */
Move* create_move();

/**
 * Destroys the given move (frees all related memory).
 * @param move: the move to destroy.
 */
void destroy_move(Move *move);

#endif
