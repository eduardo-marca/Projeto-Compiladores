#pragma once

#include <sstream>

#include "Statement.hpp"
#include "Expression.hpp"
#include "ASTVisitor.hpp"

class ForStatement : public Statement {
    ExpressionPtr initExpression;
    ExpressionPtr condExpression;
    ExpressionPtr incExpression;

    StatementPtr loopStatement;

public:
    ForStatement(ExpressionPtr initExpression, ExpressionPtr condExpression, ExpressionPtr incExpression, StatementPtr loopStatement)
        : initExpression(std::move(initExpression)), condExpression(std::move(condExpression)),
          incExpression(std::move(incExpression)), loopStatement(std::move(loopStatement)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    const ExpressionPtr& getInitializer() const { return initExpression; }
    const ExpressionPtr& getCondition() const { return condExpression; }
    const ExpressionPtr& getIncrement() const { return incExpression; }
    const StatementPtr& getBody() const { return loopStatement; }

    std::string To_String() const override {
        std::ostringstream oss;
        oss << "For(";
        if(initExpression) oss << initExpression->To_String();
        else oss << "empty";
        oss << "; ";
        if(condExpression) oss << condExpression->To_String();
        else oss << "empty";
        oss << "; ";
        if(incExpression) oss << incExpression->To_String();
        else oss << "empty";
        oss << std::endl << loopStatement->To_String();
        oss << ")";
        return oss.str();
    }
};
