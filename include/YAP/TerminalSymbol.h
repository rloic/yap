#pragma once

#include <YAP/Symbol.h>

namespace YAP {

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

} // namespace YAP
