#pragma once

#include "Expression.hpp"
#include "Statement.hpp"

class ExpressionStatement : public Statement {
public:
    virtual ~ExpressionStatement() = default;

    ExpressionPtr expression;

    ExpressionStatement(ExpressionPtr expression) : expression(std::move(expression)) {}
};
