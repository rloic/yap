#pragma once

#include "../Symbol.h"

class Val : public Symbol {
public:
    static Ptr Create(long long value) {
        return Ptr(new Val(value));
    }

    long long value() const { return mValue; }

protected:
    explicit Val(long long value) : Symbol(Id::VAL), mValue{value} {}

    virtual void print(std::ostream &os) const {
        os << "VAL(" << mValue << ")";
    }

private:
    long long mValue;
};
