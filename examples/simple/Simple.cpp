#include <iostream>

#include "Transitions.h"
#include "Symbols.h"

#include <YAP/Automata.h>
#include <string>

int main() {
    std::string input;
    std::getline(std::cin, input);

    Lexer lexer(std::move(input));

    // Configure the lexer
    lexer.RegisterToken('+', []() { return Plus::Create(); });
    lexer.RegisterToken('*', []() { return Mult::Create(); });
    lexer.RegisterToken('(', []() { return LPar::Create(); });
    lexer.RegisterToken(')', []() { return RPar::Create(); });
    lexer.RegisterToken(std::regex("[0-9]"), [](std::string const& str) {
        return Val::Create(std::stoull(str));
    });

    Automata automata{lexer};

    using namespace Shifts;
    using namespace Reductions;

    automata.AddTransition<d3>(State(0), Symbol::Id::VAL);
    automata.AddTransition<d2>(State(0), Symbol::Id::L_PAR);
    automata.AddTransition<AcceptTransition>(State(0), Symbol::Id::Eof);

    automata.AddTransition<d4>(State(1), Symbol::Id::PLUS);
    automata.AddTransition<d5>(State(1), Symbol::Id::MULT);
    automata.AddTransition<AcceptTransition>(State(1), Symbol::Id::Eof);

    automata.AddTransition<d3>(State(2), Symbol::Id::VAL);
    automata.AddTransition<d2>(State(2), Symbol::Id::L_PAR);

    automata.AddTransition<r5>(State(3), Symbol::Id::PLUS);
    automata.AddTransition<r5>(State(3), Symbol::Id::MULT);
    automata.AddTransition<r5>(State(3), Symbol::Id::R_PAR);
    automata.AddTransition<r5>(State(3), Symbol::Id::Eof);

    automata.AddTransition<d3>(State(4), Symbol::Id::VAL);
    automata.AddTransition<d2>(State(4), Symbol::Id::L_PAR);

    automata.AddTransition<d3>(State(5), Symbol::Id::VAL);
    automata.AddTransition<d2>(State(5), Symbol::Id::L_PAR);

    automata.AddTransition<d4>(State(6), Symbol::Id::PLUS);
    automata.AddTransition<d5>(State(6), Symbol::Id::MULT);
    automata.AddTransition<d9>(State(6), Symbol::Id::R_PAR);

    automata.AddTransition<r2>(State(7), Symbol::Id::PLUS);
    automata.AddTransition<d5>(State(7), Symbol::Id::MULT);
    automata.AddTransition<r2>(State(7), Symbol::Id::R_PAR);
    automata.AddTransition<r2>(State(7), Symbol::Id::Eof);

    automata.AddTransition<r3>(State(8), Symbol::Id::PLUS);
    automata.AddTransition<r3>(State(8), Symbol::Id::MULT);
    automata.AddTransition<r3>(State(8), Symbol::Id::R_PAR);
    automata.AddTransition<r3>(State(8), Symbol::Id::Eof);

    automata.AddTransition<r4>(State(9), Symbol::Id::PLUS);
    automata.AddTransition<r4>(State(9), Symbol::Id::MULT);
    automata.AddTransition<r4>(State(9), Symbol::Id::R_PAR);
    automata.AddTransition<r4>(State(9), Symbol::Id::Eof);

    automata.AddGoToTransition(State(0), State(1));
    automata.AddGoToTransition(State(4), State(7));
    automata.AddGoToTransition(State(5), State(8));
    automata.AddGoToTransition(State(2), State(6));

    auto result = automata.Read();

    if (!dynamic_cast<Expr *>(result.get())) {
        std::cout << GRAS RGE << "No result due to Error." << RESET << std::endl;
    } else {
        std::cout << GRAS VRT << "Result: " << RESET
                  << VRT << dynamic_cast<Expr *>(result.get())->GetValue() << RESET
                  << std::endl;
    }

    return 0;
}
