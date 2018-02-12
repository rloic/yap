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
            os << "E'";
            break;
        case IDs::E:
            os << "E";
            break;
        case IDs::L_PAR:
            os << "(";
            break;
        case IDs::R_PAR:
            os << ")";
            break;
        case IDs::PLUS:
            os << "+";
            break;
        case IDs::MULT:
            os << "*";
            break;
        case IDs::VAL:
            os << "VAL";
            break;
        case IDs::Eof:
            os << "$";
            break;
    }
    return os;
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
