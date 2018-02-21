#pragma once

#include <YAP/Symbol.h>

namespace YAP {

template<Symbol::Id SymbolId, char DebugName = '\0'>
class TerminalSymbol : public Symbol {
public:
    static Ptr Create() {
        return Ptr(new TerminalSymbol);
    }

protected:
    void print(std::ostream &os) const override {
        os << DebugName;
    }

protected:
    TerminalSymbol() : Symbol{SymbolId} {}
};

using Eof = TerminalSymbol<Symbol::Eof, '$'>;

} // namespace YAP
