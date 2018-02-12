#pragma once

#include <map>
#include "Symbol.h"

class Lexer {
public:
    explicit Lexer(std::string &&input);

    virtual ~Lexer() = default;

    Symbol::Ptr GetNext();

    void MoveNext();

private:
    std::string mInput;
    size_t mCursor;
    std::map<char, Symbol::Ptr> mSimpleTokens;
    size_t mNextSymbolSize;
};
