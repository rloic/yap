#include <iostream>

#include "Automata.h"
#include "Lexer.h"

int main() {
    std::string input;
    std::getline(std::cin, input);

    Automata automata{Lexer(input)};
    automata.read();

    return 0;
}
