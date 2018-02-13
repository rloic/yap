#pragma once

#include "../Symbol.h"

#define CREATE_TERMINAL_SYMBOL(name, id)    \
class name : public Symbol {                \
public:                                     \
    static Ptr Create() {                   \
        return Ptr(new name);               \
    }                                       \
protected:                                  \
    name() : Symbol(id) {}                  \
};

CREATE_TERMINAL_SYMBOL(Eof, Symbol::Id::Eof)
CREATE_TERMINAL_SYMBOL(LPar, Symbol::Id::L_PAR)
CREATE_TERMINAL_SYMBOL(RPar, Symbol::Id::R_PAR)
CREATE_TERMINAL_SYMBOL(Mult, Symbol::Id::MULT)
CREATE_TERMINAL_SYMBOL(Plus, Symbol::Id::PLUS)
