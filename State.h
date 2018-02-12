#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <iomanip>
#include <utility>

#include "Symbol.h"
#include "Console.h"

class Automata;

class State : public HasPtr<State> {
public:
    virtual ~State() = default;

    virtual bool Transition(Automata &automata, Symbol::Ptr symbol, bool debug) = 0;

    virtual State::Ptr GoTo();

    friend std::ostream &operator<<(std::ostream &os, const State &state);

protected:
    explicit State(std::string &&name);

private:
    std::string mName;
};
