#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <array>

#include "Lexer.h"
#include "State.h"

class Symbol;
class Transition;

class Automata {
public:
    explicit Automata(Lexer lexer, bool debug = false);

    virtual ~Automata() = default;

    void Read();

    void Shift(Symbol::Ptr symbol, State::Id state);

    void Reduce(int n, Symbol::Ptr symbol);

    Symbol::Ptr PopSymbol();

    void DebugStacks() const;

private:
    bool executeTransition(Symbol::Ptr symbol);

private:
    std::vector<Symbol::Ptr> mSymbolsStack;
    std::vector<State::Id> mStatesStack;
    Lexer mLexer;
    bool mDebug;

    using StateTransitions = std::array<Transition const *, Symbol::NB_SYMBOLS>;
    using TransitionTable = std::array<StateTransitions, State::NB_STATES>;
    TransitionTable transitions;

    using GotoTransitions = std::map<State::Id, State::Id>;
    GotoTransitions gotoTransitions;
};
