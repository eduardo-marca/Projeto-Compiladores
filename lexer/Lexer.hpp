#pragma once

#include "DFA.hpp"
#include <unordered_map>

class Lexer {
public:
    explicit Lexer(const std::string& source);

    // acha o próximo token do código
    Token nextToken();

private:
    // código fonte
    std::string source;
    std::size_t position = 0;

    int line = 1;
    int column = 1;

    // autômato
    DFA dfa;

    std::unordered_map<std::string, TokenType> reserved_words;
};
