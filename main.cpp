#include <iostream>

#include "Automata.h"
#include "Lexer.h"

int main() {
    std::string input;
    std::getline(std::cin, input);

//    // Test of the Lexer
//    {
//        Lexer lexer(input);
//        Symbol *current = nullptr;
//        while (current = lexer.getnext(), current->id() != IDs::Eof) {
//            current->print();
//            lexer.movenext();
//        }
//    }

    Automata automata{Lexer(input)};
    automata.read();

    return 0;
}
