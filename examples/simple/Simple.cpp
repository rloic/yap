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
    using namespace YAP::Colors;

    std::string input;
    std::getline(std::cin, input);
    if (input.empty()) {
        std::cout << yellow << "Please enter a non-empty expression." << reset << std::endl;
        return 0;
    }

    // Create and configure the lexer
    YAP::Lexer lexer{std::move(input)};
    configureLexer(lexer);

    // Create and configure the automata
    YAP::Automata automata{lexer};
    configureAutomata(automata);

    // Query the result
    auto result{automata.Read()};

    // Display the result
    if (!dynamic_cast<Expr *>(result.get())) {
        std::cout << bold << red << "[Error] No result." << reset << std::endl;
    } else {
        std::cout << bold << green << "Result: " << reset
                  << green << dynamic_cast<Expr *>(result.get())->GetValue() << reset
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

            .Add<d3>(State(0), VAL)
            .Add<d2>(State(0), L_PAR)

            .Add<d4>(State(1), PLUS)
            .Add<d5>(State(1), TIMES)
            .Add<AcceptTransition>(State(1), Symbol::Eof)

            .Add<d3>(State(2), VAL)
            .Add<d2>(State(2), L_PAR)

            .Add<r5>(State(3), PLUS)
            .Add<r5>(State(3), TIMES)
            .Add<r5>(State(3), R_PAR)
            .Add<r5>(State(3), Symbol::Eof)

            .Add<d3>(State(4), VAL)
            .Add<d2>(State(4), L_PAR)

            .Add<d3>(State(5), VAL)
            .Add<d2>(State(5), L_PAR)

            .Add<d4>(State(6), PLUS)
            .Add<d5>(State(6), TIMES)
            .Add<d9>(State(6), R_PAR)

            .Add<r2>(State(7), PLUS)
            .Add<d5>(State(7), TIMES)
            .Add<r2>(State(7), R_PAR)
            .Add<r2>(State(7), Symbol::Eof)

            .Add<r3>(State(8), PLUS)
            .Add<r3>(State(8), TIMES)
            .Add<r3>(State(8), R_PAR)
            .Add<r3>(State(8), Symbol::Eof)

            .Add<r4>(State(9), PLUS)
            .Add<r4>(State(9), TIMES)
            .Add<r4>(State(9), R_PAR)
            .Add<r4>(State(9), Symbol::Eof)

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
