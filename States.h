#pragma once

#include "Automata.h"

#define CREATE_STATE(N)                                                                     \
class State##N : public State {                                                             \
public:                                                                                     \
    static Ptr Create() {                                                                   \
        return Ptr(new State##N);                                                           \
    }                                                                                       \
    bool Transition(Automata &automata, Symbol::Ptr symbol, bool debug) override;           \
private:                                                                                    \
    State##N() : State("S"#N) {};                                                          \
};

#define CREATE_STATE_WITH_GOTO(N)                                                           \
class State##N : public State {                                                             \
public:                                                                                     \
    static Ptr Create() {                                                                   \
        return Ptr(new State##N);                                                           \
    }                                                                                       \
    bool Transition(Automata &automata, Symbol::Ptr symbol, bool debug) override;           \
    State::Ptr GoTo() override;                                                             \
private:                                                                                    \
    State##N() : State("S"#N) {};                                                          \
};

CREATE_STATE_WITH_GOTO(0)

CREATE_STATE(1)

CREATE_STATE_WITH_GOTO(2)

CREATE_STATE(3)

CREATE_STATE_WITH_GOTO(4)

CREATE_STATE_WITH_GOTO(5)

CREATE_STATE(6)

CREATE_STATE(7)

CREATE_STATE(8)

CREATE_STATE(9)
