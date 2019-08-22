#include <stdlib.h>
#include <libintl.h>
#include "Board.h"
#include "../MemoryError.h"
#include "List.h"


BoardCell* create_cell() {
    BoardCell *cell = malloc(sizeof(BoardCell));
    validate_memory_allocation("create_cell", cell);

    cell->val = CLEAR;
    cell->fixed = false;
    cell->erroneous = false;
    cell->neighbors = NULL;
    cell->conflicting = create_list();

    return cell;
}

void destroy_cell(BoardCell *cell) {
    if (cell->neighbors != NULL) {
        clear_list(cell->neighbors);
        destroy_list(cell->neighbors);
    }

    clear_list(cell->conflicting);
    destroy_list(cell->conflicting);
    free(cell);
}

BoardCell** create_row(int length) {
    int i;
    BoardCell **row = malloc(length * sizeof(BoardCell*));
    validate_memory_allocation("create_row", row);

    for (i=0; i < length; i++) {
        row[i] = create_cell();
    }

    return row;
}

void destroy_row(BoardCell **row, int length) {
    int i;
    for (i=0; i < length; i++) {
        destroy_cell(row[i]);
    }

    free(row);
}

Board* create_board(int rows_in_block, int columns_in_block){
    int i, dim;

    Board *board = malloc(sizeof(Board));
    validate_memory_allocation("create_board", board);

    dim = rows_in_block * columns_in_block;
    board->num_of_rows_in_block = rows_in_block;
    board->num_of_columns_in_block = columns_in_block;
    board->dim = dim;
    board->erroneous = false;
    board->solved = false;
    board->empty_count = 0;
    board->_errors_count = 0;

    BoardCell ***cells_arr = malloc(dim * sizeof(BoardCell**));
    validate_memory_allocation("create_board", board);

    for (i=0; i < dim; i++) {
        cells_arr[i] = create_row(dim);
    }

    board->cells_arr = cells_arr;
    return board;
}

void destroy_board(Board *board){
    int i;

    if (board == NULL) {
        return;
    }
    
    for (i=0; i < board->dim; i++) {
        destroy_row(board->cells_arr[i], board->dim);
    }

    free(board->cells_arr);
    free(board);
}


/* Query functions */

bool is_cell_fixed(Board *board, int row, int column) {
    return board->cells_arr[row][column]->fixed;
}

bool is_cell_empty(Board *board, int row, int column) {
    return board->cells_arr[row][column]->val == CLEAR;
}

int get_cell_value(Board *board, int row, int column) {
    return board->cells_arr[row][column]->val;
}

void get_block_indices(Board *board, int row, int column, int *r_start, int *r_end, int *c_start, int *c_end) {
    *r_start = row - (row % board->num_of_rows_in_block);
    *r_end = (row % board->num_of_rows_in_block) + board->num_of_rows_in_block;
    *c_start = column - (column % board->num_of_columns_in_block);
    *c_end = (column % board->num_of_columns_in_block) + board->num_of_columns_in_block;
}

List* generate_neighbors_list(Board *board, int row, int column) {
    int i, r_start, r_end, j, c_start, c_end;
    List *neighbors = create_list();

    /* row & column neighbors */
    for (i = 0; i < board->dim; i++) {
        if (i != column) {
            add(neighbors, board->cells_arr[row][i]);
        }
        if (i != row) {
            add(neighbors, board->cells_arr[i][column]);
        }
    }

    /* block neighbors */
    get_block_indices(board, row, column, &r_start, &r_end, &c_start, &c_end);
    for (i = r_start; i < r_end; i++) {
        for (j = c_start; j < c_end; j++) {
            if (i != row && j != column) {
                add(neighbors, board->cells_arr[i][j]);
            }
        }
    }
    return neighbors;
}

List* get_neighbors(Board *board, int row, int column) {
    if (board->cells_arr[row][column]->neighbors == NULL) {
        board->cells_arr[row][column]->neighbors = generate_neighbors_list(board, row, column);
    }

    reset_head(board->cells_arr[row][column]->neighbors);
    return board->cells_arr[row][column]->neighbors;
}

List* get_conflicting(Board *board, int row, int column) {
    reset_head(board->cells_arr[row][column]->conflicting);
    return board->cells_arr[row][column]->conflicting;
}

/* Board manipulation functions */

void add_conflict(Board *board, BoardCell *cell, BoardCell *conflicting_cell) {
    /* fixed cells are never erroneous */
    if (cell->fixed) {
        return;
    }

    if (is_empty(cell->conflicting)) {
        cell->erroneous = true;
        board->_errors_count++;
    }
    add(cell->conflicting, conflicting_cell);
}

void remove_conflict(Board *board, BoardCell *cell, BoardCell *conflicting_cell) {
    bool had_conflicts = !is_empty(cell->conflicting);

    delete(cell->conflicting, conflicting_cell);

    if (had_conflicts && is_empty(cell->conflicting)) {
        cell->erroneous = false;
        board->_errors_count--;
    }
}

void set_cell_value(Board *board, int row, int column, int value) {
    BoardCell *neighbor;
    List *neighbors;

    /* no action needed (value wasn't changed) */
    if (board->cells_arr[row][column]->val == value) {
        return;
    }

    neighbors = get_neighbors(board, row, column);

    do {
        neighbor = (BoardCell*) get_current_item(neighbors);
        if (neighbor->val == value) {
            add_conflict(board, board->cells_arr[row][column], neighbor);
            add_conflict(board, neighbor, board->cells_arr[row][column]);

        } else if (neighbor->val == board->cells_arr[row][column]->val) {
            remove_conflict(board, board->cells_arr[row][column], neighbor);
            remove_conflict(board, neighbor, board->cells_arr[row][column]);
        }
    } while (next(neighbors) == 0);

    board->cells_arr[row][column]->val = value;
}

bool fix_cell(Board *board, int row, int column) {
    BoardCell *conflicting_neighbor;
    List *conflicting = get_conflicting(board, row, column);
    int value = get_cell_value(board, row, column);

    /* validate there are no conflicting fixed neighbors */
    if (!is_empty(conflicting)) {
        do {
            conflicting_neighbor = (BoardCell*) get_current_item(conflicting);
            if (conflicting_neighbor->fixed == true) {
                return false;
            }
        } while (next(conflicting) == 0);
    }

    board->cells_arr[row][column]->fixed = true;
    return true;
}