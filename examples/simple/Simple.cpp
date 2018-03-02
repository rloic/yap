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

// This header defines the symbols
#include "Symbols.h"

// This header defines the transitions
#include "Transitions.h"

#include <YAP/YAP.h>

#include <iostream> // For cout, endl
#include <string> // For stoull


void configureAutomaton(YAP::Automaton &automaton);

void configureLexer(YAP::Lexer &lexer);

bool askDebug();


int main() {
    using namespace YAP::Colors;

    std::string input;
    std::getline(std::cin, input);

    // Create and configure the lexer
    YAP::Lexer lexer{std::move(input)};
    configureLexer(lexer);

    // Create and configure the automaton
    YAP::Automaton automaton{lexer, askDebug()};
    configureAutomaton(automaton);

    // Query the result
    auto result{automaton.Read()};

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

void configureAutomaton(YAP::Automaton &automaton) {
    using namespace Shifts;
    using namespace Reductions;

    using YAP::State;
    using YAP::Symbol;
    using YAP::AcceptTransition;

    automaton.AddTransitions()

            .Add<d3>(State(0), VAL)
            .Add<d2>(State(0), L_PAR)
            .Add<AcceptTransition>(State(0), Symbol::Eof) // Prevent some invalid input from going into infinite loop

            .Add<d4>(State(1), PLUS)
            .Add<d5>(State(1), TIMES)
            .Add<AcceptTransition>(State(1), Symbol::Eof)

            .Add<d3>(State(2), VAL)
            .Add<d2>(State(2), L_PAR)
            .Add<AcceptTransition>(State(2), R_PAR) // Prevent an infinite loop for inputs like "1+()"

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

            .Add(State(0), EXPR, State(1))
            .Add(State(4), EXPR, State(7))
            .Add(State(5), EXPR, State(8))
            .Add(State(2), EXPR, State(6));
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

bool askDebug() {

    using namespace YAP::Colors;
    std::cout << blue << "Do you want to enable the verbose mode? [y/N] " << reset;

    std::string input;
    std::getline(std::cin, input);

    return input.empty() && (input[0] == 'y' || input[0] == 'Y');
}
