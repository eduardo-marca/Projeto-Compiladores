#pragma once

#include "Expression.hpp"
#include "ASTVisitor.hpp"
#include "Token.hpp"

class UnaryExpression : public Expression {
public:
    TokenType op;
    ExpressionPtr operand;
    bool postfix;

    UnaryExpression(TokenType op, ExpressionPtr operand, bool postfix = false)
        : op(op), operand(move(operand)), postfix(postfix) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        return "Unary(" + to_string(op) + ", " + operand->To_String() + ")";
    }
};
