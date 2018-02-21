#pragma once

#include <YAP/ValuedSymbol.h>
#include <YAP/TerminalSymbol.h>

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
