#pragma once

#include <YAP/Symbol.h>

#include <regex>
#include <map>
#include "TokenRule.h"

class Lexer {
public:
    explicit Lexer(std::string &&input);

    virtual ~Lexer() = default;

    Symbol::Ptr GetNext();

    void MoveNext();

    template<typename FromStringFunc>
    void RegisterToken(char token, FromStringFunc fromStringFunc);

    template<typename FromStringFunc>
    void RegisterToken(std::regex &&regex, FromStringFunc fromStringFunc);

private:
    std::string mInput;
    size_t mCursor;
    std::vector<TokenRule*> mTokenRules;
    size_t mCurrentSymbolSize;
    bool mHasNextSymbol;
};

template<typename FromStringFunc>
void Lexer::RegisterToken(char token, FromStringFunc fromStringFunc) {
    mTokenRules.push_back(new SimpleTokenRule{
            token,
            std::move(fromStringFunc)
    });
}

template<typename FromStringFunc>
void Lexer::RegisterToken(std::regex &&regex, FromStringFunc fromStringFunc) {
    mTokenRules.push_back(new RegexTokenRule{
            std::forward<std::regex>(regex),
            std::move(fromStringFunc)
    });
}
