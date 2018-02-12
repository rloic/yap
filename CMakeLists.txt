cmake_minimum_required(VERSION 3.9)
project(lalr_alamain)

set(CMAKE_CXX_STANDARD 17)

add_executable(lalr_alamain main.cpp State.h Symbol.h Automata.h Console.h Console.cpp HasPtrs.h)