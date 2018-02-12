#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <memory>

#include "Console.h"
#include "HasPtrs.h"

using id_t = uint64_t;

class Symbol : HasPtrs<Symbol> {
public:
    explicit Symbol(id_t mID) : mID{mID} {}

    virtual ~Symbol() = default;

    void print() const {
        std::cout << "Symbol: " << std::setw(8) << CYN << mID << RESET << std::endl;
    }

    explicit operator int() const { return mID; }

private:
    id_t mID;
};
