#include <stdlib.h>
#include <libintl.h>
#include "Board.h"
#include "../MemoryError.h"


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
    for (i=0; i < board->dim; i++) {
        destroy_row(board->cells_arr[i], board->dim);
    }

    free(board->cells_arr);
    free(board);
}
