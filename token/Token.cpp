#include "Token.hpp"

std::string Token::ToString() const
{
    return "<"  + to_string(type) + ", \"" + lexeme + "\">";
}