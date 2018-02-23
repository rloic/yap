#pragma once

#include <YAP/Common.h>
#include <YAP/Symbol.h>
#include <YAP/Automata.h>
#include <YAP/Singleton.h>

#include <functional>

namespace YAP {

class Automata;

class Transition {
public:
    virtual bool operator()(Automata &automata, Symbol::Ptr const &symbol) const = 0;

    inline bool execute(Automata &automata, Symbol::Ptr const &symbol) const {
        return operator()(automata, symbol);
    }
};

template<State StateId>
class Shift final : public Transition, public Singleton<Shift<StateId>> {
public:
    bool operator()(Automata &automata, Symbol::Ptr const &symbol) const override {
        automata.Shift(symbol, StateId);
        return true;
    }

private:
    friend class Singleton<Shift<StateId>>;

    Shift() = default;
};

class AcceptTransition final : public Transition, public Singleton<AcceptTransition> {
public:
    bool operator()(yap_unused Automata &automata, yap_unused Symbol::Ptr const &symbol) const override {
        return false;
    }

private:
    friend class Singleton<AcceptTransition>;

    AcceptTransition() = default;
};

class SkipTransition final : public Transition, public Singleton<SkipTransition> {
public:
    bool operator()(yap_unused Automata &automata, yap_unused Symbol::Ptr const &symbol) const override {
        return true;
    }

private:
    friend class Singleton<SkipTransition>;

    SkipTransition() = default;
};

class SkipUnexpectedTransition final : public Transition, public Singleton<SkipUnexpectedTransition> {
public:
    bool operator()(yap_unused Automata &automata, Symbol::Ptr const &symbol) const override {
        using namespace Colors;
        std::cerr << bold << yellow << "[Warn] " << reset
                  << yellow << "Skipped unexpected token: " << reset << yellow << symbol
                  << reset << std::endl;
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
bool operator()(YAP::Automata &automata, YAP::Symbol::Ptr const &symbol) const override {   \
        action                                                                              \
    }                                                                                       \
private:                                                                                    \
    friend class YAP::Singleton<name>;                                                      \
    name() = default;                                                                       \
};

} // namespace YAP
