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

CREATE_TERMINAL_SYMBOL(Eof, IDs::Eof)
CREATE_TERMINAL_SYMBOL(LPar, IDs::L_PAR)
CREATE_TERMINAL_SYMBOL(RPar, IDs::R_PAR)
CREATE_TERMINAL_SYMBOL(Mult, IDs::MULT)
CREATE_TERMINAL_SYMBOL(Plus, IDs::PLUS)
