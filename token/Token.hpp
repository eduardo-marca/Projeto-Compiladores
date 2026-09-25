#pragma once

#include "TokenType.hpp"
#include "Value.hpp"

#include <cstdint>
#include <string>

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;
    Value value;

  public:
    Token(TokenType type, std::string lexeme, int line, int column)
        : type(type), lexeme(lexeme), line(line), column(column) {}

    // Converte o token para uma string apresentável
    std::string ToString() const;
};
