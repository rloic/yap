#pragma once

#include "../Symbol.h"

class Eof: public Symbol {
public:
    Eof() : Symbol(IDs::Eof) {}
};
