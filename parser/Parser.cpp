#include "Parser.hpp"
#include "ParseError.hpp"

#include "BinaryExpression.hpp"
#include "RangeExpression.hpp"
#include "AssignmentExpression.hpp"
#include "LiteralExpression.hpp"
#include "IdentifierExpression.hpp"
#include "UnaryExpression.hpp"
#include "BlockStatement.hpp"
#include "IfStatement.hpp"
#include "WhileStatement.hpp"
#include "ForStatement.hpp"
#include "IteratorForStatement.hpp"
#include "TradicionalForStatement.hpp"
#include "ReturnStatement.hpp"
#include "VariableDeclaration.hpp"
#include "FunctionDeclaration.hpp"
#include "CastExpression.hpp"
#include "RangeExpression.hpp"
#include "IndexExpression.hpp"
#include "CallExpression.hpp"

ProgramPtr Parser::parse()
{
    return parseProgram();
}

const Token &Parser::peek() const
{
    return tokens[current];
}

const Token &Parser::previous() const
{
    return tokens[current - 1];
}

bool Parser::check(TokenType type) const
{
    if (isAtEnd())
        return type == TokenType::END_OF_FILE;

    return peek().type == type;
}

bool Parser::checkNext(TokenType type) const
{
    if (current + 1 >= tokens.size())
        return type == TokenType::END_OF_FILE;

    return tokens[current + 1].type == type;
}

bool Parser::match(TokenType type)
{
    if(!check(type))
        return false;

    advance();
    return true;
}

bool Parser::match(std::initializer_list<TokenType> types)
{
    for (TokenType type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }

    return false;
}

const Token &Parser::consume(TokenType type, std::string_view message)
{
    if (check(type))
        return advance();

    throw error(peek(), message);
}

const Token &Parser::advance()
{
    if(!isAtEnd())
        current++;

    return previous();
}

bool Parser::isAtEnd() const
{
    return peek().type == TokenType::END_OF_FILE;
}

ParseError Parser::error(const Token &token, std::string_view message)
{
    std::ostringstream oss;

    oss << "Parse error at "
    << token.line
    << ":"
    << token.column
    << ": "
    << message
    << ", found "
    << to_string(token.type);

    return ParseError(oss.str());
}

void Parser::synchronize()
{
    advance();

    while (!isAtEnd()) {
        if (previous().type == TokenType::SEMICOLON)
            return;

        switch (peek().type) {
        case TokenType::VAR:
        case TokenType::LET:
        case TokenType::IF:
        case TokenType::FOR:
        case TokenType::WHILE:
        case TokenType::RETURN:
        case TokenType::FN:
            return;

        default:
            advance();
        }
    }
}

ProgramPtr Parser::parseProgram()
{
    ProgramPtr program = std::make_unique<Program>();

    while(!isAtEnd()) {
        program->add(parseBlockItem());
    }

    return program;
}

BlockItemPtr Parser::parseBlockItem()
{
    if(check(TokenType::LET) || check(TokenType::VAR) || check(TokenType::FN)) {
        return parseDeclaration();
    }

    return parseStatement();
}

StatementPtr Parser::parseStatement()
{
    if(check(TokenType::LEFT_BRACE)) return parseBlock();
    if(check(TokenType::IF)) return parseIf();
    if(check(TokenType::WHILE)) return parseWhile();
    if(check(TokenType::FOR)) return parseFor();
    if(check(TokenType::RETURN)) return parseReturn();

    return parseExpressionStatement();
}

BlockPtr Parser::parseBlock()
{
    consume(TokenType::LEFT_BRACE, "Expected " + to_string(TokenType::LEFT_BRACE));

    auto block = std::make_unique<BlockStatement>();

    while(!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
        block->add(parseBlockItem());
    }

    consume(TokenType::RIGHT_BRACE, "Expected " + to_string(TokenType::RIGHT_BRACE));

    return block;
}

StatementPtr Parser::parseIf()
{
    consume(TokenType::IF, "Expected IF");

    ExpressionPtr condition = parseExpression();
    StatementPtr thenBranch = parseBlock();

    if(match(TokenType::ELSE)) {
        StatementPtr elseBranch = parseBlock();
        return std::make_unique<IfStatement>(std::move(condition), std::move(thenBranch)
            , std::move(elseBranch));
    }
    return std::make_unique<IfStatement>(std::move(condition), std::move(thenBranch));
}

StatementPtr Parser::parseWhile()
{
    consume(TokenType::WHILE, "Expected WHILE");

    ExpressionPtr condition = parseExpression();
    StatementPtr body = parseBlock();

    return std::make_unique<WhileStatement>(std::move(condition), std::move(body));
}

StatementPtr Parser::parseFor()
{
    consume(TokenType::FOR, "Expected FOR");

    if (check(TokenType::IDENTIFIER) && checkNext(TokenType::IN)) {
        return parseIteratorFor();
    }

    return parseTradicionalFor();
}

