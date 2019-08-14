#ifndef FINAL_PROJECT_PRINTER_H
#define FINAL_PROJECT_PRINTER_H

#include "../components/Board.h"

/** Printer:
 *   this module is responsible for printing the game board. */


/* Prints the sudoku board to stdout. */
void print(Board *board, bool mark_errors);

#endif
