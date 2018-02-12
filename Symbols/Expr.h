#pragma once

#include "../Symbol.h"

class Expr : public Symbol {
public:
    Expr(long long value) : Symbol(IDs::E), mValue{value} {}

    long long value() const { return mValue; }

protected:
    virtual void print(std::ostream &os) const {
        os << "EXPR(" << mValue << ")";
    }

private:
    long long mValue;
};