StatementPtr Parser::parseIteratorFor()
{
    Token variable = consume(TokenType::IDENTIFIER, "Expected iterator variable");

    consume(TokenType::IN, "Expected" + to_string(TokenType::IN) + "iterator");

    auto iterable = parseExpression();

    auto body = parseBlock();

    return std::make_unique<IteratorForStatement>(
        variable.lexeme,
        std::move(iterable),
        std::move(body)
    );
}

StatementPtr Parser::parseTradicionalFor()
{
    ExpressionPtr initialization = nullptr;
    ExpressionPtr condition = nullptr;
    ExpressionPtr increment = nullptr;
    
    if(!check(TokenType::SEMICOLON)) {
        initialization = parseExpression();
    }

    consume(TokenType::SEMICOLON, "Expected SEMICOLON after for init");

    if(!check(TokenType::SEMICOLON)) {
        condition = parseExpression();
    }

    consume(TokenType::SEMICOLON, "Expected SEMICOLON after for cond");
    
    if(!check(TokenType::LEFT_BRACE)) {
        increment = parseExpression();
    }

    BlockPtr body = parseBlock();

    return std::make_unique<TradicionalForStatement>(
        std::move(initialization),
        std::move(condition),
        std::move(increment),
        std::move(body)
    );
}

StatementPtr Parser::parseReturn()
{
    ExpressionPtr value = nullptr;

    consume(TokenType::RETURN, "Exptected RETURN");

    if (!check(TokenType::SEMICOLON)) {
        value = parseExpression();
    }

    consume(
        TokenType::SEMICOLON,
        "Expected SEMICOLON after return"
    );

    return std::make_unique<ReturnStatement>(std::move(value));
}

StatementPtr Parser::parseExpressionStatement()
{
    ExpressionPtr expression = parseExpression();

    consume(TokenType::SEMICOLON, "Expected SEMICOLON after expression");

    return std::make_unique<ExpressionStatement>(std::move(expression));
}

DeclarationPtr Parser::parseDeclaration()
{
    if(check(TokenType::FN)) return parseFunctionDeclaration();
    return parseVariableDeclaration();
}

DeclarationPtr Parser::parseVariableDeclaration()
{
    Mutability mutability;

    if (match(TokenType::LET)) mutability = Mutability::Let;
    else if (match(TokenType::VAR)) mutability = Mutability::Var;
    else throw error (peek(), "Expected variable mutability");

    Type type = Type::Undefined;
    if (match(TokenType::COLON)) {
        type = parseType();
    }

    Token id = consume(TokenType::IDENTIFIER, "Expected IDENTIFIER in variable declaration");

    ExpressionPtr initializationExpression = nullptr;
    if(match(TokenType::ASSIGN)) {
        initializationExpression = parseExpression();
    }

    consume(TokenType::SEMICOLON, "Expected SEMICOLON after variable declaration");

    return std::make_unique<VariableDeclaration>(mutability, type, id.lexeme, std::move(initializationExpression));
}

DeclarationPtr Parser::parseFunctionDeclaration()
{
    consume(TokenType::FN, "Expected FN for function declaration");

    Token id = consume(TokenType::IDENTIFIER, "Expected " + to_string(TokenType::IDENTIFIER) + " for function declaration");

    consume(TokenType::LEFT_PAREN, "Expected " + to_string(TokenType::LEFT_PAREN) + " before parameter list");

    std::vector<Parameter> parameters = parseParameterList();

    consume(TokenType::RIGHT_PAREN, "Expected " + to_string(TokenType::RIGHT_PAREN) + " after parameter list");

    consume(TokenType::ARROW, "Expected " + to_string(TokenType::ARROW) + " after function declaration");

    Type returnType = parseType();

    BlockPtr body = parseBlock();

    return std::make_unique<FunctionDeclaration>(id.lexeme, parameters, returnType, std::move(body));
}

ExpressionPtr Parser::parseExpression()
{
    return parseAssignment();
}

