#pragma once

#include "ASTVisitor.hpp"
#include "Expression.hpp"
#include "Statement.hpp"

#include <sstream>

class WhileStatement : public Statement {
    ExpressionPtr condition;
    StatementPtr body;

  public:
    WhileStatement(ExpressionPtr condition, StatementPtr body)
        : condition(move(condition)), body(move(body)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    const ExpressionPtr& getCondition() const {
        return condition;
    }
    const StatementPtr& getBody() const {
        return body;
    }

    std::string To_String() const override {
        std::ostringstream oss;
        oss << "While(" << std::endl << body->To_String() << ")";
        return oss.str();
    }
};
