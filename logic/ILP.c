#include "ILP.h"

#define UNUSED(x) (void)(x)

bool solve_puzzle(Board *board) {
    /* TODO: actually implement this, and then remove the UNUSED and
     * change return value to be meaningful :) */
    UNUSED(board);
    return true;
}

int get_cell_solution(const Board *board, int row, int column) {
    Board* copy = get_board_copy(board);
    int cell_solution = 0;

    if (!solve_puzzle(copy)) {
        return ERROR_VALUE;
    }

    cell_solution = get_cell_value(copy, row, column);
    destroy_board(copy);
    return cell_solution;
}

bool is_board_solvable(const Board *board) {
    /* TODO: actually implement this, and then remove the UNUSED and
     * change return value to be meaningful :) */
    UNUSED(board);
    return true;
}

bool generate_puzzle(Board *board, States *states, int num_to_fill, int num_to_leave) {
    /* TODO: Tslil please make sure that when you make the actual changes to
     * the board you do it by using the "make_change" function, and not just
     * by setting the value to the board cell. This is needed in order to be
     * able to undo/redo the move of the 'guess' command. Note that you don't
     * need to do anything else to support the undo/redo list, the rest will
     * happen automatically.
     * Also, for undoing all the changes you've made (and resetting the board
     * to it's original state (before trying to generate a puzzle) you should
     * use the "reset_move" function. it will do all the work for you and also
     * maintain the undo/redo list.
     * So your flow should be: "make_change", "make_change",
     * "make_change"... oops! there's a problem with this puzzle: "reset_move",
     * and now you can "make_change", "make_change"... again :) */

    /* TODO: actually implement this, and then remove the UNUSED and
     * change return value to be meaningful :) */
    UNUSED(board);
    UNUSED(num_to_fill);
    UNUSED(num_to_leave);
    return true;
}

