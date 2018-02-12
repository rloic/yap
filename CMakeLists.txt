cmake_minimum_required(VERSION 3.9)
project(lalr_alamain)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(lalr_alamain
        main.cpp
        State.h
        Symbol.h
        Lexer.cpp Lexer.h
        Automata.h Automata.cpp
        Console.h Console.cpp
        HasPtrs.h
        Symbols/Expr.h
        Symbols/LPar.h
        Symbols/RPar.h
        Symbols/Plus.h
        Symbols/Mult.h
        Symbols/Val.h
        Symbols/Eof.h
        States.cpp States.h
)
