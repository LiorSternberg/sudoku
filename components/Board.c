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

    return cell;
}

void destroy_cell(BoardCell *cell) {
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


/* Query functions */

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

bool is_cell_fixed(Board *board, int row, int column) {
    return board->cells_arr[row][column]->fixed;
}

bool is_cell_empty(Board *board, int row, int column) {
    return board->cells_arr[row][column]->val == CLEAR;
}

int get_cell_value(Board *board, int row, int column) {
    return board->cells_arr[row][column]->val;
}

List* get_neighbors(Board *board, int row, int column) {
    int i, r_start, r_end, j, c_start, c_end;
    List *neighbors = create_list();

    r_start = row - (row % board->num_of_rows_in_block);
    r_end = (row % board->num_of_rows_in_block) + board->num_of_rows_in_block;
    c_start = column - (column % board->num_of_columns_in_block);
    c_end = (column % board->num_of_columns_in_block) + board->num_of_columns_in_block;

    for (i = r_start; i < r_end; i++) {
        for (j = c_start; j < c_end; j++) {
            add(neighbors, board->cells_arr[i][j]);
        }
    }
    return neighbors;
}


/* Board manipulation functions */

void set_cell_value(Board *board, int row, int column, int value) {
    board->cells_arr[row][column]->val = value;
}

bool fix_cell(Board *board, int row, int column) {
    BoardCell *neighbor;
    List *neighbors = get_neighbors(board, row, column);
    int value = get_cell_value(board, row, column);

    while ((neighbor = remove_last(neighbors)) != NULL) {
        if (neighbor->val == value && neighbor->fixed == true) {
            clear_list(neighbors);
            destroy_list(neighbors);
            return false;
        }
    }

    board->cells_arr[row][column]->fixed = true;
    destroy_list(neighbors);
    return true;
}