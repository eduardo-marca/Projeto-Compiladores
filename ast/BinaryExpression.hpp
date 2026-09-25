#pragma once

#include "ASTVisitor.hpp"
#include "Expression.hpp"
#include "TokenType.hpp"

class BinaryExpression : public Expression {
  public:
    virtual ~BinaryExpression() = default;

    ExpressionPtr left;
    TokenType op;
    ExpressionPtr right;

    BinaryExpression(ExpressionPtr left, TokenType op, ExpressionPtr right)
        : left(std::move(left)), op(op), right(std::move(right)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        return "Binary(" + left->To_String() + ", " + to_string(op) + ", " + right->To_String() +
               ")";
    }
};
