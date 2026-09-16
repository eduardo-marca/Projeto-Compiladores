#pragma once

#include "Expression.hpp"
#include "TokenType.hpp"

class BinaryExpression : public Expression {
    ExpressionPtr left;
    TokenType op;
    ExpressionPtr right;

public:
    BinaryExpression(ExpressionPtr left, TokenType op, ExpressionPtr right)
        : left(move(left)), op(op), right(move(right)) {}
};
