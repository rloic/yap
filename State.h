#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <utility>

#include "Automata.h"
#include "Symbol.h"
#include "Console.h"

class State : HasPtrs<State> {
public:
    explicit State(std::string name)
            : mName{std::move(name)} {
    }

    virtual ~State() = default;

    void print() const {
        std::cout << "State: " << std::setw(20) << BLE << mName << RESET << std::endl;
    }

    virtual bool transition(Automata &automata, Symbol *state) = 0;

protected:
    std::string mName;
};
