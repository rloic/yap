#pragma once

#include <YAP/ValuedSymbol.h>
#include <YAP/TerminalSymbol.h>

using IntegerType = long long;

// Non terminal symbols

using Expr = YAP::ValuedSymbol<IntegerType, 'E', YAP::Symbol::Id::E>;
using Val = YAP::ValuedSymbol<IntegerType, 'V', YAP::Symbol::Id::VAL>;

// Terminal symbols

using LPar = YAP::TerminalSymbol<YAP::Symbol::L_PAR>;
using RPar = YAP::TerminalSymbol<YAP::Symbol::R_PAR>;
using Mult = YAP::TerminalSymbol<YAP::Symbol::MULT>;
using Plus = YAP::TerminalSymbol<YAP::Symbol::PLUS>;
