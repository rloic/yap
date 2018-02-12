#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

#include "Console.h"
#include "HasPtrs.h"

enum class IDs {
    Ep,
    E,
    L_PAR,
    R_PAR,
    PLUS,
    MULT,
    VAL,
    Eof
};

inline std::ostream &operator<<(std::ostream &os, const IDs &id) {
    switch (id) {
        case IDs::Ep:
            return os << "E'";
        case IDs::E:
            return os << "E";
        case IDs::L_PAR:
            return os << "(";
        case IDs::R_PAR:
            return os << ")";
        case IDs::PLUS:
            return os << "+";
        case IDs::MULT:
            return os << "*";
        case IDs::VAL:
            return os << "VAL";
        case IDs::Eof:
            return os << "$";
    }
}

class Symbol {
public:
    explicit Symbol(IDs mID) : mID{mID} {}

    virtual ~Symbol() = default;

    virtual void print() const {
        std::cout << "Symbol: " << std::setw(8) << CYN << mID << RESET << std::endl;
    }

    virtual void tiny_print(std::ostream &os) const {
        os << mID;
    }

    friend std::ostream &operator<<(std::ostream &os, const Symbol &symbol) {
        symbol.tiny_print(os);
        return os;
    }

    IDs id() const { return mID; }

private:
    IDs mID;
};
