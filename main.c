#include <stdlib.h>
#include <stdio.h>
#include "parsing/Parser.h"

#define MAX_CMD_LEN (256)

void get_user_command(Command *command) {
    char raw_command[MAX_CMD_LEN] = {0};

    fgets(raw_command, MAX_CMD_LEN, stdin);
    parse_tokens(raw_command,  command);
}

int main() {
    printf("Hello, World!\n");

    Command *command = malloc(sizeof(Command));
    get_user_command(command);

    printf("Hello, World!\n");
    return 0;
}