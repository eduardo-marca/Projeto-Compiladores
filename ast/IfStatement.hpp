#pragma once

#include <sstream>

#include "ASTVisitor.hpp"
#include "BlockStatement.hpp"
#include "Expression.hpp"

class IfStatement : public Statement {
    ExpressionPtr condition;
    StatementPtr thenBranch;
    StatementPtr elseBranch;

  public:
    IfStatement(ExpressionPtr condition, StatementPtr thenBranch, StatementPtr elseBranch = nullptr)
        : condition(std::move(condition)), thenBranch(std::move(thenBranch)),
          elseBranch(std::move(elseBranch)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    const ExpressionPtr& getCondition() const {
        return condition;
    }
    const StatementPtr& getThenBranch() const {
        return thenBranch;
    }
    const StatementPtr& getElseBranch() const {
        return elseBranch;
    }

    std::string To_String() const override {
        std::ostringstream oss;
        oss << "If(" << condition->To_String() << std::endl << thenBranch->To_String();
        if (elseBranch) {
            oss << std::endl << "Else(" << std::endl << elseBranch->To_String() << ")";
        }
        oss << ")";
        return oss.str();
    }
};
