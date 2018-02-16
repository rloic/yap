#pragma once

#include "Symbol.h"

#include <map>

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
    size_t mCurrentSymbolSize;
    bool mHasNextSymbol;
};
