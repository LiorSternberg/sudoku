#ifndef FINAL_PROJECT_BOARD_H
#define FINAL_PROJECT_BOARD_H

#include <stdbool.h>

#define CLEAR (0)

typedef struct {
    int val;
    bool fixed;
    bool erroneous;
} game_cell;

typedef struct {
    int dim;
    int num_of_rows_in_block;
    int num_of_columns_in_block;
    game_cell cells_arr[][];
    bool solved;
} Board;


/* Alert of a failed memory allocation, and exit */
void report_memory_allocation_error(char* function_name);

/* Validate that a memory allocation was successful. If not, report failure */
void validate_memory_allocation(char* function_name, void *p);

/* Initialize the given board:
 * set the dimension fields.
 * set the cells values to CLEAR, which means that the board is empty.
 * */
void init_empty_board(Board *board, int dim, int rows_in_block, int columns_in_block);

void destroy_board(Board *board);

#endif
