#pragma once

#include <sstream>

#include "ASTVisitor.hpp"
#include "Expression.hpp"

class IndexExpression : public Expression {
  public:
    ExpressionPtr expression;
    ExpressionPtr index;

    IndexExpression(ExpressionPtr expression, ExpressionPtr index)
        : expression(std::move(expression)), index(std::move(index)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        std::ostringstream oss;
        oss << "Index(" << expression->To_String() << ", " << index->To_String() << ")";
        return oss.str();
    }
};
