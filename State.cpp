#include "State.h"

State::State(std::string &&name)
        : mName{std::move(name)} {}

State::Ptr State::GoTo() {
    std::cout << GRAS RGE << "Illegal state (GoTo)." << RESET << std::endl;
    exit(0);
}

std::ostream &operator<<(std::ostream &os, const State &state) {
    os << MAG << state.mName << RESET;
    return os;
}
