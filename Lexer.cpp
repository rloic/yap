#include "Lexer.h"

#include <cassert>

#include "Symbols/Plus.h"
#include "Symbols/Mult.h"
#include "Symbols/LPar.h"
#include "Symbols/RPar.h"
#include "Symbols/Eof.h"
#include "Symbols/Val.h"

Lexer::Lexer(std::string input)
        : mInput{std::move(input)},
          mNextSymbolSize{} {

    mSimpleDecals['+'] = new Plus;
    mSimpleDecals['*'] = new Mult;
    mSimpleDecals['('] = new LPar;
    mSimpleDecals[')'] = new RPar;
    mSimpleDecals['\0'] = new Eof;
}

inline bool isInt(char c) {
    return c >= '0' && c <= '9';
}

Symbol *Lexer::getnext() {
    auto found = mSimpleDecals.find(mInput[mCursor]);
    if (found != mSimpleDecals.end()) {
        mNextSymbolSize = 1U;
        return new Symbol(*found->second);
    } else {
        int value = 0;
        auto cursor{mCursor};
        while (mInput[cursor] != '\0' && mSimpleDecals.find(mInput[cursor]) == mSimpleDecals.end()) {
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
        return new Val{value};
    }
}

void Lexer::movenext() {
    if (mNextSymbolSize == 0U) {
        getnext();
    }
    mCursor += mNextSymbolSize;
    mNextSymbolSize = 0U;
}
