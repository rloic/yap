#include "States.h"

#include <iostream>
#include <cassert>

#include "Console.h"
#include "States.h"
#include "Symbols/Expr.h"
#include "Symbols/Val.h"

#if 1
#define WHEREAMI(NAME) if(debug) { std::cout << JAU << "transition@" << NAME << RESET << std::endl; }
#else
#define WHEREAMI(NAME) ;
#endif

bool State0::transition(Automata &automata, Symbol *symbol, bool debug) {
    WHEREAMI("State0");

    switch (symbol->id()) {
        case IDs::VAL:
            automata.shift(symbol, new State3{});
            break;
        case IDs::L_PAR:
            automata.shift(symbol, new State2{});
            break;
        case IDs::E:
            automata.shift(symbol, new State1{});
            break;
        default:
            error(symbol);
    }
    return true;
}

State *State0::GoTo() {
    return new State1;
}

bool State1::transition(Automata &automata, Symbol *symbol, bool debug) {
    WHEREAMI("State1");

    switch (symbol->id()) {
        case IDs::MULT:
            automata.shift(symbol, new State5{});
            break;
        case IDs::PLUS:
            automata.shift(symbol, new State4{});
            break;
        case IDs::Eof:
            std::cout << GRAS VRT << "ACCEPT" << RESET << std::endl;
            return false;
        default:
            error(symbol);
    }
    return true;
}

bool State2::transition(Automata &automata, Symbol *symbol, bool debug) {
    WHEREAMI("State2");

    switch (symbol->id()) {
        case IDs::VAL:
            automata.shift(symbol, new State3{});
            break;
        case IDs::L_PAR:
            automata.shift(symbol, new State2{});
            break;
        case IDs::E:
            automata.shift(symbol, new State6{});
            break;
        default:
            error(symbol);
    }
    return true;
}

State *State2::GoTo() {
    return new State6;
}

bool State3::transition(Automata &automata, Symbol *symbol, bool debug) {
    WHEREAMI("State3");

    switch (symbol->id()) {
        case IDs::PLUS:
        case IDs::MULT:
        case IDs::R_PAR:
        case IDs::Eof: {
            Symbol *s = automata.mSymbols.back();
            automata.mSymbols.pop_back();
            assert(s->id() == IDs::VAL);
            automata.reduce(1, new Expr{((Val *) s)->value()});
            break;
        }
        default:
            error(symbol);
    }

    return true;
}

bool State4::transition(Automata &automata, Symbol *symbol, bool debug) {
    WHEREAMI("State4");

    switch (symbol->id()) {
        case IDs::VAL:
            automata.shift(symbol, new State3{});
            break;
        case IDs::L_PAR:
            automata.shift(symbol, new State2{});
            break;
        case IDs::E:
            automata.shift(symbol, new State7{});
            break;
        default:
            error(symbol);
    }
    return true;
}

State *State4::GoTo() {
    return new State7;
}

bool State5::transition(Automata &automata, Symbol *symbol, bool debug) {
    WHEREAMI("State5");

    switch (symbol->id()) {
        case IDs::VAL:
            automata.shift(symbol, new State3{});
            break;
        case IDs::L_PAR:
            automata.shift(symbol, new State2{});
            break;
        case IDs::E:
            automata.shift(symbol, new State8{});
            break;
        default:
            error(symbol);
    }
    return true;
}

State *State5::GoTo() {
    return new State8;
}

bool State6::transition(Automata &automata, Symbol *symbol, bool debug) {
    WHEREAMI("State6");

    switch (symbol->id()) {
        case IDs::PLUS:
            automata.shift(symbol, new State4{});
            break;
        case IDs::MULT:
            automata.shift(symbol, new State5{});
            break;
        case IDs::R_PAR:
            automata.shift(symbol, new State9{});
            break;
        default:
            error(symbol);
    }
    return true;
}

bool State7::transition(Automata &automata, Symbol *symbol, bool debug) {
    WHEREAMI("State7");

    switch (symbol->id()) {
        case IDs::PLUS:
        case IDs::R_PAR:
        case IDs::Eof: {
            Symbol *s1 = automata.mSymbols.back();
            automata.mSymbols.pop_back();
            //Symbol *s2 = automata.mSymbols.back();
            automata.mSymbols.pop_back();
            Symbol *s3 = automata.mSymbols.back();
            automata.mSymbols.pop_back();

//            print();
//            s1->print();
//            s2->print();
//            s3->print();

            assert(s1->id() == IDs::E);
            assert(s3->id() == IDs::E);

            auto *e1 = dynamic_cast<Expr *>(s1);
            auto *e3 = dynamic_cast<Expr *>(s3);
            auto *result = new Expr(e1->value() + e3->value());

            automata.reduce(3, result);
            break;
        }
        case IDs::MULT:
            automata.shift(symbol, new State5{});
            break;
        default:
            error(symbol);
    }
    return true;
}

bool State8::transition(Automata &automata, Symbol *symbol, bool debug) {
    WHEREAMI("State8");

    switch (symbol->id()) {
        case IDs::PLUS:
        case IDs::MULT:
        case IDs::R_PAR:
        case IDs::Eof: {
            Symbol *s1 = automata.mSymbols.back();
            automata.mSymbols.pop_back();
            //Symbol *s2 = automata.mSymbols.back();
            automata.mSymbols.pop_back();
            Symbol *s3 = automata.mSymbols.back();
            automata.mSymbols.pop_back();

//            print();
//            s1->print();
//            s2->print();
//            s3->print();

            assert(s1->id() == IDs::E);
            assert(s3->id() == IDs::E);

            auto *e1 = dynamic_cast<Expr *>(s1);
            auto *e3 = dynamic_cast<Expr *>(s3);
            auto *result = new Expr(e1->value() * e3->value());

            automata.reduce(3, result);
            break;
        }
        default:
            error(symbol);
    }
    return true;
}

bool State9::transition(Automata &automata, Symbol *symbol, bool debug) {
    WHEREAMI("State9");

    switch (symbol->id()) {
        case IDs::PLUS:
        case IDs::MULT:
        case IDs::R_PAR:
        case IDs::Eof: {
            //Symbol *s1 = automata.mSymbols.back();
            automata.mSymbols.pop_back();
            Symbol *s2 = automata.mSymbols.back();
            automata.mSymbols.pop_back();
            //Symbol *s3 = automata.mSymbols.back();
            automata.mSymbols.pop_back();

//            print();
//            s1->print();
//            s2->print();
//            s3->print();

            assert(s2->id() == IDs::E);

            auto *result = dynamic_cast<Expr *>(s2);

            automata.reduce(3, result);
            break;
        }
        default:
            error(symbol);
    }
    return true;
}
