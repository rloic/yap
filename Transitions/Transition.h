#pragma once

#include <functional>

#include "../Automata.h"

#define unused __attribute__((unused))

class Transition {
public:
    using TransitionFunction_t = std::function<bool(Automata &, Symbol::Ptr const &)>;

    explicit Transition(TransitionFunction_t &&function) noexcept : mFunction{std::move(function)} {}
    Transition(Transition const&) = delete;
    Transition& operator=(Transition const &) = delete;

    virtual ~Transition() = default;
    virtual bool execute(Automata & automata, Symbol::Ptr const & symbol) const {
        return mFunction(automata, symbol);
    }

protected:
    TransitionFunction_t mFunction{};
};
