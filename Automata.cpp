#include "Automata.h"
//#include "States/State0.h"
#include "States.h"
#include "Symbols/Expr.h"

void Automata::read() {
    mStates.emplace_back(new State0{});
    Symbol *current = nullptr;
    while ((current = mLexer.getnext())) {
        if(mDebug) {
            debug();
            current->print();
        }
        if (!mStates.back()->transition(*this, current, false)) break;
    }
    std::cout << "Result: " << dynamic_cast<Expr*>(mSymbols.back())->value() << std::endl;
    if(mDebug) debug();
}

void Automata::shift(Symbol *symbol, State *state) {
    mSymbols.push_back(symbol);
    mStates.push_back(state);

    mLexer.movenext();
}

void Automata::reduce(int n, Symbol *symbol) {
    for (int i = 0; i < n; ++i) {
        delete mStates.back();
        mStates.pop_back();

        // Symbols are popped in the states' transitions
    }
    mSymbols.push_back(symbol);
    mStates.push_back(mStates.back()->GoTo());
}

void Automata::debug() const {
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
