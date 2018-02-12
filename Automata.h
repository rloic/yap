#pragma once

#include <string>
#include <iostream>
#include <stack>

#include "Symbol.h"


class Automata : HasPtrs<Automata> {
public:
    Automata() {}

    virtual ~Automata() = default;

private:
    std::stack<Symbol::Ptr> mSymbols;
};
