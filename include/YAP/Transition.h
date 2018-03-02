/*
 * MIT License
 *
 * Copyright (c) 2018 insa.4if.hexanome_kalate
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#pragma once

#include <YAP/Common.h>
#include <YAP/Symbol.h>
#include <YAP/Automaton.h>
#include <YAP/Singleton.h>

#include <functional>

namespace YAP {

class Automaton;

class Transition {
public:
    virtual bool operator()(Automaton &automaton, Symbol::Ptr const &symbol) const = 0;

    inline bool execute(Automaton &automaton, Symbol::Ptr const &symbol) const {
        return operator()(automaton, symbol);
    }
};

template<State StateId>
class Shift final : public Transition, public Singleton<Shift<StateId>> {
public:
    bool operator()(Automaton &automaton, Symbol::Ptr const &symbol) const override {
        automaton.Shift(symbol, StateId);
        return true;
    }

private:
    friend class Singleton<Shift<StateId>>;

    Shift() = default;
};

class AcceptTransition final : public Transition, public Singleton<AcceptTransition> {
public:
    bool operator()(yap_unused Automaton &automaton, yap_unused Symbol::Ptr const &symbol) const override {
        return false;
    }

private:
    friend class Singleton<AcceptTransition>;

    AcceptTransition() = default;
};

class SkipTransition final : public Transition, public Singleton<SkipTransition> {
public:
    bool operator()(Automaton &automaton, yap_unused Symbol::Ptr const &symbol) const override {
        automaton.MoveNext();
        return true;
    }

private:
    friend class Singleton<SkipTransition>;

    SkipTransition() = default;
};

class SkipUnexpectedTransition final : public Transition, public Singleton<SkipUnexpectedTransition> {
public:
    bool operator()(Automaton &automaton, Symbol::Ptr const &symbol) const override {
        using namespace Colors;
        std::cout << bold << yellow << "[Warn] " << reset
                  << yellow << "Skipped unexpected token: " << reset << yellow << symbol
                  << reset << std::endl;
        automaton.MoveNext();
        return true;
    }

private:
    friend class Singleton<SkipUnexpectedTransition>;

    SkipUnexpectedTransition() = default;
};

using Reduction = Transition;

#define NEW_REDUCTION(name, action)                                                         \
class name : public YAP::Reduction, public YAP::Singleton<name> { /* NOLINT */              \
public:                                                                                     \
bool operator()(YAP::Automaton &automaton, YAP::Symbol::Ptr const &symbol) const override { \
        action                                                                              \
    }                                                                                       \
private:                                                                                    \
    friend class YAP::Singleton<name>;                                                      \
    name() = default;                                                                       \
};

} // namespace YAP
