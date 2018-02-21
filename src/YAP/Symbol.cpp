#include <YAP/Symbol.h>

#include <YAP/Common.h>

#include <map>

namespace YAP {

Symbol::Symbol(size_t id) : mID{id} {}

size_t Symbol::GetId() const { return mID; }

void Symbol::print(std::ostream &os) const {
    os << mID;
}

std::ostream &operator<<(std::ostream &os, const Symbol &symbol) {
    symbol.print(os);
    return os;
}

std::ostream &operator<<(std::ostream &os, const Symbol::Ptr &symbolPtr) {
    symbolPtr->print(os);
    return os;
}

} // namespace YAP
