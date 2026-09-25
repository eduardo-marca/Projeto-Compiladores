#pragma once

#include <sstream>
#include <vector>

#include "ASTVisitor.hpp"
#include "Expression.hpp"

class CallExpression : public Expression {
  public:
    ExpressionPtr callee;
    std::vector<ExpressionPtr> arguments;

    CallExpression(ExpressionPtr callee, std::vector<ExpressionPtr> arguments)
        : callee(std::move(callee)), arguments(std::move(arguments)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }
};
