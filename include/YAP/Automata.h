#pragma once

#include <type_traits>
#include <iostream>
#include <cassert>
#include <vector>
#include <array>
#include <tuple>
#include <map>

#include <YAP/Lexer.h>
#include <YAP/State.h>
#include <YAP/Common.h>

namespace YAP {

class Symbol;
class Transition;
class Automata;

class TransitionAdder {
public:
    template<typename Transition>
    inline TransitionAdder &Add(State state, Symbol::Id symbol);

    inline TransitionAdder &Add(State from, State to);

private:
    friend class Automata;

    explicit TransitionAdder(Automata &automata) : mAutomata{automata} {}

private:
    Automata &mAutomata;
};

class Automata {
public:
    explicit Automata(Lexer lexer, bool debug = false);

    virtual ~Automata() = default;

    Symbol::Ptr Read();

    template<typename Transition>
    void AddTransition(State state, Symbol::Id symbol);

    TransitionAdder AddTransitions();

    void AddGoToTransition(State from, State to);

    void Shift(Symbol::Ptr symbol, State state);

    void Reduce(int n, Symbol::Ptr symbol);

    void PopSymbol();

    template<typename SymbolType, bool Assert = true>
    auto PopSymbolAs();

    void DebugStacks() const;

private:
    bool executeTransition(Symbol::Ptr symbol);

private:
    std::vector<Symbol::Ptr> mSymbolsStack;
    std::vector<State> mStatesStack;
    Lexer mLexer;
    bool mDebug;

    using StateTransitions = std::array<Transition const *, Symbol::NB_SYMBOLS>;
    using TransitionTable = std::map<State, StateTransitions>;
    TransitionTable transitions;

    using GotoTransitions = std::map<State, State>;
    GotoTransitions goToTransitions;
};

template<class TransitionClass>
void Automata::AddTransition(State state, Symbol::Id symbol) {
    static_assert(
            std::is_base_of<Transition, TransitionClass>::value,
            "TransitionClass must be a child of Transition."
    );
    transitions[state][symbol] = TransitionClass::InstancePtr();
}

template<typename SymbolType, bool Assert = true>
auto Automata::PopSymbolAs() {
    static_assert(
            std::is_base_of<Symbol, SymbolType>::value,
            "SymbolType must be a child of Symbol!"
    );

    // TODO: Use a Result class
    assert(!mSymbolsStack.empty() && "Can't pop as the stack is empty.");

    Symbol::Ptr s = mSymbolsStack.back();
    mSymbolsStack.pop_back();
    auto r = std::dynamic_pointer_cast<SymbolType>(s);

    if constexpr (Assert) {
        assert(r && "The popped symbol is of wrong type!");
    }

    return r;
}

template<typename Transition>
TransitionAdder &TransitionAdder::Add(State state, Symbol::Id symbol) {
    mAutomata.AddTransition<Transition>(state, symbol);
    return *this;
}

TransitionAdder &TransitionAdder::Add(State from, State to) {
    mAutomata.AddGoToTransition(from, to);
    return *this;
}

} // namespace YAP
