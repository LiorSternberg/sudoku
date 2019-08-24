CC = gcc
OBJS = main.o GameManager.o io/Parser.o logic/actions.o io/validators.o io/Printer.o io/Command.o io/Error.o components/Game.o components/StatesList.o components/Move.o components/Board.o components/List.o MemoryError.o
EXEC = sudoku
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors

$(EXEC): $(OBJS)
		$(CC) $(OBJS) -o $@
main.o: main.c GameManager.h io/Printer.h
		$(CC) $(COMP_FLAG) -c $*.c
GameManager.o: GameManager.c GameManager.h io/Parser.h io/validators.h io/Printer.h io/Command.h
		$(CC) $(COMP_FLAG) -c $*.c
io/Parser.o: io/Parser.c io/Parser.h io/validators.h logic/actions.h io/Command.h MemoryError.h
		$(CC) $(COMP_FLAG) -c $*.c
logic/actions.o: logic/actions.c logic/actions.h components/Game.h io/Command.h io/Serializer.h io/Printer.h
		$(CC) $(COMP_FLAG) -c $*.c
io/validators.o: io/validators.c io/validators.h components/Game.h io/Command.h MemoryError.h
		$(CC) $(COMP_FLAG) -c $*.c
io/Printer.o: io/Printer.c io/Printer.h components/Game.h io/Error.h MemoryError.h
		$(CC) $(COMP_FLAG) -c $*.c
io/Command.o: io/Command.c io/Command.h MemoryError.h components/Game.h io/Error.h
		$(CC) $(COMP_FLAG) -c $*.c
io/Error.o: io/Error.c io/Error.h MemoryError.h
		$(CC) $(COMP_FLAG) -c $*.c
components/Game.o: components/Game.c components/Game.h MemoryError.h components/StatesList.h components/Board.h
		$(CC) $(COMP_FLAG) -c $*.c
components/StatesList.o: components/StatesList.c components/StatesList.h components/Move.h components/List.h MemoryError.h
		$(CC) $(COMP_FLAG) -c $*.c
components/Move.o: components/Move.c components/Move.h components/List.h MemoryError.h
		$(CC) $(COMP_FLAG) -c $*.c
components/Board.o: components/Board.c components/Board.h components/List.h MemoryError.h
		$(CC) $(COMP_FLAG) -c $*.c
components/List.o: components/List.c components/List.h MemoryError.h
		$(CC) $(COMP_FLAG) -c $*.c
MemoryError.o: MemoryError.c MemoryError.h
		$(CC) $(COMP_FLAG) -c $*.c
clean:
		rm -f $(OBJS) $(EXEC)
