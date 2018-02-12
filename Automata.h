#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "Lexer.h"
#include "State.h"

class Symbol;

class Automata {
public:
    explicit Automata(Lexer lexer, bool debug = false);

    virtual ~Automata() = default;

    void Read();

    void Shift(Symbol::Ptr symbol, State::Ptr state);

    void Reduce(int n, Symbol::Ptr symbol);

    Symbol::Ptr PopSymbol();

    void DebugStacks() const;

private:
    std::vector<Symbol::Ptr> mSymbols;
    std::vector<State::Ptr> mStates;
    Lexer mLexer;
    bool mDebug;
};
