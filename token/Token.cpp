#include "Token.hpp"

std::string Token::ToString() const
{
    return "<"  + to_string(type) + ", \"" + lexeme + "\", " +
        std::to_string(line) + ":" + std::to_string(column) + ">";
}
