#ifndef FINAL_PROJECT_VALIDATION_H
#define FINAL_PROJECT_VALIDATION_H

#include "Command.h"
#include "../components/Game.h"

/** validators:
 *   this module is responsible for the validation of structured commands.
 *   It contains the type-specific validators for commands that require custom
 *   validations, and the main validation function used to validate a Command. */


/* Command-specific validators (used by the Parser at the configuration stage) */

/**
 * The custom validator for the solve command. In case the command is found to
 * be invalid (if the game-mode is illegal for this command for example), the
 * command's Error is updated to reflect the issue.
 * @param command: the Command to validate.
 * @param game: the current game.
 */
void solve_validator(Command *command, Game *game);


/**
 * The custom validator for the edit command. In case the command is found to
 * be invalid (if the game-mode is illegal for this command for example), the
 * command's Error is updated to reflect the issue.
 * @param command: the Command to validate.
 * @param game: the current game.
 */
void edit_validator(Command *command, Game *game);

/**
 * The custom validator for the mark_errors command. In case the command is found to
 * be invalid (if the game-mode is illegal for this command for example), the
 * command's Error is updated to reflect the issue.
 * @param command: the Command to validate.
 * @param game: the current game.
 */
void mark_errors_validator(Command *command, Game *game);

/**
 * The custom validator for the set command. In case the command is found to
 * be invalid (if the game-mode is illegal for this command for example), the
 * command's Error is updated to reflect the issue.
 * @param command: the Command to validate.
 * @param game: the current game.
 */
void set_validator(Command *command, Game *game);

/**
 * The custom validator for the validate command. In case the command is found to
 * be invalid (if the game-mode is illegal for this command for example), the
 * command's Error is updated to reflect the issue.
 * @param command: the Command to validate.
 * @param game: the current game.
 */
void validate_validator(Command *command, Game *game);

/**
 * The custom validator for the guess command. In case the command is found to
 * be invalid (if the game-mode is illegal for this command for example), the
 * command's Error is updated to reflect the issue.
 * @param command: the Command to validate.
 * @param game: the current game.
 */
void guess_validator(Command *command, Game *game);

/**
 * The custom validator for the generate command. In case the command is found to
 * be invalid (if the game-mode is illegal for this command for example), the
 * command's Error is updated to reflect the issue.
 * @param command: the Command to validate.
 * @param game: the current game.
 */
void generate_validator(Command *command, Game *game);

/**
 * The custom validator for the undo command. In case the command is found to
 * be invalid (if the game-mode is illegal for this command for example), the
 * command's Error is updated to reflect the issue.
 * @param command: the Command to validate.
 * @param game: the current game.
 */
void undo_validator(Command *command, Game *game);

/**
 * The custom validator for the redo command. In case the command is found to
 * be invalid (if the game-mode is illegal for this command for example), the
 * command's Error is updated to reflect the issue.
 * @param command: the Command to validate.
 * @param game: the current game.
 */
void redo_validator(Command *command, Game *game);

/**
 * The custom validator for the save command. In case the command is found to
 * be invalid (if the game-mode is illegal for this command for example), the
 * command's Error is updated to reflect the issue.
 * @param command: the Command to validate.
 * @param game: the current game.
 */
void save_validator(Command *command, Game *game);

/**
 * The custom validator for the hint command. In case the command is found to
 * be invalid (if the game-mode is illegal for this command for example), the
 * command's Error is updated to reflect the issue.
 * @param command: the Command to validate.
 * @param game: the current game.
 */
void hint_validator(Command *command, Game *game);

/**
 * The custom validator for the guess_hint command. In case the command is found to
 * be invalid (if the game-mode is illegal for this command for example), the
 * command's Error is updated to reflect the issue.
 * @param command: the Command to validate.
 * @param game: the current game.
 */
void guess_hint_validator(Command *command, Game *game);

/**
 * The custom validator for the num_solutions command. In case the command is found to
 * be invalid (if the game-mode is illegal for this command for example), the
 * command's Error is updated to reflect the issue.
 * @param command: the Command to validate.
 * @param game: the current game.
 */
void num_solutions_validator(Command *command, Game *game);

/**
 * The custom validator for the autofill command. In case the command is found to
 * be invalid (if the game-mode is illegal for this command for example), the
 * command's Error is updated to reflect the issue.
 * @param command: the Command to validate.
 * @param game: the current game.
 */
void autofill_validator(Command *command, Game *game);

/**
 * Validates the command - In case the command is found to be invalid (if the
 * game-mode is illegal for this command for example), the command's Error is
 * updated to reflect the issue.
 * @param command: the Command to validate.
 * @param game: the current game.
 */
void validate_command(Command *command, Game *game);

#endif
