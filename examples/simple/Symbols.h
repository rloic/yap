#pragma once

#include <YAP/ValuedSymbol.h>
#include <YAP/TerminalSymbol.h>

using IntegerType = long long;

// Non terminal symbols

using Expr = ValuedSymbol<IntegerType, 'E', Symbol::Id::E>;
using Val = ValuedSymbol<IntegerType, 'V', Symbol::Id::VAL>;

// Terminal symbols

using LPar = TerminalSymbol<Symbol::L_PAR>;
using RPar = TerminalSymbol<Symbol::R_PAR>;
using Mult = TerminalSymbol<Symbol::MULT>;
using Plus = TerminalSymbol<Symbol::PLUS>;
