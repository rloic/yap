#pragma once

#include <YAP/HasPtr.h>

namespace YAP {

class Symbol : public HasPtr<Symbol> {
public:
    enum Id : std::size_t {
        Ep,
        E,
        L_PAR,
        R_PAR,
        PLUS,
        MULT,
        VAL,
        Eof,
        NB_SYMBOLS
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

} // namespace YAP
