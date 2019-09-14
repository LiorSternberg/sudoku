CC = gcc
OBJS = main.o GameManager.o Parser.o actions.o validators.o Printer.o Serializer.o Command.o Error.o Backtracking.o ILP.o LP.o solver.o random.o Game.o StatesList.o Move.o Board.o List.o Stack.o MemoryError.o
EXEC = sudoku
COMP_FLAG = -ansi -O3 -Wall -Wextra -Werror -pedantic-errors
GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

all: $(OBJS)
	    $(CC) $(OBJS) $(GUROBI_LIB) -o $(EXEC)
$(EXEC): $(OBJS)
	    $(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm

main.o: main.c GameManager.h io/Printer.h logic/random.h
		$(CC) $(COMP_FLAG) -c $*.c
GameManager.o: GameManager.c GameManager.h io/Parser.h io/validators.h io/Printer.h io/Command.h
		$(CC) $(COMP_FLAG) -c $*.c
Parser.o: io/Parser.c io/Parser.h io/validators.h logic/actions.h io/Command.h MemoryError.h
		$(CC) $(COMP_FLAG) -c io/$*.c
actions.o: logic/actions.c logic/actions.h logic/Backtracking.h logic/LP.h logic/ILP.h io/Serializer.h io/Printer.h components/Game.h io/Command.h
		$(CC) $(COMP_FLAG) -c logic/$*.c
validators.o: io/validators.c io/validators.h components/Game.h io/Command.h MemoryError.h
		$(CC) $(COMP_FLAG) -c io/$*.c
Printer.o: io/Printer.c io/Printer.h components/Game.h io/Error.h MemoryError.h
		$(CC) $(COMP_FLAG) -c io/$*.c
Serializer.o: io/Serializer.c io/Serializer.h components/Game.h io/Error.h
		$(CC) $(COMP_FLAG) -c io/$*.c
Command.o: io/Command.c io/Command.h MemoryError.h components/Game.h io/Error.h
		$(CC) $(COMP_FLAG) -c io/$*.c
Error.o: io/Error.c io/Error.h MemoryError.h
		$(CC) $(COMP_FLAG) -c io/$*.c
Backtracking.o: logic/Backtracking.c logic/Backtracking.h components/Board.h components/Stack.h
		$(CC) $(COMP_FLAG) -c logic/$*.c
ILP.o: logic/ILP.c logic/ILP.h logic/random.h logic/solver.h components/Board.h components/StatesList.h MemoryError.h
		$(CC) $(COMP_FLAG) -c logic/$*.c
LP.o: logic/LP.c logic/LP.h components/Board.h components/StatesList.h MemoryError.h
		$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c logic/$*.c
solver.o: logic/solver.c logic/solver.h logic/random.h components/Board.h components/StatesList.h MemoryError.h
		$(CC) $(COMP_FLAG) $(GUROBI_COMP) -c logic/$*.c
random.o: logic/random.c logic/random.h
		$(CC) $(COMP_FLAG) -c logic/$*.c
Game.o: components/Game.c components/Game.h MemoryError.h components/StatesList.h components/Board.h
		$(CC) $(COMP_FLAG) -c components/$*.c
StatesList.o: components/StatesList.c components/StatesList.h components/Board.h components/Move.h components/List.h MemoryError.h
		$(CC) $(COMP_FLAG) -c components/$*.c
Move.o: components/Move.c components/Move.h components/List.h MemoryError.h
		$(CC) $(COMP_FLAG) -c components/$*.c
Board.o: components/Board.c components/Board.h components/List.h MemoryError.h
		$(CC) $(COMP_FLAG) -c components/$*.c
List.o: components/List.c components/List.h MemoryError.h
		$(CC) $(COMP_FLAG) -c components/$*.c
Stack.o: components/Stack.c components/Stack.h MemoryError.h
		$(CC) $(COMP_FLAG) -c components/$*.c
MemoryError.o: MemoryError.c MemoryError.h
		$(CC) $(COMP_FLAG) -c $*.c
clean:
		rm -f $(OBJS) $(EXEC)
