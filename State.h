#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <iomanip>
#include <utility>

#include "Symbol.h"
#include "Console.h"

class Automata;

class State {
public:
    explicit State(std::string name)
            : mName{std::move(name)} {
    }

    virtual ~State() = default;

    friend std::ostream &operator<<(std::ostream &os, const State &state) {
        os << MAG << state.mName << RESET;
        return os;
    }

    void error(Symbol *s) {
        std::cout << GRAS RGE << "Unexpected symbol: " << RESET;
        if (s) std::cout << JAU << *s << RESET;
        std::cout << std::endl;
    }

    virtual bool transition(Automata &automata, Symbol *symbol, bool debug = false) = 0;

    virtual State* GoTo() {
        assert(false && "Can't be here.");
    };

protected:
    std::string mName;
};
