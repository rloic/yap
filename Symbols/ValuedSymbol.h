#pragma once

#include "../Symbol.h"

template<typename Type, char Name, Symbol::Id const ValueId>
class ValuedSymbol : public Symbol {
public:
    static Ptr Create(Type value) {
        return Ptr(new ValuedSymbol(value));
    }

    Type GetValue() const { return mValue; }

protected:
    explicit ValuedSymbol(Type value) : Symbol(ValueId), mValue{value} {}

    void print(std::ostream &os) const override {
        os << Name << "(" << mValue << ")";
    }

private:
    Type mValue;
};
