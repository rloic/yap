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

#include <YAP/YAP.h>

using IntegerType = long long;

enum Symbols : size_t {
    EXPR,
    VAL,
    L_PAR,
    R_PAR,
    TIMES,
    PLUS
};

// Non terminal symbols

using Expr = YAP::ValuedSymbol<IntegerType, EXPR, 'E'>;
using Val = YAP::ValuedSymbol<IntegerType, VAL, 'V'>;

// Terminal symbols

using LPar = YAP::TerminalSymbol<L_PAR, '('>;
using RPar = YAP::TerminalSymbol<R_PAR, ')'>;
using Mult = YAP::TerminalSymbol<TIMES, '*'>;
using Plus = YAP::TerminalSymbol<PLUS, '+'>;
