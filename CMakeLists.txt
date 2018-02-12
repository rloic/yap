cmake_minimum_required(VERSION 3.9)
project(lalr_alamain)

set(CMAKE_CXX_STANDARD 17)

add_executable(lalr_alamain
        main.cpp
        State.h
        Symbol.h
        Lexer.cpp Lexer.h
        Automata.h Automata.cpp
        Console.h Console.cpp
        HasPtrs.h
        SyntaxTree.h SyntaxTree.cpp
#        States/State0.h
#        States/State1.h
#        States/State2.h
#        States/State3.h
#        States/State4.h
#        States/State5.h
#        States/State6.h
#        States/State7.h
#        States/State8.h
#        States/State9.h
        Symbols/Expr.h
        Symbols/LPar.h
        Symbols/RPar.h
        Symbols/Plus.h
        Symbols/Mult.h
        Symbols/Val.h
        Symbols/Eof.h
        States.cpp States.h)