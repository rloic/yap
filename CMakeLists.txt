cmake_minimum_required(VERSION 3.9)
project(lalr_alamain)

set(CMAKE_CXX_STANDARD 17)

set(CXX_STRICT_WARNINGS "-fno-elide-constructors -pedantic-errors -ansi -Wextra -Wall -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -Winit-self")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g ${CXX_STRICT_WARNINGS}")

add_executable(lalr_alamain
        main.cpp
        State.h
        Symbol.h
        Lexer.cpp Lexer.h
        Automata.h Automata.cpp
        Console.h
        HasPtr.h
        Symbols/Expr.h
        Symbols/LPar.h
        Symbols/RPar.h
        Symbols/Plus.h
        Symbols/Mult.h
        Symbols/Val.h
        Symbols/Eof.h
        States.cpp States.h
        Symbol.cpp State.cpp Symbols/TerminalSymbols.h)
