CC = gcc
OBJS = main.o GameManager.o Parser.o actions.o validators.o Printer.o Serializer.o Command.o Error.o Game.o StatesList.o Move.o Board.o List.o MemoryError.o
EXEC = sudoku
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors

$(EXEC): $(OBJS)
		$(CC) $(OBJS) -o $@
main.o: main.c GameManager.h io/Printer.h
		$(CC) $(COMP_FLAG) -c $*.c
GameManager.o: GameManager.c GameManager.h io/Parser.h io/validators.h io/Printer.h io/Command.h
		$(CC) $(COMP_FLAG) -c $*.c
Parser.o: io/Parser.c io/Parser.h io/validators.h logic/actions.h io/Command.h MemoryError.h
		$(CC) $(COMP_FLAG) -c io/$*.c
actions.o: logic/actions.c logic/actions.h io/Serializer.h io/Printer.h components/Game.h io/Command.h
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
Game.o: components/Game.c components/Game.h MemoryError.h components/StatesList.h components/Board.h
		$(CC) $(COMP_FLAG) -c components/$*.c
StatesList.o: components/StatesList.c components/StatesList.h components/Move.h components/List.h MemoryError.h
		$(CC) $(COMP_FLAG) -c components/$*.c
Move.o: components/Move.c components/Move.h components/List.h MemoryError.h
		$(CC) $(COMP_FLAG) -c components/$*.c
Board.o: components/Board.c components/Board.h components/List.h MemoryError.h
		$(CC) $(COMP_FLAG) -c components/$*.c
List.o: components/List.c components/List.h MemoryError.h
		$(CC) $(COMP_FLAG) -c components/$*.c
MemoryError.o: MemoryError.c MemoryError.h
		$(CC) $(COMP_FLAG) -c $*.c
clean:
		rm -f $(OBJS) $(EXEC)
