#pragma once

#include "../Symbol.h"

class Expr : public Symbol {
public:
    Expr(int value) : Symbol(IDs::E), mValue{value} {}

    int value() const { return mValue; }

    virtual void print() const {
        std::cout << "Symbol: " << std::setw(8) << CYN << "EXPR(" << mValue << ")" << RESET << std::endl;
    }

    virtual void tiny_print(std::ostream &os) const {
        os << "EXPR(" << mValue << ")";
    }

private:
    int mValue;
};
