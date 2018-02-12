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

    mCursor = mInput.begin();

    mSimpleDecals['+'] = new Plus;
    mSimpleDecals['*'] = new Mult;
    mSimpleDecals['('] = new LPar;
    mSimpleDecals[')'] = new RPar;
    mSimpleDecals['\0'] = new Eof;
}

inline bool isInt(char c) {
    return c >= '0' && c <= '9';
}

Symbol *Lexer::getnext() const {
    char nextChar = *mCursor;

    auto found = mSimpleDecals.find(nextChar);
    if (found != mSimpleDecals.end()) {
        mNextSymbolSize = 1U;
        return new Symbol(*found->second);
    }

    auto cursor = mCursor;
    int value = 0;
    while (isInt(*cursor)) {
        value *= 10;
        value += nextChar - '0';
        nextChar = *(++cursor);
    }
    mNextSymbolSize = static_cast<size_t>(std::distance(mCursor, cursor));
    if (mNextSymbolSize == 0) {
        std::cout << GRAS JAU << "[Warn] " << RESET << JAU << "unexpected symbol: " << RESET << *cursor << std::endl;
    }
    return new Val{value};
}

void Lexer::movenext() {
    if (mNextSymbolSize == 0U) {
        ++mCursor;
        getnext();
        movenext();
    }
    mCursor += mNextSymbolSize;
    mNextSymbolSize = 0U;
}
