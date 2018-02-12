#pragma once

#include "../Symbol.h"

class Val : public Symbol {
public:
    Val(long long value) : Symbol(IDs::VAL), mValue{value} {}

    long long value() const { return mValue; }

protected:
    virtual void print(std::ostream &os) const {
        os << "VAL(" << mValue << ")";
    }

private:
    long long mValue;
};
