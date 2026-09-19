#pragma once

#include "DFA.hpp"
#include "LexicalError.hpp"

#include <unordered_map>
#include <sstream>

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

    // tratamento de erros
    LexicalError error(const int line, const int column, std::string_view message);
};
