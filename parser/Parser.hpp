#pragma once

#include <vector>
#include "Token.hpp"
#include "Statement.hpp"
#include "Expression.hpp"

class Parser {
public:
    explicit Parser(std::vector<Token> tokens);

    //Program parse();

private:
    std::vector<Token> tokens;
    size_t current = 0;

    const Token& peek() const;
    const Token& previous() const;

    bool check(TokenType type) const;
    bool match(TokenType type);
    bool match(std::vector<TokenType> types);

    const Token& expect(TokenType type);
    const Token& advance();
    const Token& consume(TokenType type);

    bool atEnd() const;

    // Grammar rules
    //Program parseProgram();

    StatementPtr parseStatement();
    StatementPtr parseBlock();
    StatementPtr parseIf();
    StatementPtr parseWhile();
    StatementPtr parseFor();
    StatementPtr parseVariableDeclaration();
    StatementPtr parseFunctionDeclaration();

    ExpressionPtr parseExpression();
    ExpressionPtr parseAssignment();
    ExpressionPtr parseLogicalOr();
    ExpressionPtr parseLogicalXor();
    ExpressionPtr parseLogicalAnd();
    ExpressionPtr parseEquality();
    ExpressionPtr parseComparison();
    ExpressionPtr parseRange();
    ExpressionPtr parseAdditive();
    ExpressionPtr parseMultiplicative();
    ExpressionPtr parsePower();
    ExpressionPtr parseCast();
    ExpressionPtr parseUnary();
    ExpressionPtr parsePostfix();
    ExpressionPtr parsePrimary();
};
