#pragma once

#include "Expression.hpp"
#include "Statement.hpp"

class ExpressionStatement : public Statement {
public:
    virtual ~ExpressionStatement() = default;

    ExpressionPtr expression;

    ExpressionStatement(ExpressionPtr expression) : expression(std::move(expression)) {}

    std::string To_String() const override {
        return "ExpressionStatement(" + expression->To_String() + ")";
    }
};
