#pragma once

#include <sstream>

#include "ASTVisitor.hpp"
#include "Expression.hpp"
#include "Type.hpp"

class CastExpression : public Expression {
  public:
    ExpressionPtr expression;
    Type type;

    CastExpression(ExpressionPtr expression, Type type)
        : expression(std::move(expression)), type(type) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        std::ostringstream oss;
        oss << "Cast(" << expression->To_String() << ", " << to_string(type) << ")";
        return oss.str();
    }
};
