#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parser.h"

#define MAX_ARGS 4
#define WHITESPACE " \t\r\n"


void parse_tokens(char *raw_command, Command *command) {
    char *token;
    char* tokens[MAX_ARGS];
    int num_of_args = 0;


    /* get the first token (the type of the command, if exists) */
    token = strtok(raw_command, WHITESPACE);
    if (token == NULL) {
        command->type = empty;
        return;
    }

    /* parse type */
    parse_type(command, token);


    /* walk through other tokens */
    token = strtok(NULL, WHITESPACE);
    while (token != NULL && num_of_args < MAX_ARGS) {
        tokens[num_of_args] = token;
        num_of_args++;
        token = strtok(NULL, WHITESPACE);
    }

    command->_parse_args(command, tokens, num_of_args);
}



