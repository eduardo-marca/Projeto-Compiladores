#pragma once

#include "ASTVisitor.hpp"
#include "Expression.hpp"
#include "Token.hpp"
#include "Value.hpp"

class LiteralExpression : public Expression {
  public:
    Value value;
    LiteralExpression(Value value) : value(std::move(value)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        return "(" + to_string(value.type) + ", " + value.lexeme + ")";
    }
};
