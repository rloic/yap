/*
 * MIT License
 *
 * Copyright (c) 2018 insa.4if.hexanome_kalate
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

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

    inline TransitionAdder &Add(State fromState, Symbol::Id fromSymbol, State toState);

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

    void AddGoToTransition(State fromState, Symbol::Id fromSymbol, State toState);

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

    using StateTransitions = std::map<Symbol::Id, Transition const *>;
    using TransitionTable = std::map<State, StateTransitions>;
    TransitionTable transitions;

    using SymbolTransitions = std::map<Symbol::Id, State>;
    using GotoTransitions = std::map<State, SymbolTransitions>;
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

TransitionAdder &TransitionAdder::Add(State fromState, Symbol::Id fromSymbol, State toState) {
    mAutomata.AddGoToTransition(fromState, fromSymbol, toState);
    return *this;
}

} // namespace YAP
