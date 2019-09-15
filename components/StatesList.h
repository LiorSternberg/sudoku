#ifndef FINAL_PROJECT_STATESLIST_H
#define FINAL_PROJECT_STATESLIST_H

#include "List.h"
#include "Move.h"
#include "Board.h"

/** StatesList:
 *
 *  The component is used to manage the states of the game between turns.
 *  Holds a list of Moves, and allows to traverse the moves, undo or redo them.
 */


typedef struct {
    List *moves;
} States;

/**
 * Creates a new states list.
 * @return: the states list that was created.
 */
States* create_states_list();

/**
 * Destroys the states list (frees all related memory).
 * @param states: the list to destroy.
 */
void destroy_states_list(States *states);

/**
 * Clears the states list (destroys all moves).
 * To be used in case of starting a new game with an empty state, or
 * before destroying the states list.
 * @param states: the states list to clear.
 */
void clear_states_list(States *states);

/**
 * Adds a new empty Move to the states list.
 * @param states: the states list to add a move to.
 */
void add_new_move(States *states);

/**
 * Deletes the last move that was added to the states list.
 * @param board: the board to undo the move over.
 * @param states: the current states list.
 */
void delete_last_move(Board *board, States *states);

/**
 * Adds a Change to the current Move in the given states list, based on the row,
 * column and values (previous and new) that were supplied.
 * @param states: the states list to add the change to.
 * @param row: the row of the cell that was changed
 * @param column: the column of the cell that was changed.
 * @param prev_val: the previous value of the cell that was changed.
 * @param new_val: the new value of the cell that was changed.
 * @return: the new Change that was created.
 */
Change* add_change(States *states, int row, int column, int prev_val, int new_val);

/**
 * Clears the redo part of the states list.
 * @param states: the current states list.
 */
void clear_redo(States *states);

/**
 * Given a Change, sets it to the board (applies the change).
 * @param board: the board to apply the change to.
 * @param change: the change that is to be applied.
 */
void set_change(Board *board, Change *change);

/**
 * Given a Change, resets it (reverts the change).
 * @param board: the board to apply the change to.
 * @param change: the change that is to be reverted.
 */
void reset_change(Board *board, Change *change);

/**
 * Given a Move, resets it (reverts all the changes of the move,
 * and clears the move's changes list).
 * @param board: the board to apply the changes to.
 * @param move: the move that is to be reverted.
 */
void reset_move(Board *board, Move *move);

/**
 * Creates a new change, sets it to the board, and adds it to the states list.
 * @param board: the board to apply the change to.
 * @param states: the current states list.
 * @param row: the row of the cell that is to be changed
 * @param column: the column of the cell that is to be changed.
 * @param new_value: the new value of the cell that is to be changed.
 */
void make_change(Board *board, States *states, int row, int column, int new_value);

#endif
