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

#include <YAP/Automata.h>

#include <YAP/Common.h>
#include <YAP/Transition.h>

namespace YAP {

Automata::Automata(Lexer lexer, bool debug)
        : mLexer{lexer},
          mDebug{debug},
          transitions{},
          goToTransitions{}
{}

Symbol::Ptr Automata::Read() {
    mStatesStack.emplace_back(State(0));
    if (mDebug) DebugStacks();
    Symbol::Ptr current;
    do {
        current = mLexer.GetNext();
        if (mDebug) {
            std::cout << "Symbol: " << current << std::endl;
            DebugStacks();
        }
    } while (executeTransition(current));

    return mSymbolsStack.empty() ? Symbol::Ptr() : mSymbolsStack.back();
}

TransitionAdder Automata::AddTransitions() {
    return TransitionAdder(*this);
}

void Automata::AddGoToTransition(State from, State to) {
    goToTransitions[from] = to;
}

void Automata::Shift(Symbol::Ptr symbol, State state) {
    mSymbolsStack.push_back(symbol);
    mStatesStack.push_back(state);

    mLexer.MoveNext();
}

void Automata::Reduce(int n, Symbol::Ptr symbol) {
    for (int i = 0; i < n; ++i) {
        mStatesStack.pop_back();

        // Symbols are popped in the states' transitions
    }
    mSymbolsStack.push_back(symbol);
    mStatesStack.push_back(goToTransitions[mStatesStack.back()]);

    // => goto(état, non_terminal)
}

void Automata::PopSymbol() {
    mSymbolsStack.pop_back();
}

void Automata::DebugStacks() const {
    std::cout << mStatesStack.size() << " states:";
    for (auto &state : mStatesStack) {
        std::cout << " " << state;
    }
    std::cout << std::endl;
    std::cout << mSymbolsStack.size() << " symbols:";
    for (auto &symbol : mSymbolsStack) {
        std::cout << " " << symbol;
    }
    std::cout << std::endl;

    std::cout << "------------------------------------------" << std::endl;
}

bool Automata::executeTransition(Symbol::Ptr symbol) {
    StateTransitions const& availableTransitions = transitions.at(mStatesStack.back());
    Transition const * transition{nullptr};
    auto it = availableTransitions.find(symbol->GetId());
    if (it == availableTransitions.end()) {
        transition = SkipUnexpectedTransition::InstancePtr();
        mLexer.MoveNext();
    } else {
        transition = it->second;
    }
    return transition->execute(*this, symbol);
}

} // namespace YAP
