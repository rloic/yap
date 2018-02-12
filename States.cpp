#include "States.h"

#include <cassert>

#include "Symbols/Expr.h"
#include "Symbols/Val.h"

#define WHEREAMI(NAME) if(debug) { std::cout << JAU << "Transition@" << (NAME) << RESET << std::endl; }

static void unexpectedSymbol(const Symbol::Ptr &s) {
    std::cout << GRAS RGE << "Unexpected symbol: " << RESET;
    if (s) std::cout << JAU << *s << RESET;
    std::cout << std::endl;
}

bool State0::Transition(Automata &automata, Symbol::Ptr symbol, bool debug) {
    WHEREAMI("State0");

    switch (symbol->id()) {
        case IDs::VAL:
            automata.Shift(symbol, State3::Create());
            break;
        case IDs::L_PAR:
            automata.Shift(symbol, State2::Create());
            break;
        case IDs::E:
            automata.Shift(symbol, State1::Create());
            break;
        default:
            unexpectedSymbol(symbol);
            return false;
    }
    return true;
}

State::Ptr State0::GoTo() {
    return State1::Create();
}

bool State1::Transition(Automata &automata, Symbol::Ptr symbol, bool debug) {
    WHEREAMI("State1");

    switch (symbol->id()) {
        case IDs::MULT:
            automata.Shift(symbol, State5::Create());
            break;
        case IDs::PLUS:
            automata.Shift(symbol, State4::Create());
            break;
        case IDs::Eof:
            if (debug) std::cout << GRAS VRT << "ACCEPT" << RESET << std::endl;
            return false;
        default:
            unexpectedSymbol(symbol);
            return false;
    }
    return true;
}

bool State2::Transition(Automata &automata, Symbol::Ptr symbol, bool debug) {
    WHEREAMI("State2");

    switch (symbol->id()) {
        case IDs::VAL:
            automata.Shift(symbol, State3::Create());
            break;
        case IDs::L_PAR:
            automata.Shift(symbol, State2::Create());
            break;
        case IDs::E:
            automata.Shift(symbol, State6::Create());
            break;
        default:
            unexpectedSymbol(symbol);
            return false;
    }
    return true;
}

State::Ptr State2::GoTo() {
    return State6::Create();
}

bool State3::Transition(Automata &automata, Symbol::Ptr symbol, bool debug) {
    WHEREAMI("State3");

    switch (symbol->id()) {
        case IDs::PLUS:
        case IDs::MULT:
        case IDs::R_PAR:
        case IDs::Eof: {
            Symbol::Ptr s = automata.PopSymbol();
            auto *val = dynamic_cast<Val *>(s.get());
            assert(s->id() == IDs::VAL && val);

            automata.Reduce(1, Expr::Create(val->value()));
            break;
        }
        default:
            unexpectedSymbol(symbol);
            return false;
    }

    return true;
}

bool State4::Transition(Automata &automata, Symbol::Ptr symbol, bool debug) {
    WHEREAMI("State4");

    switch (symbol->id()) {
        case IDs::VAL:
            automata.Shift(symbol, State3::Create());
            break;
        case IDs::L_PAR:
            automata.Shift(symbol, State2::Create());
            break;
        case IDs::E:
            automata.Shift(symbol, State7::Create());
            break;
        default:
            unexpectedSymbol(symbol);
            return false;
    }
    return true;
}

State::Ptr State4::GoTo() {
    return State7::Create();
}

bool State5::Transition(Automata &automata, Symbol::Ptr symbol, bool debug) {
    WHEREAMI("State5");

    switch (symbol->id()) {
        case IDs::VAL:
            automata.Shift(symbol, State3::Create());
            break;
        case IDs::L_PAR:
            automata.Shift(symbol, State2::Create());
            break;
        case IDs::E:
            automata.Shift(symbol, State8::Create());
            break;
        default:
            unexpectedSymbol(symbol);
            return false;
    }
    return true;
}

State::Ptr State5::GoTo() {
    return State8::Create();
}

bool State6::Transition(Automata &automata, Symbol::Ptr symbol, bool debug) {
    WHEREAMI("State6");

    switch (symbol->id()) {
        case IDs::PLUS:
            automata.Shift(symbol, State4::Create());
            break;
        case IDs::MULT:
            automata.Shift(symbol, State5::Create());
            break;
        case IDs::R_PAR:
            automata.Shift(symbol, State9::Create());
            break;
        default:
            unexpectedSymbol(symbol);
            return false;
    }
    return true;
}

bool State7::Transition(Automata &automata, Symbol::Ptr symbol, bool debug) {
    WHEREAMI("State7");

    switch (symbol->id()) {
        case IDs::PLUS:
        case IDs::R_PAR:
        case IDs::Eof: {
            Symbol::Ptr s1 = automata.PopSymbol();
            automata.PopSymbol();
            Symbol::Ptr s3 = automata.PopSymbol();

            Expr const *e1 = dynamic_cast<Expr *>(s1.get());
            Expr const *e3 = dynamic_cast<Expr *>(s3.get());
            assert(s1->id() == IDs::E && e1);
            assert(s3->id() == IDs::E && e3);

            auto result = Expr::Create(e1->value() + e3->value());

            automata.Reduce(3, result);
            break;
        }
        case IDs::MULT:
            automata.Shift(symbol, State5::Create());
            break;
        default:
            unexpectedSymbol(symbol);
            return false;
    }
    return true;
}

bool State8::Transition(Automata &automata, Symbol::Ptr symbol, bool debug) {
    WHEREAMI("State8");

    switch (symbol->id()) {
        case IDs::PLUS:
        case IDs::MULT:
        case IDs::R_PAR:
        case IDs::Eof: {
            Symbol::Ptr s1 = automata.PopSymbol();
            automata.PopSymbol();
            Symbol::Ptr s3 = automata.PopSymbol();

            Expr const *e1 = dynamic_cast<Expr *>(s1.get());
            Expr const *e3 = dynamic_cast<Expr *>(s3.get());
            assert(s1->id() == IDs::E && e1);
            assert(s3->id() == IDs::E && e3);

            auto result = Expr::Create(e1->value() * e3->value());

            automata.Reduce(3, result);
            break;
        }
        default:
            unexpectedSymbol(symbol);
            return false;
    }
    return true;
}

bool State9::Transition(Automata &automata, Symbol::Ptr symbol, bool debug) {
    WHEREAMI("State9");

    switch (symbol->id()) {
        case IDs::PLUS:
        case IDs::MULT:
        case IDs::R_PAR:
        case IDs::Eof: {
            automata.PopSymbol();
            Symbol::Ptr s2 = automata.PopSymbol();
            automata.PopSymbol();

            Expr const *e2 = dynamic_cast<Expr *>(s2.get());
            assert(s2->id() == IDs::E && e2);

            automata.Reduce(3, Expr::Create(e2->value()));
            break;
        }
        default:
            unexpectedSymbol(symbol);
            return false;
    }
    return true;
}
