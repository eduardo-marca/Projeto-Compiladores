#pragma once

#include <sstream>

#include "ASTVisitor.hpp"
#include "Expression.hpp"

class RangeExpression : public Expression {
  public:
    ExpressionPtr left;
    ExpressionPtr right;

    RangeExpression(ExpressionPtr left, ExpressionPtr right)
        : left(std::move(left)), right(std::move(right)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        std::ostringstream oss;
        oss << "Range(" << left->To_String() << ", " << right->To_String() << ")";
        return oss.str();
    }
};
