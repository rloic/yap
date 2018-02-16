#pragma once

#include "TerminalSymbol.h"

using Eof = TerminalSymbol<Symbol::Eof>;
using LPar = TerminalSymbol<Symbol::L_PAR>;
using RPar = TerminalSymbol<Symbol::R_PAR>;
using Mult = TerminalSymbol<Symbol::MULT>;
using Plus = TerminalSymbol<Symbol::PLUS>;
