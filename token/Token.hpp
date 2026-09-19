#pragma once

#include "TokenType.hpp"
#include <string>

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;

    Token(TokenType type, std::string lexeme) : type(type), lexeme(lexeme) {}

    // Converte o token para uma string apresentável
    std::string ToString() const;
};
