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
