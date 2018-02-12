#pragma once

#include "../Symbol.h"

class Val : public Symbol {
public:
    Val(int value) : Symbol(IDs::VAL), mValue{value} {}

    int value() const { return mValue; }

    virtual void print() const {
        std::cout << "Symbol: " << std::setw(8) << CYN << "VAL(" << mValue << ")" << RESET << std::endl;
    }

    virtual void tiny_print(std::ostream &os) const {
        os << "VAL(" << mValue << ")";
    }

private:
    int mValue;
};
