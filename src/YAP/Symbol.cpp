#include <YAP/Symbol.h>

#include <YAP/Common.h>

Symbol::Symbol(Id mID) : mID{mID} {}

Symbol::Ptr Symbol::Clone(const Symbol::Ptr &symbol) {
    return std::make_shared<Symbol>(Symbol(*symbol));
}

Symbol::Id Symbol::id() const { return mID; }

void Symbol::print(std::ostream &os) const {
    os << mID;
}

std::ostream &operator<<(std::ostream &os, const Symbol &symbol) {
    symbol.print(os);
    return os;
}

std::ostream &operator<<(std::ostream &os, const Symbol::Id &id) {
    switch (id) {
        case Symbol::Id::Ep:
            os << "E'";
            break;
        case Symbol::Id::E:
            os << "E";
            break;
        case Symbol::Id::L_PAR:
            os << "(";
            break;
        case Symbol::Id::R_PAR:
            os << ")";
            break;
        case Symbol::Id::PLUS:
            os << "+";
            break;
        case Symbol::Id::MULT:
            os << "*";
            break;
        case Symbol::Id::VAL:
            os << "VAL";
            break;
        case Symbol::Id::Eof:
            os << "$";
            break;
        default:
            throw std::invalid_argument("The symbol is invalid.");
    }
    return os;
}
