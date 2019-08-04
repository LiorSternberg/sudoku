cmake_minimum_required(VERSION 3.13)
project(final_project C)

set(CMAKE_C_STANDARD 90)

add_executable(final_project main.c MemoryError.c MemoryError.h Editor.h Editor.c GameManager.h GameManager.c
        Initializer.h Initializer.c Parsing/Parser.h Parsing/Parser.c Printer.h Printer.c Solver.h Solver.c UserHandler.h UserHandler.c
        Logic/Backtracking.h Logic/Backtracking.c Logic/ILP.h Logic/ILP.c Parsing/Command.c Parsing/Command.h
        Parsing/validation.h Parsing/validation.c)