ExpressionPtr Parser::parseAssignment()
{
    auto left = parseLogicalOr();

    if(match({TokenType::ASSIGN, TokenType::PLUS_EQUAL, TokenType::MINUS_EQUAL, TokenType::STAR_EQUAL,
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
    auto left = parseRange();

    while(match({TokenType::LEFT_ANGLE, TokenType::LEFT_ANGLE_EQUAL,
            TokenType::RIGHT_ANGLE, TokenType::RIGHT_ANGLE_EQUAL}
    )) {
        Token op = previous();

        auto right = parseRange();

        left = std::make_unique<BinaryExpression>(std::move(left), op.type, std::move(right));
    }

    return left;
}

ExpressionPtr Parser::parseRange()
{
    auto left = parseAdditive();

    if (match(TokenType::RANGE)) {
        Token op = previous();

        auto right = parseAdditive();

        return std::make_unique<RangeExpression>(std::move(left), std::move(right));
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
    auto left = parseCast();

    while(match(TokenType::CARET)) {
        Token op = previous();

        auto right = parseCast();

        left = std::make_unique<BinaryExpression>(std::move(left), op.type, std::move(right));
    }

    return left;
}

ExpressionPtr Parser::parseCast()
{
    auto expression = parseUnary();

    while (match(TokenType::AS)) {
        Type type = parseType();

        expression = std::make_unique<CastExpression>(std::move(expression), type);
    }

    return expression;
}

ExpressionPtr Parser::parseUnary()
{
    if(match({TokenType::NOT, TokenType::MINUS, TokenType::PLUS,
        TokenType::INCREMENT, TokenType::DECREMENT
    })) {
        Token op = previous();

        auto operand = parseUnary();

        return std::make_unique<UnaryExpression>(op.type, std::move(operand));
    }

    return parsePostfix();
}

ExpressionPtr Parser::parsePostfix()
{
    auto expression = parsePrimary();

    while (true) {
        if (match({TokenType::INCREMENT, TokenType::DECREMENT})) {
            expression = std::make_unique<UnaryExpression>(
                previous().type,
                std::move(expression),
                true
            );
        }
        else if(match(TokenType::LEFT_BRACKET)) {
            auto index = parseExpression();

            consume(
                TokenType::RIGHT_BRACKET,
                "Expected RIGHT_BRACKET after array index"
            );

            expression = std::make_unique<IndexExpression>(
                std::move(expression),
                std::move(index)
            );
        }
        else if (match(TokenType::LEFT_PAREN)) {
            expression = finishCall(std::move(expression));
        }
        else {
            break;
        }
    }

    return expression;
}

ExpressionPtr Parser::finishCall(ExpressionPtr callee)
{
    std::vector<ExpressionPtr> arguments;

    if (!check(TokenType::RIGHT_PAREN)) {
        do {
            arguments.push_back(parseExpression());
        }
        while (match(TokenType::COMMA));
    }

    consume(
        TokenType::RIGHT_PAREN,
        "Expected RIGHT_PAREN after arguments"
    );

    return std::make_unique<CallExpression>(
        std::move(callee),
        std::move(arguments)
    );
}

ExpressionPtr Parser::parsePrimary()
{
    if (match({
        TokenType::INT_LITERAL,
        TokenType::FLOAT_LITERAL,
        TokenType::TRUE_LITERAL,
        TokenType::FALSE_LITERAL,
        TokenType::CHAR_LITERAL,
        TokenType::STRING_LITERAL
    })) {
        return std::make_unique<LiteralExpression>(previous().value);
    }

    if(match(TokenType::IDENTIFIER)) {
        auto id = previous();
        return std::make_unique<IdentifierExpression>(id.lexeme);
    }

    if (match(TokenType::LEFT_PAREN)) {
        auto expr = parseExpression();

        consume(TokenType::RIGHT_PAREN, "Expected right parentese");
        
        return expr;
    }

    if (match(TokenType::LEFT_BRACKET)) {
        //return parseArrayLiteral();
    }

    throw error(peek(), "Expected primary");
}

// ExpressionPtr Parser::parseArrayLiteral()
// {
//     std::vector<ExpressionPtr> elements;
// 
//     if (!check(TokenType::RIGHT_BRACKET)) {
//         do {
//             elements.push_back(parseExpression());
//         }
//         while (match(TokenType::COMMA));
//     }
// 
//     consume(
//         TokenType::RIGHT_BRACKET,
//         "Expected RIGHT_BRACKET after array literal"
//     );
// 
//     return std::make_unique<ArrayLiteral>(
//         std::move(elements)
//     );
// }

Type Parser::parseType()
{
    if (match(TokenType::INT_TYPE))
        return Type::Int;
    
    if (match(TokenType::FLOAT_TYPE))
        return Type::Float;

    if (match(TokenType::BOOL_TYPE))
        return Type::Bool;

    if (match(TokenType::CHAR_TYPE))
        return Type::Char;

    if (match(TokenType::STRING_TYPE))
        return Type::String;

    if (match(TokenType::VOID_TYPE))
        return Type::Void;

    throw error(peek(), "Expected type");
}

std::vector<Parameter> Parser::parseParameterList()
{
    std::vector<Parameter> parameters;

    if(check(TokenType::IDENTIFIER)) {
        parameters.push_back(parseParameter());

        while(match(TokenType::COMMA)) {
            parameters.push_back(parseParameter());
        }
    }

    return parameters;
}

Parameter Parser::parseParameter()
{
    Token id = consume(TokenType::IDENTIFIER, "Expected " + to_string(TokenType::IDENTIFIER) + "for parameter");

    consume(TokenType::COLON, "Expected " + to_string(TokenType::COLON) + "for parameter");

    Type type = parseType();

    return Parameter(id.lexeme, type);
}
