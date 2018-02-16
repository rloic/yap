#pragma once

#include "../Symbol.h"

template<Symbol::Id SymbolId>
class TerminalSymbol : public Symbol {
public:
    static Ptr Create() {
        return Ptr(new TerminalSymbol);
    }

protected:
    TerminalSymbol() : Symbol{SymbolId} {}
};
