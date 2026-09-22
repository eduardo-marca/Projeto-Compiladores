#pragma once

#include "Expression.hpp"
#include "ASTVisitor.hpp"
#include "Value.hpp"
#include "Token.hpp"

class LiteralExpression : public Expression {
public:
    Value value;
    LiteralExpression(Value value) : value(std::move(value)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        return "Literal(" + to_string(value.type) + ", " + value.lexeme + ")";
    }
};
