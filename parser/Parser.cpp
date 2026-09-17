#include "Parser.hpp"
#include "ParseError.hpp"

#include "BinaryExpression.hpp"
#include "AssignmentExpression.hpp"

const Token &Parser::peek() const
{
    return tokens[current];
}

const Token &Parser::previous() const
{
    return tokens[current-1];
}

bool Parser::check(TokenType type) const
{
    return tokens[current].type == type;
}

bool Parser::match(TokenType type)
{
    if(!check(type))
        return false;

    advance();
    return true;
}

bool Parser::match(std::vector<TokenType> types)
{
    for(TokenType type : types) {
        if(check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

const Token &Parser::expect(TokenType type)
{
    if(check(type))
        return advance();

    throw ParseError("Token of type <" + to_string(type) + "> expected");
}

const Token &Parser::advance()
{
    current++;
    return tokens[current-1];
}

const Token &Parser::consume(TokenType type)
{
    if(check(type))
        return advance();

    throw ParseError("Token of type <" + to_string(type) + "> expected");
}

bool Parser::atEnd() const
{
    return current >= tokens.size();
}

ExpressionPtr Parser::parseExpression()
{
    return parseAssignment();
}

ExpressionPtr Parser::parseAssignment()
{
    auto left = parseLogicalOr();

    if(match({TokenType::EQUAL, TokenType::PLUS_EQUAL, TokenType::MINUS_EQUAL, TokenType::STAR_EQUAL,
                TokenType::SLASH_EQUAL, TokenType::CARET_EQUAL, TokenType::PERCENT_EQUAL}
    )) {
        Token op = previous();

        auto right = parseAssignment();

        return std::make_unique<AssignmentExpression>(std::move(left), op.type, std::move(right));
    }

    return left;
}

ExpressionPtr Parser::parseLogicalOr()
{
    return ExpressionPtr();
}

ExpressionPtr Parser::parseAdditive()
{
    auto left = parseMultiplicative();

    while(match({TokenType::PLUS, TokenType::MINUS})) {
        Token op = previous();

        auto right = parseMultiplicative();

        left = std::make_unique<BinaryExpression>(std::move(left), op.type, std::move(right));
    }

    return left;
}

ExpressionPtr Parser::parseMultiplicative()
{
    auto left = parsePower();

    while(match({TokenType::STAR, TokenType::SLASH, TokenType::PERCENT})) {
        Token op = previous();

        auto right = parsePower();

        left = std::make_unique<BinaryExpression>(std::move(left), op.type, std::move(right));
    }

    return left;
}

ExpressionPtr Parser::parsePower()
{
    return ExpressionPtr();
}
