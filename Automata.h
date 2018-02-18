#pragma once

#include <type_traits>
#include <iostream>
#include <cassert>
#include <vector>
#include <array>
#include <tuple>
#include <map>

#include "Lexer.h"
#include "State.h"

class Symbol;
class Transition;

class Automata {
public:
    explicit Automata(Lexer lexer, bool debug = false);

    virtual ~Automata() = default;

    void Read();

    template<typename Transition>
    void AddTransition(State::Id state, Symbol::Id symbol);

    void Shift(Symbol::Ptr symbol, State::Id state);

    void Reduce(int n, Symbol::Ptr symbol);

    Symbol::Ptr PopSymbol();

    template<typename SymbolType, bool Assert = true>
    auto PopSymbolAs();

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

template<class TransitionClass>
void Automata::AddTransition(State::Id state, Symbol::Id symbol) {
    static_assert(
            std::is_base_of<Transition, TransitionClass>::value,
            "Derived not derived from BaseClass"
    );
    transitions[state][symbol] = TransitionClass::InstancePtr();
}

template<typename SymbolType, bool Assert = true>
auto Automata::PopSymbolAs() {
    static_assert(
            std::is_base_of<Symbol, SymbolType>::value,
            "SymbolType must be a child of Symbol!"
    );

    Symbol::Ptr s = PopSymbol();
    auto r = std::dynamic_pointer_cast<SymbolType>(s);

    if constexpr (Assert) {
        assert(r && "The popped symbol is of wrong type!");
    }

    return r;
}
