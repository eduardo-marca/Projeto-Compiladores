#pragma once

#include "TokenType.hpp"
#include <string>

struct Token {
    TokenType type;
    std::string lexeme;

    Token(TokenType type, std::string value) : type(type), lexeme(value) {}

    std::string ToString() const;
};
