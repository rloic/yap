#pragma once

#include "Transition.h"

class Shift: public Transition {
public:
    explicit Shift(TransitionFunction_t &&function) noexcept : Transition(std::forward<TransitionFunction_t>(function)) {}
    Shift(Shift const&) = delete;
    Shift& operator=(Shift const &) = delete;

    ~Shift() override = default;
};
