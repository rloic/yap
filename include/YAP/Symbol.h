#pragma once

#include <YAP/HasPtr.h>

namespace YAP {

class Symbol : public HasPtr<Symbol> {
public:
    using Id = size_t;

    /// Symbol ids over 2^16 are reserved
    static const Id Eof = 1U + (1U << 15U);

public:
    virtual ~Symbol() = default;

    Id GetId() const;

    friend std::ostream &operator<<(std::ostream &os, const Symbol &symbol);
    friend std::ostream &operator<<(std::ostream &os, const Symbol::Ptr &symbolPtr);

protected:
    explicit Symbol(Id id);

    virtual void print(std::ostream &os) const;

private:
    Id mID;
};

} // namespace YAP
