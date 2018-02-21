#pragma once

#include <YAP/Symbol.h>

template<Symbol::Id SymbolId>
class TerminalSymbol : public Symbol {
public:
    static Ptr Create() {
        return Ptr(new TerminalSymbol);
    }

protected:
    TerminalSymbol() : Symbol{SymbolId} {}
};

using Eof = TerminalSymbol<Symbol::Eof>;
