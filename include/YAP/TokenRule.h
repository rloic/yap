#pragma once

#include <YAP/Symbol.h>

#include <regex>
#include <utility>

namespace YAP {

class TokenRule {
public:
    TokenRule() = default;

    virtual ~TokenRule() = default;

    virtual bool Match(char currentChar) const = 0;

    virtual Symbol::Ptr GetSymbol(const std::string& str) const = 0;

    virtual bool IsSingleChar() const = 0;
};

template<typename FromStringFunc>
class SimpleTokenRule : public TokenRule {
public:
    explicit SimpleTokenRule(char character, FromStringFunc fromStringFunc)
            : mChar{character},
              mFromStringFunc{fromStringFunc} {
        static_assert(
                std::is_invocable<FromStringFunc, std::string const&>::value
                || std::is_invocable<FromStringFunc>::value,
                "FromStringFunc must be a function that either turns a string into a symbol or takes no argument."
        );
    }

    bool Match(char currentChar) const override {
        return currentChar == mChar;
    }

    Symbol::Ptr GetSymbol(const std::string& str) const override {
        if constexpr (std::is_invocable<FromStringFunc, std::string const&>::value) {
            return mFromStringFunc(str);
        } else {
            return mFromStringFunc();
        }
    }

    bool IsSingleChar() const override {
        return true;
    }

private:
    char mChar;
    FromStringFunc mFromStringFunc;
};

template<typename FromStringFunc>
class RegexTokenRule : public TokenRule {
public:
    explicit RegexTokenRule(std::regex &&regex, FromStringFunc fromStringFunc)
            : mRegex{std::move(regex)},
              mFromStringFunc{fromStringFunc} {
        static_assert(
                std::is_invocable<FromStringFunc, std::string const&>::value
                || std::is_invocable<FromStringFunc>::value,
                "FromStringFunc must be a function that either turns a string into a symbol or takes no argument."
        );
    }

    bool Match(char currentChar) const override {
        return std::regex_match(std::string(1, currentChar), mRegex) != 0;
    }

    Symbol::Ptr GetSymbol(const std::string& str) const override {
        if constexpr (std::is_invocable<FromStringFunc, std::string const&>::value) {
            return mFromStringFunc(str);
        } else {
            return mFromStringFunc();
        }
    }

    bool IsSingleChar() const override {
        return false;
    }

private:
    std::regex mRegex;
    FromStringFunc mFromStringFunc;
};

} // namespace YAP
