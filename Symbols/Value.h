#pragma once

#include <ostream>

#include "../Symbol.h"

template<typename Type, char Name, Symbol::Id const ValueId>
class Value : public Symbol {
public:
    static Ptr Create(Type value) {
        return Ptr(new Value(value));
    }

    Type GetValue() const { return mValue; }

protected:
    explicit Value(Type value) : Symbol(ValueId), mValue{value} {}

    void print(std::ostream &os) const override {
        os << Name << "(" << mValue << ")";
    }

private:
    Type mValue;
};
