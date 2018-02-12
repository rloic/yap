#pragma once

#include "../Symbol.h"

class Expr : public Symbol {
public:
    static Ptr Create(long long value) {
        return Ptr(new Expr(value));
    }

    long long value() const { return mValue; }

protected:
    explicit Expr(long long value) : Symbol(IDs::E), mValue{value} {}

    virtual void print(std::ostream &os) const {
        os << "EXPR(" << mValue << ")";
    }

private:
    long long mValue;
};
