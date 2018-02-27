/*
 * MIT License
 *
 * Copyright (c) 2018 insa.4if.hexanome_kalate
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#pragma once

#include "Symbols.h"

#include <YAP/YAP.h>

#include <iostream>

namespace Shifts {
    using YAP::Shift;
    using YAP::State;

    using d2 = Shift<State(2)>;
    using d3 = Shift<State(3)>;
    using d4 = Shift<State(4)>;
    using d5 = Shift<State(5)>;
    using d9 = Shift<State(9)>;
}

namespace Reductions {
    // E -> E + E
    NEW_REDUCTION(r2, {
        YAP_UNUSED(symbol);

        auto const e1 = automata.PopSymbolAs<Expr>();
        automata.PopSymbol();
        auto const e3 = automata.PopSymbolAs<Expr>();

        auto result = Expr::Create(e1->GetValue() + e3->GetValue());
        automata.Reduce(3, result);

        return true;
    })

    // E -> E * E
    NEW_REDUCTION(r3, {
        YAP_UNUSED(symbol);

        auto const e1 = automata.PopSymbolAs<Expr>();
        automata.PopSymbol();
        auto const e3 = automata.PopSymbolAs<Expr>();

        auto result = Expr::Create(e1->GetValue() * e3->GetValue());
        automata.Reduce(3, result);

        return true;
    })

    // E -> ( E )
    NEW_REDUCTION(r4, {
        YAP_UNUSED(symbol);

        automata.PopSymbol();
        auto const e2 = automata.PopSymbolAs<Expr>();
        automata.PopSymbol();

        automata.Reduce(3, Expr::Create(e2->GetValue()));

        return true;
    })

    // E -> val
    NEW_REDUCTION(r5, {
        YAP_UNUSED(symbol);

        auto const v = automata.PopSymbolAs<Val>();
        automata.Reduce(1, Expr::Create(v->GetValue()));
        return true;
    })
}
