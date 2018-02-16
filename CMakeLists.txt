cmake_minimum_required(VERSION 3.9)
project(lalr_alamain)

set(CMAKE_CXX_STANDARD 17)

set(CXX_STRICT_WARNINGS "-fno-elide-constructors -pedantic-errors -ansi -Wextra -Wall -Werror -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -Winit-self")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_STRICT_WARNINGS}")

# Clang
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Qunused-arguments")

add_executable(lalr_alamain
        main.cpp
        State.h
        Lexer.h Lexer.cpp
        Automata.h Automata.cpp
        Console.h
        HasPtr.h
        Symbol.h Symbol.cpp
        Symbols/TerminalSymbol.h
        Symbols/TerminalSymbols.h
        Symbols/NonTerminalSymbols.h
        Symbols/ValuedSymbol.h
        Transition.h
        Transitions/Reductions.cpp
        Transitions/Shifts.cpp
        Common.h Transitions/Transitions.h)
