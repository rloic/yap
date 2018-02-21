#pragma once

#include <YAP/Symbol.h>

#include <iostream>

namespace YAP {

template<typename Type, Symbol::Id ValueId, char DebugName = '\0'>
class ValuedSymbol : public Symbol {
public:
    static Ptr Create(Type value) {
        return Ptr(new ValuedSymbol(value));
    }

    Type GetValue() const { return mValue; }

protected:
    explicit ValuedSymbol(Type value) : Symbol(ValueId), mValue{value} {}

    void print(std::ostream &os) const override {
        os << DebugName << "(" << mValue << ")";
    }

private:
    Type mValue;
};

} // namespace YAP
