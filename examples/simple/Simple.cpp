// This header defines the symbols
#include "Symbols.h"

// This header defines the transitions
#include "Transitions.h"

#include <YAP/YAP.h>

#include <iostream> // For cout, endl
#include <string> // For stoull


void configureAutomata(YAP::Automata &automata);

void configureLexer(YAP::Lexer &lexer);


int main() {
    std::string input;
    std::getline(std::cin, input);
    if (input.empty()) {
        std::cout << JAU << "Please enter a non-empty expression." << RESET << std::endl;
        return 0;
    }

    // Create and configure the lexer
    YAP::Lexer lexer(std::move(input));
    configureLexer(lexer);

    // Create and configure the automata
    YAP::Automata automata{lexer};
    configureAutomata(automata);

    // Query the result
    auto result = automata.Read();

    // Display the result
    if (!dynamic_cast<Expr *>(result.get())) {
        std::cout << GRAS RGE << "[Error] No result." << RESET << std::endl;
    } else {
        std::cout << GRAS VRT << "Result: " << RESET
                  << VRT << dynamic_cast<Expr *>(result.get())->GetValue() << RESET
                  << std::endl;
    }

    return 0;
}

void configureAutomata(YAP::Automata &automata) {
    using namespace Shifts;
    using namespace Reductions;

    using YAP::State;
    using YAP::Symbol;
    using YAP::AcceptTransition;

    automata.AddTransitions()

            .Add<d3>(State(0), Symbol::Id::VAL)
            .Add<d2>(State(0), Symbol::Id::L_PAR)
            .Add<AcceptTransition>(State(0), Symbol::Id::Eof)

            .Add<d4>(State(1), Symbol::Id::PLUS)
            .Add<d5>(State(1), Symbol::Id::MULT)
            .Add<AcceptTransition>(State(1), Symbol::Id::Eof)

            .Add<d3>(State(2), Symbol::Id::VAL)
            .Add<d2>(State(2), Symbol::Id::L_PAR)

            .Add<r5>(State(3), Symbol::Id::PLUS)
            .Add<r5>(State(3), Symbol::Id::MULT)
            .Add<r5>(State(3), Symbol::Id::R_PAR)
            .Add<r5>(State(3), Symbol::Id::Eof)

            .Add<d3>(State(4), Symbol::Id::VAL)
            .Add<d2>(State(4), Symbol::Id::L_PAR)

            .Add<d3>(State(5), Symbol::Id::VAL)
            .Add<d2>(State(5), Symbol::Id::L_PAR)

            .Add<d4>(State(6), Symbol::Id::PLUS)
            .Add<d5>(State(6), Symbol::Id::MULT)
            .Add<d9>(State(6), Symbol::Id::R_PAR)

            .Add<r2>(State(7), Symbol::Id::PLUS)
            .Add<d5>(State(7), Symbol::Id::MULT)
            .Add<r2>(State(7), Symbol::Id::R_PAR)
            .Add<r2>(State(7), Symbol::Id::Eof)

            .Add<r3>(State(8), Symbol::Id::PLUS)
            .Add<r3>(State(8), Symbol::Id::MULT)
            .Add<r3>(State(8), Symbol::Id::R_PAR)
            .Add<r3>(State(8), Symbol::Id::Eof)

            .Add<r4>(State(9), Symbol::Id::PLUS)
            .Add<r4>(State(9), Symbol::Id::MULT)
            .Add<r4>(State(9), Symbol::Id::R_PAR)
            .Add<r4>(State(9), Symbol::Id::Eof)

            .Add(State(0), State(1))
            .Add(State(4), State(7))
            .Add(State(5), State(8))
            .Add(State(2), State(6));
}

void configureLexer(YAP::Lexer &lexer) {
    lexer.RegisterToken('+', []() { return Plus::Create(); });
    lexer.RegisterToken('*', []() { return Mult::Create(); });
    lexer.RegisterToken('(', []() { return LPar::Create(); });
    lexer.RegisterToken(')', []() { return RPar::Create(); });
    lexer.RegisterToken(std::regex("[0-9]"), [](std::string const &str) {
        return Val::Create(std::stoull(str));
    });
}
