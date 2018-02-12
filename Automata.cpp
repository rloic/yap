#include "Automata.h"
#include "States.h"
#include "Symbols/Expr.h"

Automata::Automata(Lexer lexer, bool debug)
        : mLexer{lexer},
          mDebug{debug} {}

void Automata::Read() {
    mStates.emplace_back(State0::Create());
    Symbol::Ptr current;
    do {
        current = mLexer.GetNext();
        if (mDebug) {
            DebugStacks();
            std::cout << "Symbol: " << *current << std::endl;
        }
    } while (mStates.back()->Transition(*this, current, mDebug));
    if (mDebug) DebugStacks();

    if (mSymbols.empty() || !dynamic_cast<Expr *>(mSymbols.back().get())) {
        std::cout << GRAS RGE << "No result due to Error." << RESET << std::endl;
    } else {
        std::cout << GRAS VRT << "Result: " << RESET
                  << VRT << dynamic_cast<Expr *>(mSymbols.back().get())->value() << RESET
                  << std::endl;
    }
}

void Automata::Shift(Symbol::Ptr symbol, State::Ptr state) {
    mSymbols.push_back(symbol);
    mStates.push_back(state);

    mLexer.MoveNext();
}

void Automata::Reduce(int n, Symbol::Ptr symbol) {
    for (int i = 0; i < n; ++i) {
        mStates.pop_back();

        // Symbols are popped in the states' transitions
    }
    mSymbols.push_back(symbol);
    mStates.push_back(mStates.back()->GoTo());
}

Symbol::Ptr Automata::PopSymbol() {
    Symbol::Ptr popped{mSymbols.back()};
    mSymbols.pop_back();
    return popped;
}

void Automata::DebugStacks() const {
    std::cout << mStates.size() << " states:";
    for (auto &state : mStates) {
        std::cout << " " << *state;
    }
    std::cout << std::endl;
    std::cout << mSymbols.size() << " symbols:";
    for (auto &symbol : mSymbols) {
        std::cout << " " << *symbol;
    }
    std::cout << std::endl;

    std::cout << "------------------------------------------" << std::endl;
}
