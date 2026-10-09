#pragma once

#include <sstream>

#include "ASTVisitor.hpp"
#include "BlockStatement.hpp"
#include "Expression.hpp"

class IfStatement : public Statement {
    ExpressionPtr condition;
    BlockPtr thenBranch;
    BlockPtr elseBranch;

  public:
    IfStatement(ExpressionPtr condition, BlockPtr thenBranch, BlockPtr elseBranch = nullptr)
        : condition(std::move(condition)), thenBranch(std::move(thenBranch)),
          elseBranch(std::move(elseBranch)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    const ExpressionPtr& getCondition() const {
        return condition;
    }
    const BlockPtr& getThenBranch() const {
        return thenBranch;
    }
    const BlockPtr& getElseBranch() const {
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
