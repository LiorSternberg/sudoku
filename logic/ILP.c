#include <stdlib.h>

#include "ILP.h"
#include "solver.h"
#include "../MemoryError.h"
#include "random.h"

#define UNUSED(x) (void)(x)
#define MAX_TRIALS (1000)


bool solve_puzzle(Board *board, States *states) {
    return gurobi_solver(board, states, integer, solve_board, NULL, 1.0);
}

int get_cell_solution(const Board *board, int row, int column) {
    Board* copy = get_board_copy(board);
    int cell_solution;

    if (!solve_puzzle(copy, NULL)) {
        destroy_board(copy);
        return ERROR_VALUE;
    }

    cell_solution = get_cell_value(copy, row, column);
    destroy_board(copy);
    return cell_solution;
}

bool is_board_solvable(const Board *board) {
    Board* copy = get_board_copy(board);
    bool solvable = solve_puzzle(copy, NULL);

    destroy_board(copy);
    return solvable;
}

/* Gets the row & column coordinates from the board cell index. */
void get_coordinates(int cell_index, int dim, int *row, int *column) {
    *column = cell_index % dim;
    *row = cell_index / dim;
}

/* Returns an array of the indices of empty cells in the board. */
int* get_board_empty_cells_indices(Board *board) {
    int i, row, column, counter = 0, *board_indices = malloc(board->empty_count * sizeof(int));
    validate_memory_allocation("get_random_empty_cells", board_indices);

    for (i = 0; i < board->dim * board->dim; i++) {
        get_coordinates(i, board->dim, &row, &column);
        if (is_cell_empty(board, row, column)) {
            board_indices[counter] = i;
            counter++;
        }

        if (counter == board->empty_count) {
            break;
        }
    }
    return board_indices;
}

/* Fills the given cell with a random legal value. Returns false if no legal
 * value exists, and true on success. */
bool fill_cell_with_random_value(Board *board, States *states, bool *marks, int row, int column) {
    int i, rand_index, possible_values_counter = 0;

    mark_neighboring_values(board, marks, row, column);
    /* count possible values */
    for (i = 0; i < board->dim; i++) {
        if (!marks[i]) {
            possible_values_counter++;
        }
    }

    if (possible_values_counter == 0) {
        return false;
    }

    /* fill cell with a random legal value */
    rand_index = get_rand_index(possible_values_counter);
    for (i = 0; i < board->dim; i++) {
        if (!marks[i]) {
            if (rand_index == 0) {
                make_change(board, states, row, column, i+1);
                return true;
            }
            rand_index--;
        }
    }
    return false;
}


/* Randomly chooses empty cells and fills them with legal values. */
bool fill_board_randomly(Board *board, States *states, bool *marks, int num_to_fill) {
    int i, row, column, trial_counter = 0, *indices_to_fill;
    bool trial_success = true;

    indices_to_fill = get_board_empty_cells_indices(board);
    while (trial_counter < MAX_TRIALS) {
        trial_counter++;
        trial_success = true;
        shuffle(indices_to_fill, num_to_fill, board->empty_count);

        for (i = 0; i < num_to_fill; i++) {
            get_coordinates(indices_to_fill[i], board->dim, &row, &column);

            if (!fill_cell_with_random_value(board, states, marks, row, column)) {
                trial_success = false;
                reset_move(board, (Move*) get_current_item(states->moves));
                break;
            }
        }
        if (!trial_success) {
            continue;
        }

        if (solve_puzzle(board, states)) {
            break;
        }
        reset_move(board, (Move*) get_current_item(states->moves));
    }

    free(indices_to_fill);
    return trial_success;
}


/* Randomly chooses cells to clear, and leaves the rest. */
void clear_board_randomly(Board *board, States *states, int num_to_leave) {
    int i, row, column, size = board->dim * board->dim, num_to_clear = size - num_to_leave;
    int *board_indices = malloc(size * sizeof(int));
    validate_memory_allocation("clear_board_randomly", board_indices);

    for (i = 0; i < size; i++) {
        board_indices[i] = i;
    }

    shuffle(board_indices, num_to_clear, size);
    for (i = 0; i < num_to_clear; i++) {
        get_coordinates(board_indices[i], board->dim, &row, &column);
        make_change(board, states, row, column, CLEAR);
    }
    free(board_indices);
}

bool generate_puzzle(Board *board, States *states, int num_to_fill, int num_to_leave) {
    bool *marks;

    marks = malloc(board->dim * sizeof(bool));
    validate_memory_allocation("generate_puzzle", marks);

    if (!fill_board_randomly(board, states, marks, num_to_fill)) {
        free(marks);
        return false;
    }
    clear_board_randomly(board, states, num_to_leave);
    free(marks);
    return true;
}


