cmake_minimum_required(VERSION 3.9)
project(lalr_alamain)

set(CMAKE_CXX_STANDARD 17)

set(CXX_STRICT_WARNINGS "-fno-elide-constructors -pedantic-errors -ansi -Wextra -Wall -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -Winit-self")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Werror ${CXX_STRICT_WARNINGS}")

add_executable(lalr_alamain
        main.cpp
        State.h
        Lexer.h Lexer.cpp
        Automata.h Automata.cpp
        Console.h
        HasPtr.h
        Symbol.h Symbol.cpp
        Symbols/TerminalSymbols.h
        Symbols/Val.h
        Symbols/Expr.h
        Transitions/Transition.h
        Transitions/Shift.h
        Transitions/Reduction.h
        Transitions/Reductions.h Transitions/Reductions.cpp
        Transitions/Shifts.h Transitions/Shifts.cpp
        )
