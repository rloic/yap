#include "Automata.h"

#include "Common.h"
#include "Symbols/NonTerminalSymbols.h"
#include "Transitions/Transitions.h"

Automata::Automata(Lexer lexer, bool debug)
        : mLexer{lexer},
          mDebug{debug},
          transitions{},
          gotoTransitions{}
{
    using namespace Shifts;
    using namespace Reductions;

    AddTransition<d3>(State::S0, Symbol::Id::VAL);
    AddTransition<d2>(State::S0, Symbol::Id::L_PAR);

    AddTransition<d4>(State::S1, Symbol::Id::PLUS);
    AddTransition<d5>(State::S1, Symbol::Id::MULT);
    AddTransition<AcceptTransition>(State::S1, Symbol::Id::Eof);

    AddTransition<d3>(State::S2, Symbol::Id::VAL);
    AddTransition<d2>(State::S2, Symbol::Id::L_PAR);

    AddTransition<r5>(State::S3, Symbol::Id::PLUS);
    AddTransition<r5>(State::S3, Symbol::Id::MULT);
    AddTransition<r5>(State::S3, Symbol::Id::R_PAR);
    AddTransition<r5>(State::S3, Symbol::Id::Eof);

    AddTransition<d3>(State::S4, Symbol::Id::VAL);
    AddTransition<d2>(State::S4, Symbol::Id::L_PAR);

    AddTransition<d3>(State::S5, Symbol::Id::VAL);
    AddTransition<d2>(State::S5, Symbol::Id::L_PAR);

    AddTransition<d4>(State::S6, Symbol::Id::PLUS);
    AddTransition<d5>(State::S6, Symbol::Id::MULT);
    AddTransition<d9>(State::S6, Symbol::Id::R_PAR);

    AddTransition<r2>(State::S7, Symbol::Id::PLUS);
    AddTransition<d5>(State::S7, Symbol::Id::MULT);
    AddTransition<r2>(State::S7, Symbol::Id::R_PAR);
    AddTransition<r2>(State::S7, Symbol::Id::Eof);

    AddTransition<r3>(State::S8, Symbol::Id::PLUS);
    AddTransition<r3>(State::S8, Symbol::Id::MULT);
    AddTransition<r3>(State::S8, Symbol::Id::R_PAR);
    AddTransition<r3>(State::S8, Symbol::Id::Eof);

    AddTransition<r4>(State::S9, Symbol::Id::PLUS);
    AddTransition<r4>(State::S9, Symbol::Id::MULT);
    AddTransition<r4>(State::S9, Symbol::Id::R_PAR);
    AddTransition<r4>(State::S9, Symbol::Id::Eof);

    gotoTransitions[State::S0] = State::S1;
    gotoTransitions[State::S4] = State::S7;
    gotoTransitions[State::S5] = State::S8;
    gotoTransitions[State::S2] = State::S6;

}

void Automata::Read() {
    mStatesStack.emplace_back(State::S0);
    Symbol::Ptr current;
    do {
        current = mLexer.GetNext();
        if (mDebug) {
            DebugStacks();
            std::cout << "Symbol: " << *current << std::endl;
        }
    } while (executeTransition(current));

    if (mSymbolsStack.empty() || !dynamic_cast<Expr *>(mSymbolsStack.back().get())) {
        std::cout << GRAS RGE << "No result due to Error." << RESET << std::endl;
    } else {
        std::cout << GRAS VRT << "Result: " << RESET
                  << VRT << dynamic_cast<Expr *>(mSymbolsStack.back().get())->GetValue() << RESET
                  << std::endl;
    }
}

void Automata::Shift(Symbol::Ptr symbol, State::Id state) {
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
    mStatesStack.push_back(gotoTransitions[mStatesStack.back()]);
}

Symbol::Ptr Automata::PopSymbol() {
    Symbol::Ptr popped{mSymbolsStack.back()};
    mSymbolsStack.pop_back();
    return popped;
}

void Automata::DebugStacks() const {
    std::cout << mStatesStack.size() << " states:";
    for (auto &state : mStatesStack) {
        std::cout << " " << state;
    }
    std::cout << std::endl;
    std::cout << mSymbolsStack.size() << " symbols:";
    for (auto &symbol : mSymbolsStack) {
        std::cout << " " << *symbol;
    }
    std::cout << std::endl;

    std::cout << "------------------------------------------" << std::endl;
}

bool Automata::executeTransition(Symbol::Ptr symbol) {
    StateTransitions const& availableTransitions = transitions.at(mStatesStack.back());
    Transition const * transition{availableTransitions.at(symbol->id())};
    if (!transition) {
        transition = SkipUnexpectedTransition::InstancePtr();
        mLexer.MoveNext();
    }
    return transition->execute(*this, symbol);
}
