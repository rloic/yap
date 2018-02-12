#pragma once

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

#include "Console.h"
#include "HasPtr.h"

enum class IDs {
    Ep,
    E,
    L_PAR,
    R_PAR,
    PLUS,
    MULT,
    VAL,
    Eof
};

class Symbol : public HasPtr<Symbol> {
public:
    static Ptr Clone(const Symbol::Ptr &symbol);

    virtual ~Symbol() = default;

    IDs id() const;

    friend std::ostream &operator<<(std::ostream &os, const Symbol &symbol);

protected:
    explicit Symbol(IDs mID);

    virtual void print(std::ostream &os) const;

private:
    IDs mID;
};

std::ostream &operator<<(std::ostream &os, const IDs &id);
