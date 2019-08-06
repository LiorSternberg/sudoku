cmake_minimum_required(VERSION 3.13)
project(final_project C)

set(CMAKE_C_STANDARD 90)

add_executable(final_project
        main.c
        MemoryError.c
        MemoryError.h
        Editor.h
        Editor.c
        GameManager.h
        GameManager.c
        Initializer.h
        Initializer.c
        parsing/Parser.h
        parsing/Parser.c
        Printer.h
        Printer.c
        Solver.h
        Solver.c
        UserHandler.h
        UserHandler.c
        logic/Backtracking.h
        logic/Backtracking.c
        logic/ILP.h
        logic/ILP.c
        parsing/Command.c
        parsing/Command.h
        parsing/validators.h
        parsing/validators.c
        components/Game.c
        components/Game.h
        components/StatesList.c
        components/StatesList.h
        components/Board.c
        components/Board.h
        components/Move.c components/Move.h components/List.c components/List.h)