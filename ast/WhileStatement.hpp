#pragma once

#include "Statement.hpp"
#include "Expression.hpp"

class WhileStatement : public Statement {
    ExpressionPtr condition;
    StatementPtr body;

public:
    WhileStatement(ExpressionPtr condition, StatementPtr body)
        : condition(move(condition)), body(move(body)) {}
};
