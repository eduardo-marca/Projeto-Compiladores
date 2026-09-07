#pragma once

#include "DFA.hpp"
#include "CharClass.hpp"

class Lexer {
public:
    explicit Lexer(const std::string& source);

    Token nextToken();

private:
    std::string source;
    std::size_t position = 0;

    DFA dfa;
};
