#pragma once

#include "Expression.hpp"
#include "Statement.hpp"
#include "ASTVisitor.hpp"

class ExpressionStatement : public Statement {
public:
    virtual ~ExpressionStatement() = default;

    ExpressionPtr expression;

    ExpressionStatement(ExpressionPtr expression) : expression(std::move(expression)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        return "Expression(" + expression->To_String() + ")";
    }
};
