#include "Automata.h"
#include "Symbols/NonTerminalSymbols.h"
#include "Transitions/Shifts.h"
#include "Transitions/Reductions.h"

Automata::Automata(Lexer lexer, bool debug)
        : mLexer{lexer},
          mDebug{debug},
          transitions{},
          gotoTransitions{}
{
    transitions[State::S0][Symbol::Id::VAL] = &d3;
    transitions[State::S0][Symbol::Id::L_PAR] = &d2;

    transitions[State::S1][Symbol::Id::PLUS] = &d4;
    transitions[State::S1][Symbol::Id::MULT] = &d5;
    transitions[State::S1][Symbol::Id::Eof] = &accept;

    transitions[State::S2][Symbol::Id::VAL] = &d3;
    transitions[State::S2][Symbol::Id::L_PAR] = &d2;

    transitions[State::S3][Symbol::Id::PLUS] = &r5;
    transitions[State::S3][Symbol::Id::MULT] = &r5;
    transitions[State::S3][Symbol::Id::R_PAR] = &r5;
    transitions[State::S3][Symbol::Id::Eof] = &r5;

    transitions[State::S4][Symbol::Id::VAL] = &d3;
    transitions[State::S4][Symbol::Id::L_PAR] = &d2;

    transitions[State::S5][Symbol::Id::VAL] = &d3;
    transitions[State::S5][Symbol::Id::L_PAR] = &d2;

    transitions[State::S6][Symbol::Id::PLUS] = &d4;
    transitions[State::S6][Symbol::Id::MULT] = &d5;
    transitions[State::S6][Symbol::Id::R_PAR] = &d9;

    transitions[State::S7][Symbol::Id::PLUS] = &r2;
    transitions[State::S7][Symbol::Id::MULT] = &d5;
    transitions[State::S7][Symbol::Id::R_PAR] = &r2;
    transitions[State::S7][Symbol::Id::Eof] = &r2;

    transitions[State::S8][Symbol::Id::PLUS] = &r3;
    transitions[State::S8][Symbol::Id::MULT] = &r3;
    transitions[State::S8][Symbol::Id::R_PAR] = &r3;
    transitions[State::S8][Symbol::Id::Eof] = &r3;

    transitions[State::S9][Symbol::Id::PLUS] = &r4;
    transitions[State::S9][Symbol::Id::MULT] = &r4;
    transitions[State::S9][Symbol::Id::R_PAR] = &r4;
    transitions[State::S9][Symbol::Id::Eof] = &r4;

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
            std::
            cout << "Symbol: " << *current << std::endl;
        }
    } while (executeTransition(current));
    if (mDebug) DebugStacks();

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
        std::cout << " " << State::Names[state];
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
        transition = &skip;
        mLexer.MoveNext();
    }
    return transition->execute(*this, symbol);
}
