#pragma once

#include <map>
#include "Symbol.h"

class Lexer {
public:
    explicit Lexer(std::string input);

    virtual ~Lexer() = default;

    Symbol* getnext() const;

    void movenext();

private:
    std::string mInput;
    std::string::iterator mCursor;
    std::map<char, Symbol*> mSimpleDecals;

    mutable size_t mNextSymbolSize;
};
