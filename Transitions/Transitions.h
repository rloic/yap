#pragma once

#include "../Transition.h"
#include "../Automata.h"
#include "../Symbols/NonTerminalSymbols.h"

namespace Shifts {
    using d2 = Shift<State::S2>;
    using d3 = Shift<State::S3>;
    using d4 = Shift<State::S4>;
    using d5 = Shift<State::S5>;
    using d9 = Shift<State::S9>;
}

namespace Reductions {
    // E -> E + E
    NEW_REDUCTION(r2, {
        (void)(symbol);

        auto const e1 = automata.PopSymbolAs<Expr>();
        automata.PopSymbol();
        auto const e3 = automata.PopSymbolAs<Expr>();

        auto result = Expr::Create(e1->GetValue() + e3->GetValue());
        automata.Reduce(3, result);

        return true;
    })

    // E -> E * E
    NEW_REDUCTION(r3, {
        (void)(symbol);

        auto const e1 = automata.PopSymbolAs<Expr>();
        automata.PopSymbol();
        auto const e3 = automata.PopSymbolAs<Expr>();

        auto result = Expr::Create(e1->GetValue() * e3->GetValue());
        automata.Reduce(3, result);

        return true;
    })

    // E -> ( E )
    NEW_REDUCTION(r4, {
        (void)(symbol);

        automata.PopSymbol();
        auto const e2 = automata.PopSymbolAs<Expr>();
        automata.PopSymbol();

        automata.Reduce(3, Expr::Create(e2->GetValue()));

        return true;
    })

    // E -> val
    NEW_REDUCTION(r5, {
        (void)(symbol);

        auto const v = automata.PopSymbolAs<Val>();
        automata.Reduce(1, Expr::Create(v->GetValue()));
        return true;
    })
}
