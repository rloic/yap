#pragma once

#include "Transition.h"

class Reduction : public Transition {
public:
    explicit Reduction(TransitionFunction_t &&function) noexcept : Transition(std::forward<TransitionFunction_t>(function)) {}
    Reduction(Reduction const &) = delete;
    Reduction& operator=(Reduction const &) = delete;

    ~Reduction() override = default;
};
