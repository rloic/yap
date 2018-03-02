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

#include <YAP/Automaton.h>

#include <YAP/Common.h>
#include <YAP/Transition.h>

namespace YAP {

Automaton::Automaton(Lexer lexer, bool debug)
        : mLexer{lexer},
          mDebug{debug},
          transitions{},
          goToTransitions{}
{}

Symbol::Ptr Automaton::Read(State rootState) {
    mStatesStack.emplace_back(rootState);
    if (mDebug) DebugStacks();
    Symbol::Ptr current;
    do {
        if (mDebug) {
            using namespace Colors;
            std::cout << bold << blue << "[Debug] " << reset
                      << grey << "------------------------------------------" << reset << std::endl;
        }
        current = mLexer.GetNext();
        if (mDebug) {
            using namespace Colors;
            std::cout << bold << blue << "[Debug] " << reset
                      << grey << "Read symbol: " << reset
                      << cyan << current << reset
                      << std::endl;
            DebugStacks();
        }
    } while (executeTransition(current));

    return mSymbolsStack.empty() ? Symbol::Ptr() : mSymbolsStack.back();
}

TransitionAdder Automaton::AddTransitions() {
    return TransitionAdder(*this);
}

void Automaton::AddGoToTransition(State fromState, Symbol::Id fromSymbol, State toState) {
    goToTransitions[fromState][fromSymbol] = toState;
}

void Automaton::Shift(Symbol::Ptr symbol, State state) {
    mSymbolsStack.push_back(symbol);
    mStatesStack.push_back(state);

    mLexer.MoveNext();
}

void Automaton::Reduce(int n, Symbol::Ptr symbol) {
    for (int i = 0; i < n; ++i) {
        mStatesStack.pop_back();

        // Symbols are popped in the states' transitions
    }
    mSymbolsStack.push_back(symbol);
    auto symbolColumn = goToTransitions.find(mStatesStack.back());
    if (symbolColumn == goToTransitions.end()
        || symbolColumn->second.find(symbol->GetId()) == symbolColumn->second.end()) { // Missing transition
        using namespace Colors;
        std::cout << bold << red << "[Critical] " << reset
                  << red << "missing goto transition: " << reset
                  << cyan << "(State(" << mStatesStack.back() << ')'
                  << ", " << symbol << ')' << reset
                  << std::endl;
        exit(1);
    }
    if (mDebug) {
        using namespace Colors;
        std::cout << bold << blue << "[Debug] " << reset
                  << blue << "using goto transition: " << reset
                  << cyan << "(State(" << mStatesStack.back() << ')'
                  << ", " << symbol << ')' << reset
                  << yellow << " => State(" << goToTransitions[mStatesStack.back()][symbol->GetId()] << ')' << reset
                  << std::endl;
    }
    mStatesStack.push_back(goToTransitions[mStatesStack.back()][symbol->GetId()]);
}

void Automaton::MoveNext() {
    mLexer.MoveNext();
}

void Automaton::PopSymbol() {
    mSymbolsStack.pop_back();
}

void Automaton::DebugStacks() const {
    using namespace Colors;

    std::cout << bold << blue << "[Debug] " << reset
              << magenta << mStatesStack.size() << " states:" << reset;
    for (auto &state : mStatesStack) {
        std::cout << " " << cyan << state << reset;
    }
    std::cout << std::endl;
    std::cout << bold << blue << "[Debug] " << reset
              << magenta << mSymbolsStack.size() << " symbols:" << reset;
    for (auto &symbol : mSymbolsStack) {
        std::cout << " " << cyan << symbol << reset;
    }
    std::cout << std::endl;
}

bool Automaton::executeTransition(Symbol::Ptr symbol) {
    if (transitions.find(mStatesStack.back()) == transitions.end()) { // Missing transition
        using namespace Colors;
        std::cout << bold << red << "[Critical] " << reset
                  << red << "missing transition: " << reset
                  << cyan << "(State(" << mStatesStack.back() << ')'
                  << ", " << symbol << ')' << reset
                  << std::endl;
        exit(1);
    }
    StateTransitions const& availableTransitions = transitions.at(mStatesStack.back());
    Transition const * transition{nullptr};
    auto it = availableTransitions.find(symbol->GetId());
    if (it == availableTransitions.end()) {
        transition = SkipUnexpectedTransition::InstancePtr();
        mLexer.MoveNext();
    } else {
        transition = it->second;
    }
    if (mDebug) {
        using namespace Colors;
        std::cout << bold << blue << "[Debug] " << reset
                  << blue << "using transition: " << reset
                  << cyan << "(State(" << mStatesStack.back() << ')'
                  << ", " << symbol << ')' << reset
                  << std::endl;
    }
    return transition->execute(*this, symbol);
}

} // namespace YAP
