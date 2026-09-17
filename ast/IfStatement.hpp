#pragma once

#include "Expression.hpp"
#include "BlockStatement.hpp"

class IfStatement : public Statement {
    ExpressionPtr condition;
    std::unique_ptr<BlockStatement> thenBranch;
    std::unique_ptr<BlockStatement> elseBranch;
public:
    IfStatement(ExpressionPtr condition, StatementPtr thenBranch, StatementPtr elseBranch)
        : condition(move(condition)), thenBranch(move(thenBranch)), elseBranch(move(elseBranch)) {}
};
