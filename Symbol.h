#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

#include "Console.h"
#include "HasPtr.h"

class Symbol : public HasPtr<Symbol> {
public:
    enum class Id {
        Ep,
        E,
        L_PAR,
        R_PAR,
        PLUS,
        MULT,
        VAL,
        Eof
    };

public:
    static Ptr Clone(const Symbol::Ptr &symbol);

    virtual ~Symbol() = default;

    Id id() const;

    friend std::ostream &operator<<(std::ostream &os, const Symbol &symbol);

protected:
    explicit Symbol(Id mID);

    virtual void print(std::ostream &os) const;

private:
    Id mID;
};

std::ostream &operator<<(std::ostream &os, const Symbol::Id &id);
