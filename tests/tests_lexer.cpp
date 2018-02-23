#include <gtest/gtest.h>

#include <YAP/YAP.h>


TEST(LexerTests, empty_input_eof) { // NOLINT

    // Create a lexer with an empty input
    YAP::Lexer lexer{""};

    // Get a symbol from the lexer
    auto s = lexer.GetNext();

    // Verify its type
    ASSERT_EQ(s->GetId(), YAP::Symbol::Eof);
}

TEST(LexerTests, terminal_symbol) { // NOLINT

    // Create a lexer with a one-character input
    YAP::Lexer lexer{"-"};

    // Create a minus symbol
    enum Symbols : size_t {
        MINUS
    };
    using Minus = YAP::TerminalSymbol<MINUS, '-'>;

    // Register a minus token
    lexer.RegisterToken('-', []() { return Minus::Create(); });

    // Get one symbol, along with the EOF symbol
    auto s1 = lexer.GetNext();
    lexer.MoveNext();
    auto s2 = lexer.GetNext();

    // Verify their types
    ASSERT_EQ(s1->GetId(), MINUS);
    ASSERT_EQ(s2->GetId(), YAP::Symbol::Eof);
}

TEST(LexerTests, valued_symbol) { // NOLINT

    // Create a lexer with a number
    YAP::Lexer lexer{"1337"};

    // Create the symbol
    enum Symbols : size_t {
        VAL
    };
    using Val = YAP::ValuedSymbol<long long, VAL, 'V'>;

    // Register a token to read numbers
    lexer.RegisterToken(std::regex("[0-9]"), [](std::string const &str) {
        return Val::Create(std::stoull(str));
    });

    // Get one symbol, along with the EOF symbol
    auto s1 = lexer.GetNext();
    lexer.MoveNext();
    auto s2 = lexer.GetNext();

    // Verify their types
    ASSERT_EQ(s1->GetId(), VAL);
    ASSERT_EQ(s2->GetId(), YAP::Symbol::Eof);

    // Verify the values of the valued symbols
    auto v1 = dynamic_cast<Val*>(s1.get());
    ASSERT_TRUE(v1 != nullptr);
    ASSERT_EQ(v1->GetValue(), 1337);
}

TEST(LexerTests, valued_symbol_negative) { // NOLINT

    // Create a lexer with a number
    YAP::Lexer lexer{"-70"};

    // Create the symbol
    enum Symbols : size_t {
        VAL
    };
    using Val = YAP::ValuedSymbol<int, VAL>; // Omit the debug name

    // Register a token to read negative numbers
    lexer.RegisterToken(std::regex("[\\-0-9]"), [](std::string const &str) {
        return Val::Create(std::stoi(str));
    });

    // Get one symbol, along with the EOF symbol
    auto s1 = lexer.GetNext();
    lexer.MoveNext();
    auto s2 = lexer.GetNext();

    // Verify their types
    ASSERT_EQ(s1->GetId(), VAL);
    ASSERT_EQ(s2->GetId(), YAP::Symbol::Eof);

    // Verify the values of the valued symbols
    auto v1 = dynamic_cast<Val*>(s1.get());
    ASSERT_TRUE(v1 != nullptr);
    ASSERT_EQ(v1->GetValue(), -70);
}

TEST(LexerTests, valued_symbol_decimal) { // NOLINT

    // Create a lexer with a number
    YAP::Lexer lexer{"7.43"};

    // Create the symbol
    enum Symbols : size_t {
        VAL
    };
    using Val = YAP::ValuedSymbol<double, VAL, 'V'>;

    // Register a token to read numbers
    lexer.RegisterToken(std::regex("[\\.0-9]"), [](std::string const &str) {
        return Val::Create(std::stod(str));
    });

    // Get one symbol, along with the EOF symbol
    auto s1 = lexer.GetNext();
    lexer.MoveNext();
    auto s2 = lexer.GetNext();

    // Verify their types
    ASSERT_EQ(s1->GetId(), VAL);
    ASSERT_EQ(s2->GetId(), YAP::Symbol::Eof);

    // Verify the values of the valued symbols
    auto v1 = dynamic_cast<Val*>(s1.get());
    ASSERT_TRUE(v1 != nullptr);
    ASSERT_EQ(v1->GetValue(), 7.43);
}

TEST(LexerTests, simple_grammar) { // NOLINT

    /* Create a lexer */
    YAP::Lexer lexer{"1+2*56"};

    // Create symbols
    enum Symbols : size_t {
        L_PAR,
        R_PAR,
        TIMES,
        PLUS,
        VAL
    };
    using LPar = YAP::TerminalSymbol<L_PAR, '('>;
    using RPar = YAP::TerminalSymbol<R_PAR, ')'>;
    using Times = YAP::TerminalSymbol<TIMES, '*'>;
    using Plus = YAP::TerminalSymbol<PLUS, '+'>;
    using Val = YAP::ValuedSymbol<long long, VAL, 'V'>;

    // Register tokens
    lexer.RegisterToken('+', []() { return Plus::Create(); });
    lexer.RegisterToken('*', []() { return Times::Create(); });
    lexer.RegisterToken('(', []() { return LPar::Create(); });
    lexer.RegisterToken(')', []() { return RPar::Create(); });
    lexer.RegisterToken(std::regex("[0-9]"), [](std::string const &str) {
        return Val::Create(std::stoull(str));
    });

    /* Test the lexer */
    // Get the symbols from the lexer
    auto s1 = lexer.GetNext();
    lexer.MoveNext();
    auto s2 = lexer.GetNext();
    lexer.MoveNext();
    auto s3 = lexer.GetNext();
    lexer.MoveNext();
    auto s4 = lexer.GetNext();
    lexer.MoveNext();
    auto s5 = lexer.GetNext();
    lexer.MoveNext();
    auto s6 = lexer.GetNext();

    // Verify their types
    ASSERT_EQ(s1->GetId(), VAL);
    ASSERT_EQ(s2->GetId(), PLUS);
    ASSERT_EQ(s3->GetId(), VAL);
    ASSERT_EQ(s4->GetId(), TIMES);
    ASSERT_EQ(s5->GetId(), VAL);
    ASSERT_EQ(s6->GetId(), YAP::Symbol::Eof);

    // Verify the values of the valued symbols
    auto v1 = dynamic_cast<Val*>(s1.get());
    ASSERT_TRUE(v1 != nullptr);
    auto v3 = dynamic_cast<Val*>(s3.get());
    ASSERT_TRUE(v3 != nullptr);
    auto v5 = dynamic_cast<Val*>(s5.get());
    ASSERT_TRUE(v5 != nullptr);
    ASSERT_EQ(v1->GetValue(), 1);
    ASSERT_EQ(v3->GetValue(), 2);
    ASSERT_EQ(v5->GetValue(), 56);
}
