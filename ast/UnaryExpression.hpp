#pragma once

#include "Expression.hpp"
#include "Token.hpp"

class UnaryExpression : public Expression {
    TokenType op;
    ExpressionPtr operand;

public:
    UnaryExpression(TokenType op, ExpressionPtr operand) : op(op), operand(move(operand)) {}
};
