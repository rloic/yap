#include "Symbol.h"

Symbol::Symbol(IDs mID) : mID{mID} {}

Symbol::Ptr Symbol::Clone(const Symbol::Ptr &symbol) {
    return std::make_shared<Symbol>(Symbol(*symbol));
}

IDs Symbol::id() const { return mID; }

void Symbol::print(std::ostream &os) const {
    os << mID;
}

std::ostream &operator<<(std::ostream &os, const Symbol &symbol) {
    symbol.print(os);
    return os;
}

std::ostream &operator<<(std::ostream &os, const IDs &id) {
    switch (id) {
        case IDs::Ep:
            os << "E'";
            break;
        case IDs::E:
            os << "E";
            break;
        case IDs::L_PAR:
            os << "(";
            break;
        case IDs::R_PAR:
            os << ")";
            break;
        case IDs::PLUS:
            os << "+";
            break;
        case IDs::MULT:
            os << "*";
            break;
        case IDs::VAL:
            os << "VAL";
            break;
        case IDs::Eof:
            os << "$";
            break;
    }
    return os;
}
