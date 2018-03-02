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
    auto result{automaton.Read(YAP::State(0))};

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
    using YAP::SkipTransition;

    automaton.AddTransitions()

            .Add<d10>(State(0), SEP)
            .Add<d2>(State(0), CONST)
            .Add<d13>(State(0), VAL)
            .Add<d20>(State(0), VAR)
            .Add<d12>(State(0), L_PAR)
            .Add<AcceptTransition>(State(0), Symbol::Eof)

            .Add<d10>(State(1), SEP)
            .Add<AcceptTransition>(State(1), Symbol::Eof)

            .Add<d10>(State(2), EQUAL)
            .Add<AcceptTransition>(State(2), Symbol::Eof)

            .Add<rconst>(State(3), COMMA)
            .Add<rconst>(State(3), SEP)

            .Add<d13>(State(10), VAL)
            .Add<d20>(State(10), VAR)
            .Add<d21>(State(10), CONST)
            .Add<d12>(State(10), L_PAR)
            .Add<d0>(State(10), COMMA)
            .Add<SkipTransition>(State(10), SEP)
            .Add<AcceptTransition>(State(10), Symbol::Eof)

            .Add<d14>(State(11), PLUS)
            .Add<d15>(State(11), TIMES)
            .Add<rconst>(State(11), COMMA)
            .Add<rconst>(State(11), SEP)
            .Add<d3>(State(11), Symbol::Eof)
            .Add<AcceptTransition>(State(11), Symbol::Eof)

            .Add<d13>(State(12), VAL)
            .Add<d20>(State(12), VAR)
            .Add<d21>(State(12), CONST)
            .Add<d12>(State(12), L_PAR)
            .Add<AcceptTransition>(State(12), R_PAR) // Prevent an infinite loop for inputs like "1+()"
            .Add<AcceptTransition>(State(12), Symbol::Eof) // Prevent an infinite loop for inputs like "(=)"

            .Add<r5>(State(13), PLUS)
            .Add<r5>(State(13), TIMES)
            .Add<r5>(State(13), R_PAR)
            .Add<r5>(State(13), SEP)
            .Add<r5>(State(13), COMMA)
            .Add<r5>(State(13), Symbol::Eof)

            .Add<d13>(State(14), VAL)
            .Add<d20>(State(14), VAR)
            .Add<d21>(State(14), CONST)
            .Add<d12>(State(14), L_PAR)

            .Add<d13>(State(15), VAL)
            .Add<d20>(State(15), VAR)
            .Add<d21>(State(15), CONST)
            .Add<d12>(State(15), L_PAR)

            .Add<d14>(State(16), PLUS)
            .Add<d15>(State(16), TIMES)
            .Add<d19>(State(16), R_PAR)
            .Add<d3>(State(16), SEP)
            .Add<d3>(State(16), COMMA)

            .Add<r2>(State(17), PLUS)
            .Add<d15>(State(17), TIMES)
            .Add<r2>(State(17), R_PAR)
            .Add<r2>(State(17), SEP)
            .Add<r2>(State(17), COMMA)
            .Add<r2>(State(17), Symbol::Eof)

            .Add<r3>(State(18), PLUS)
            .Add<r3>(State(18), TIMES)
            .Add<r3>(State(18), R_PAR)
            .Add<r3>(State(18), SEP)
            .Add<r3>(State(18), COMMA)
            .Add<r3>(State(18), Symbol::Eof)

            .Add<r4>(State(19), PLUS)
            .Add<r4>(State(19), TIMES)
            .Add<r4>(State(19), R_PAR)
            .Add<r4>(State(19), SEP)
            .Add<r4>(State(19), COMMA)
            .Add<r4>(State(19), Symbol::Eof)

            .Add<r6>(State(20), PLUS)
            .Add<r6>(State(20), TIMES)
            .Add<r6>(State(20), R_PAR)
            .Add<r6>(State(20), SEP)
            .Add<r6>(State(20), COMMA)
            .Add<r6>(State(20), Symbol::Eof)

            .Add<r7>(State(21), PLUS)
            .Add<r7>(State(21), TIMES)
            .Add<r7>(State(21), R_PAR)
            .Add<r7>(State(21), SEP)
            .Add<r7>(State(21), COMMA)
            .Add<r7>(State(21), Symbol::Eof)

            .Add(State(0), CONST, State(10))
            .Add(State(0), EXPR, State(11))
            .Add(State(10), EXPR, State(11))
            .Add(State(14), EXPR, State(17))
            .Add(State(15), EXPR, State(18))
            .Add(State(12), EXPR, State(16));
}

void configureLexer(YAP::Lexer &lexer) {
    lexer.RegisterToken('+', []() { return Plus::Create(); });
    lexer.RegisterToken('*', []() { return Mult::Create(); });
    lexer.RegisterToken('(', []() { return LPar::Create(); });
    lexer.RegisterToken(')', []() { return RPar::Create(); });
    lexer.RegisterToken('=', []() { return Equal::Create(); });
    lexer.RegisterToken(';', []() { return Sep::Create(); });
    lexer.RegisterToken(',', []() { return Comma::Create(); });
    lexer.RegisterToken(std::regex("[0-9]"), [](std::string const &str) {
        return Val::Create(std::stoull(str));
    });
    lexer.RegisterToken(std::regex("[a-z]"), [](std::string const &str) {
        return Var::Create(str);
    });
    lexer.RegisterToken(std::regex("[A-Z]"), [](std::string const &str) {
        return Const::Create(str);
    });
}

bool askDebug() {

    using namespace YAP::Colors;
    std::cout << blue << "Do you want to enable the verbose mode? [y/N] " << reset;

    std::string input;
    std::getline(std::cin, input);

    return input.empty() && (input[0] == 'y' || input[0] == 'Y');
}
