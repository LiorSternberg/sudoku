#include <stdlib.h>
#include <stdio.h>
#include "parsing/Parser.h"
#include "UserHandler.h"

int main() {
    printf("Hello, World!\n");

    Command *command = create_command();
    Game *game = create_game();

    get_user_command(game, command);
    printf("Hello, World!\n");

    destroy_command(command);
    destroy_game(game);
    return 0;
}