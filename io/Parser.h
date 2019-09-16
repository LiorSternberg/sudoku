#ifndef FINAL_PROJECT_PARSER_H
#define FINAL_PROJECT_PARSER_H


#include "Command.h"

/** Parser:
 *   this module is responsible for parsing raw commands (text entered by the user)
 *   into structured Commands.
 *
 *  [Note: errors that are not parsing errors (i.e. not related to the type or number
 *   of arguments) will not be recognized by the parser. Use the 'validate_command'
 *   function for more comprehensive validations.] */


/**
 * Given the raw command entered by the player, parses it into a structured
 * Command containing all relevant information.
 * If any parsing errors occur, a relevant error message will be added to
 * the Command.
 * @param raw_command: the text the user entered.
 * @param command: the command to set according to the parsed data.
 * @param game: the current game.
 */
void parse_command(char *raw_command, Command *command, Game *game);

#endif
