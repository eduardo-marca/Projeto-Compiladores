#pragma once

#include <sstream>
#include <vector>

#include "ASTVisitor.hpp"
#include "Expression.hpp"

class ArrayLiteral : public Expression {
  public:
    std::vector<ExpressionPtr> elements;

    ArrayLiteral(std::vector<ExpressionPtr> elements) : elements(std::move(elements)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        std::ostringstream oss;
        oss << "ArrayLiteral)";
        return oss.str();
    }
};
