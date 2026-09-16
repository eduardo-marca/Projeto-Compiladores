#pragma once

#include "Statement.hpp"
#include "Expression.hpp"

class IfStatement : public Statement {
    ExpressionPtr condition;
    StatementPtr thenBranch;
    StatementPtr elseBranch;
public:
    IfStatement(ExpressionPtr condition, StatementPtr thenBranch, StatementPtr elseBranch)
        : condition(move(condition)), thenBranch(move(thenBranch)), elseBranch(move(elseBranch)) {}
};
