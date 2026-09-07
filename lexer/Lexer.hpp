#pragma once

#include "DFA.hpp"
#include "CharClass.hpp"
#include <unordered_map>

class Lexer {
public:
    explicit Lexer(const std::string& source);

    Token nextToken();

private:
    std::string source;
    std::size_t position = 0;

    DFA dfa;
    std::unordered_map<std::string, TokenType> reserved_words;
};
