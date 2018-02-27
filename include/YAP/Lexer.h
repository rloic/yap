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

#pragma once

#include <YAP/Symbol.h>
#include <YAP/TokenRule.h>

#include <regex>
#include <map>

namespace YAP {

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

} // namespace YAP
