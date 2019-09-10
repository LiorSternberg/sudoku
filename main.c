#include <stdlib.h>
#include <stdio.h>

#include "GameManager.h"
#include "io/Printer.h"
#include "logic/ILP.h"

int main() {
/*    Command *command = NULL;*/
/*    Game *game = create_game();*/
    announce_game_start();

    printf("0\n");
    gurobi_solver(create_board(3, 3));
    /* Ty running:
     *
     * solve ../test_files/boards/board_2_5_with_fixed.txt
     * solve ../test_files/boards/board_2_2_almost_full.txt
     * solve ../test_files/boards/board_2_2_four_solutions_with_fixed.txt
     * solve ../test_files/boards/board_5_5_two_solutions.txt
     * solve test_files/boards/board_2_5_with_fixed.txt
     */

/*
    while (!game->over) {
        play_turn(game, command);
    }

    destroy_game(game);
*/
    return 0;
}