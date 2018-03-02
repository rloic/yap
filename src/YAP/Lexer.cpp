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

#include <YAP/Lexer.h>

#include <YAP/Common.h>
#include <YAP/Symbol.h>
#include <YAP/TerminalSymbol.h>

namespace YAP {

Lexer::Lexer(std::string &&input)
        : mInput{std::move(input)},
          mCursor{0U},
          mCurrentSymbolSize{0U},
          mHasNextSymbol{true} {

    RegisterToken('\0', []() { return Eof::Create(); });
}

Symbol::Ptr Lexer::GetNext() {
    // Prevent overflow
    if (mCursor >= mInput.size()) {
        return Eof::Create();
    }

    std::vector<TokenRule*> candidates;
    std::copy(mTokenRules.begin(), mTokenRules.end(), std::back_inserter(candidates));

    auto cursor{mCursor};

    while (candidates.size() > 1U) {
        char current = mInput[cursor++];

        // Filter candidates
        for (auto it = candidates.begin(); it != candidates.end(); ) {
            if (!(*it)->Match(current)) {
                it = candidates.erase(it);
            } else ++it;
        }
    }

    // It should not, so we handle the error
    if (candidates.empty()) {
        using namespace Colors;
        std::cout << bold << yellow << "[Warn] " << reset
                  << yellow << "skipped unexpected symbol: '" << reset
                  << mInput[mCursor]
                  << yellow << "'" << reset
                  << std::endl;
        mCursor++;
        // TODO: test this recursive return
        return GetNext();
    }

    // Get the token rule
    TokenRule *rule = candidates.back();

    if (rule->IsSingleChar()) {
        assert(cursor - mCursor == 1U && "Single char rule needed more than one char.");
        mCurrentSymbolSize = 1U;
        return rule->GetSymbol(std::string(1, mInput[mCursor]));
    }

    while (rule->Match(mInput[cursor])) {
        cursor++;
    }

    mCurrentSymbolSize = cursor - mCursor;
    return rule->GetSymbol(std::string(mInput, mCursor, mCurrentSymbolSize));
}

void Lexer::MoveNext() {
    if (mCurrentSymbolSize == 0U && mHasNextSymbol) {
        GetNext();
    }
    mCursor += mCurrentSymbolSize;
    mCurrentSymbolSize = 0U;
}

} // namespace YAP
