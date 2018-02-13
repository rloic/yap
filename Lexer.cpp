#include "Lexer.h"

#include "Symbols/TerminalSymbols.h"
#include "Symbols/Val.h"

Lexer::Lexer(std::string &&input)
        : mInput{std::move(input)},
          mCursor{0U},
          mNextSymbolSize{0U}{

    mSimpleTokens['+'] = Plus::Create();
    mSimpleTokens['*'] = Mult::Create();
    mSimpleTokens['('] = LPar::Create();
    mSimpleTokens[')'] = RPar::Create();
    mSimpleTokens['\0'] = Eof::Create();
}

static inline bool isInt(char c) {
    return c >= '0' && c <= '9';
}

Symbol::Ptr Lexer::GetNext() {
    auto found = mSimpleTokens.find(mInput[mCursor]);
    if (found != mSimpleTokens.end()) {
        mNextSymbolSize = 1U;
        return Symbol::Clone(found->second);
    } else {
        int value = 0;
        auto cursor{mCursor};
        while (mInput[cursor] != '\0' && mSimpleTokens.find(mInput[cursor]) == mSimpleTokens.end()) {
            const char current = mInput[cursor];
            if (isInt(current)) {
                value *= 10;
                value += current - '0';
            } else {
                std::cout << GRAS JAU << "[Warn] " << RESET
                          << JAU << "skipped unexpected symbol: " << RESET
                          << current
                          << std::endl;
            }
            ++cursor;
        }
        mNextSymbolSize = cursor - mCursor;
        return Val::Create(value);
    }
}

void Lexer::MoveNext() {
    if (mNextSymbolSize == 0U) {
        GetNext();
    }
    mCursor += mNextSymbolSize;
    mNextSymbolSize = 0U;
}
