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
        std::cerr << GRAS JAU << "[Warn] " << RESET
                  << JAU << "skipped unexpected symbol: " << RESET
                  << mInput[mCursor]
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
