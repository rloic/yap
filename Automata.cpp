#include "Automata.h"
#include "States.h"
#include "Symbols/Expr.h"

void Automata::read() {
    mStates.emplace_back(new State0{});
    Symbol *current;
    do {
        current = mLexer.getnext();
        if (mDebug) {
            debug();
            std::cout << "Symbol: " << *current << std::endl;
        }
    } while (mStates.back()->transition(*this, current, mDebug));
    if (mDebug) debug();

    if (mSymbols.empty() || !dynamic_cast<Expr *>(mSymbols.back())) {
        std::cout << GRAS RGE << "No result due to error." << RESET<< std::endl;
    } else {
        std::cout << GRAS VRT << "Result: " << RESET
                  << VRT << dynamic_cast<Expr *>(mSymbols.back())->value() << RESET
                  << std::endl;
    }
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
