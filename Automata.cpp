#include "Automata.h"
#include "Symbols/Expr.h"
#include "Transitions/Shifts.h"
#include "Transitions/Reductions.h"

Automata::Automata(Lexer lexer, bool debug)
        : mLexer{lexer},
          mDebug{debug},
          transitions{},
          gotoTransitions{}
{
    transitions[State::State0][Symbol::Id::VAL] = &d3;
    transitions[State::State0][Symbol::Id::L_PAR] = &d2;

    transitions[State::State1][Symbol::Id::PLUS] = &d4;
    transitions[State::State1][Symbol::Id::MULT] = &d5;
    transitions[State::State1][Symbol::Id::Eof] = &accept;

    transitions[State::State2][Symbol::Id::VAL] = &d3;
    transitions[State::State2][Symbol::Id::L_PAR] = &d2;

    transitions[State::State3][Symbol::Id::PLUS] = &r5;
    transitions[State::State3][Symbol::Id::MULT] = &r5;
    transitions[State::State3][Symbol::Id::R_PAR] = &r5;
    transitions[State::State3][Symbol::Id::Eof] = &r5;

    transitions[State::State4][Symbol::Id::VAL] = &d3;
    transitions[State::State4][Symbol::Id::L_PAR] = &d2;

    transitions[State::State5][Symbol::Id::VAL] = &d3;
    transitions[State::State5][Symbol::Id::L_PAR] = &d2;

    transitions[State::State6][Symbol::Id::PLUS] = &d4;
    transitions[State::State6][Symbol::Id::MULT] = &d5;
    transitions[State::State6][Symbol::Id::R_PAR] = &d9;

    transitions[State::State7][Symbol::Id::PLUS] = &r2;
    transitions[State::State7][Symbol::Id::MULT] = &d5;
    transitions[State::State7][Symbol::Id::R_PAR] = &r2;
    transitions[State::State7][Symbol::Id::Eof] = &r2;

    transitions[State::State8][Symbol::Id::PLUS] = &r3;
    transitions[State::State8][Symbol::Id::MULT] = &r3;
    transitions[State::State8][Symbol::Id::R_PAR] = &r3;
    transitions[State::State8][Symbol::Id::Eof] = &r3;

    transitions[State::State9][Symbol::Id::PLUS] = &r4;
    transitions[State::State9][Symbol::Id::MULT] = &r4;
    transitions[State::State9][Symbol::Id::R_PAR] = &r4;
    transitions[State::State9][Symbol::Id::Eof] = &r4;

    gotoTransitions[State::State0] = State::State1;
    gotoTransitions[State::State2] = State::State6;
    gotoTransitions[State::State4] = State::State7;
    gotoTransitions[State::State5] = State::State8;

}

void Automata::Read() {
    mStatesStack.emplace_back(State::State0);
    Symbol::Ptr current;
    do {
        current = mLexer.GetNext();
        if (mDebug) {
            DebugStacks();
            std::cout << "Symbol: " << *current << std::endl;
        }
    } while (executeTransition(current));
    if (mDebug) DebugStacks();

    if (mSymbolsStack.empty() || !dynamic_cast<Expr *>(mSymbolsStack.back().get())) {
        std::cout << GRAS RGE << "No result due to Error." << RESET << std::endl;
    } else {
        std::cout << GRAS VRT << "Result: " << RESET
                  << VRT << dynamic_cast<Expr *>(mSymbolsStack.back().get())->value() << RESET
                  << std::endl;
    }
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
    mStatesStack.push_back(gotoTransitions[mStatesStack.back()]);
}

Symbol::Ptr Automata::PopSymbol() {
    Symbol::Ptr popped{mSymbolsStack.back()};
    mSymbolsStack.pop_back();
    return popped;
}

void Automata::DebugStacks() const {
    std::cout << mStatesStack.size() << " states:";
//    for (auto &state : mStatesStack) {
//        //std::cout << " " << state; TODO("Implement << for State")
//    }
    std::cout << std::endl;
    std::cout << mSymbolsStack.size() << " symbols:";
    for (auto &symbol : mSymbolsStack) {
        std::cout << " " << *symbol;
    }
    std::cout << std::endl;

    std::cout << "------------------------------------------" << std::endl;
}

bool Automata::executeTransition(Symbol::Ptr symbol) {
    StateTransitions availableTransitions = transitions[mStatesStack.back()];
    Transition const *transition;
    if (availableTransitions.find(symbol->id()) == availableTransitions.end()) {
        transition = &skip;
        mLexer.MoveNext();
    } else {
        transition = availableTransitions[symbol->id()];
    }
    return transition->execute(*this, symbol);
}
