#include "Parser.hpp"
#include "ParseError.hpp"

#include "BinaryExpression.hpp"
#include "AssignmentExpression.hpp"
#include "LiteralExpression.hpp"
#include "IdentifierExpression.hpp"

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
    auto left = parseLogicalXor();

    while(match(TokenType::OR)) {
        Token op = previous();

        auto right = parseLogicalXor();

        left = std::make_unique<BinaryExpression>(std::move(left), op.type, std::move(right));
    }

    return left;
}

ExpressionPtr Parser::parseLogicalXor()
{
    auto left = parseLogicalAnd();

    while(match(TokenType::XOR)) {
        Token op = previous();

        auto right = parseLogicalAnd();

        left = std::make_unique<BinaryExpression>(std::move(left), op.type, std::move(right));
    }

    return left;
}

ExpressionPtr Parser::parseLogicalAnd()
{
    auto left = parseEquality();

    while(match(TokenType::AND)) {
        Token op = previous();

        auto right = parseEquality();

        left = std::make_unique<BinaryExpression>(std::move(left), op.type, std::move(right));
    }

    return left;
}

ExpressionPtr Parser::parseEquality()
{
    auto left = parseComparison();

    while(match({TokenType::EQUAL, TokenType::EXCLAMATION_EQUAL})) {
        Token op = previous();

        auto right = parseComparison();

        left = std::make_unique<BinaryExpression>(std::move(left), op.type, std::move(right));
    }

    return left;
}

ExpressionPtr Parser::parseComparison()
{
    auto left = parseAdditive();

    while(match({TokenType::LEFT_ANGLE, TokenType::LEFT_ANGLE_EQUAL,
            TokenType::RIGHT_ANGLE, TokenType::RIGHT_ANGLE_EQUAL}
    )) {
        Token op = previous();

        auto right = parseAdditive();

        left = std::make_unique<BinaryExpression>(std::move(left), op.type, std::move(right));
    }

    return left;
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
    auto left = parseUnary();

    while(match(TokenType::CARET)) {
        Token op = previous();

        auto right = parseUnary();

        left = std::make_unique<BinaryExpression>(std::move(left), op.type, std::move(right));
    }

    return left;
}

ExpressionPtr Parser::parseUnary()
{
    auto left = parsePrimary();

    while(match({TokenType::NOT, TokenType::MINUS, TokenType::PLUS})) {
        Token op = previous();

        auto right = parsePrimary();

        left = std::make_unique<BinaryExpression>(std::move(left), op.type, std::move(right));
    }

    return left;
}

ExpressionPtr Parser::parsePrimary()
{
    if(match({TokenType::INT_LITERAL, TokenType::FLOAT_LITERAL, TokenType::TRUE_LITERAL,
            TokenType::FALSE_LITERAL, TokenType::CHAR_LITERAL, TokenType::STRING_LITERAL}
    )) {
        Token token = previous();

        return std::make_unique<LiteralExpression>(token);
    }

    if(match(TokenType::LEFT_PAREN)) {
        auto expr = parseExpression();
        if(match(TokenType::RIGHT_PAREN)) {
            return expr;
        }
    }

    if(match(TokenType::IDENTIFIER)) {
        auto id = previous();
        return std::make_unique<IdentifierExpression>(id.lexeme);
    }
}
