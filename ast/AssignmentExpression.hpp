#pragma once

#include "Expression.hpp"
#include "TokenType.hpp"

class AssignmentExpression : public Expression {
public:
    ExpressionPtr left;
    TokenType op;
    ExpressionPtr right;

    AssignmentExpression(ExpressionPtr left, TokenType op, ExpressionPtr right)
        : left(std::move(left)), op(op), right(std::move(right)) {}
};
