# Sudoku Software Project

### Main Algorithms:
- **ILP** - For accurately solving a puzzle. 
- **LP** - For estimating a probable solution.
- **Exhaustive Backtracking** - For counting the number of possible solutions.  

### Supported Actions:
| Action | Details |
|---------|-------------------------------------------------------|
| **solve \<path\>**                    | Starts a puzzle in *solve* mode. |
| **edit [\<path\>]**                   | Starts a puzzle in *edit* mode. If a path is not provided, starts a puzzle of default size (3x3). |
| **mark_errors \<set\>**               | Toggles the *mark_errors* flag (determines whether or not errors are marked). |
| **print_board**                       | Prints the board. |
| **set \<column\> \<row\> \<value\>**  | Sets the cell at the given coordinates to the given value. |
| **validate**                          | Validates the current board state using ILP. |
| **guess \<threshold\>**               | Guesses a solution the current board state using LP. Only fills guesses with probability over the given threshold. |
| **generate \<\#cells to fill\> \<\#cells to leave\>** | Generates a new puzzle by randomly filling *\#cells to fill* cells, solving the board (using ILP), and then clearing all but *\#cells to leave* randomly chosen cells. |
| **undo**                              | Undoes the previous move. |
| **redo**                              | Redoes the previous move. |
| **save \<path\>**                     | Saves the current game board to a file. |
| **hint \<column\> \<row\>**           | Gives the user a hint (the solution for the specified cell, determined by solving the board using ILP). |
| **guess_hint \<column\> \<row\>**     | Gives the user guesses for a hint (possible solutions and their probabilities, determined by solving the board using LP). |
| **num_solutions**                     | Prints the number of solutions for the current board state, determined by running the backtracking algorithm. |
| **autofill**                          | Automatically fills "obvious" values (cells with only one legal value). |
| **reset**                             | Undoes all moves made since loading the puzzle. |
| **exit**                              | Exits the game. |
