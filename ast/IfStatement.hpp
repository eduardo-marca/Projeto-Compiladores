#pragma once

#include <sstream>

#include "Expression.hpp"
#include "BlockStatement.hpp"

class IfStatement : public Statement {
    ExpressionPtr condition;
    StatementPtr thenBranch;
    StatementPtr elseBranch;
public:
    IfStatement(ExpressionPtr condition, StatementPtr thenBranch, StatementPtr elseBranch = nullptr)
        : condition(std::move(condition)), thenBranch(std::move(thenBranch)),
          elseBranch(std::move(elseBranch)) {}

    std::string To_String() const override {
        std::ostringstream oss;
        oss << "If("
        << condition->To_String() << std::endl
        << thenBranch->To_String();
        if(elseBranch) {
            oss << std::endl
            << "Else(" << std::endl
            << elseBranch->To_String()
            << ")";
        }
        oss << ")";
        return oss.str();
    }
};
