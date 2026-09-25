#pragma once

#include <iostream>
#include <sstream>
#include <vector>

#include "BlockStatement.hpp"
#include "Declaration.hpp"
#include "Expression.hpp"
#include "ExpressionStatement.hpp"
#include "ParseError.hpp"
#include "Program.hpp"
#include "Statement.hpp"
#include "Token.hpp"

#include "Parameter.hpp"
#include "Type.hpp"

class Parser {
  private:
    std::vector<Token> tokens;
    size_t current = 0;

  public:
    explicit Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

    ProgramPtr parse();

  private:
    // Navegação de tokens
    const Token& peek() const;
    const Token& previous() const;

    bool isAtEnd() const;

    const Token& advance();

    bool check(TokenType type) const;
    bool checkNext(TokenType type) const;

    bool match(TokenType type);
    bool match(std::initializer_list<TokenType> types);

    const Token& consume(TokenType type, std::string_view message);

    // tratamento de erros
    ParseError error(const Token& token, std::string_view message);

    void synchronize();

    // Grammar rules
    ProgramPtr parseProgram();
    BlockItemPtr parseBlockItem();
    // std::unique_ptr<StatementList> parseStatementList();

    // declarações
    DeclarationPtr parseDeclaration();
    DeclarationPtr parseVariableDeclaration();
    DeclarationPtr parseFunctionDeclaration();

    // instruções
    StatementPtr parseStatement();
    StatementPtr parseExpressionStatement();
    StatementPtr parseIf();
    StatementPtr parseWhile();
    StatementPtr parseFor();
    StatementPtr parseIteratorFor();
    StatementPtr parseTradicionalFor();
    StatementPtr parseReturn();
    BlockPtr parseBlock();

    // expressões
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
    ExpressionPtr finishCall(ExpressionPtr callee);
    ExpressionPtr parsePrimary();
    ExpressionPtr parseArrayLiteral();

    // auxiliares
    Type parseType();
    std::vector<Parameter> parseParameterList();
    Parameter parseParameter();
};
