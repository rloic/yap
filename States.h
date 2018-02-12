#pragma once

#include "Automata.h"

class State0 : public State {
public:
    State0() : State("S0") {};
    bool transition(Automata &automata, Symbol *symbol, bool debug = false) override;

    State *GoTo() override;
};

class State1 : public State {
public:
    State1() : State("S1") {};
    bool transition(Automata &automata, Symbol *symbol, bool debug = false) override;
};

class State2 : public State {
public:
    State2() : State("S2") {};
    bool transition(Automata &automata, Symbol *symbol, bool debug = false) override;

    State *GoTo() override;
};

class State3 : public State {
public:
    State3() : State("S3") {};
    bool transition(Automata &automata, Symbol *symbol, bool debug = false) override;
};

class State4 : public State {
public:
    State4() : State("S4") {};
    bool transition(Automata &automata, Symbol *symbol, bool debug = false) override;

    State *GoTo() override;
};

class State5 : public State {
public:
    State5() : State("S5") {};
    bool transition(Automata &automata, Symbol *symbol, bool debug = false) override;

    State *GoTo() override;
};

class State6 : public State {
public:
    State6() : State("S6") {};
    bool transition(Automata &automata, Symbol *symbol, bool debug = false) override;
};

class State7 : public State {
public:
    State7() : State("S7") {};
    bool transition(Automata &automata, Symbol *symbol, bool debug = false) override;
};

class State8 : public State {
public:
    State8() : State("S8") {};
    bool transition(Automata &automata, Symbol *symbol, bool debug = false) override;
};

class State9 : public State {
public:
    State9() : State("S9") {};
    bool transition(Automata &automata, Symbol *symbol, bool debug = false) override;
};
