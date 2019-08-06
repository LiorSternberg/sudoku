#include <stdlib.h>
#include <libintl.h>
#include "Board.h"

void report_memory_allocation_error(char* function_name) {
    printf("Error: function \"%s\" has failed\n", function_name);
    exit(1);
}

void validate_memory_allocation(char* function_name, void *p) {
    if (p == NULL) {
        report_memory_allocation_error(function_name);
    }
}

void init_empty_board(Board *board, int dim, int rows_in_block, int columns_in_block){
    int i, j;

    board->num_of_rows_in_block = rows_in_block;
    board->num_of_columns_in_block = columns_in_block;
    board->dim = dim;

    board->cells_arr = calloc(dim*dim, sizeof(game_cell));
    validate_memory_allocation("init_empty_board", board->cells_arr);

    for (i=0; i < dim; i++) {
        for (j=0; j < dim; j++) {
            board->cells_arr[i][j].val = CLEAR;
            board->cells_arr[i][j].fixed = false;
            board->cells_arr[i][j].erroneous = false;
        }
    }

}

void destroy_board(Board *board){
    free(board->cells_arr);
}
