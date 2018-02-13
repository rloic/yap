#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "Lexer.h"
#include "State.h"

class Symbol;
class Transition;

class Automata {
public:
    explicit Automata(Lexer lexer, bool debug = false);

    virtual ~Automata() = default;

    void Read();

    void Shift(Symbol::Ptr symbol, State state);

    void Reduce(int n, Symbol::Ptr symbol);

    Symbol::Ptr PopSymbol();

    void DebugStacks() const;

private:
    bool executeTransition(Symbol::Ptr symbol);

private:
    std::vector<Symbol::Ptr> mSymbolsStack;
    std::vector<State> mStatesStack;
    Lexer mLexer;
    bool mDebug;

    using StateTransitions = std::map<Symbol::Id, Transition const *>;
    using TransitionTable = std::map<State, StateTransitions>;
    TransitionTable transitions;

    using GotoTransitions = std::map<State, State>;
    GotoTransitions gotoTransitions;
};
