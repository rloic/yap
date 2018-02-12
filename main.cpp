#include <iostream>

#include "Automata.h"

int main() {
    std::string input;
    std::getline(std::cin, input);

    Automata automata{Lexer(std::move(input)), false};
    automata.Read();

    return 0;
}
