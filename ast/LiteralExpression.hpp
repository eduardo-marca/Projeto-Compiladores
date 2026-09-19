#pragma once

#include "Expression.hpp"
#include "Value.hpp"
#include "Token.hpp"

class LiteralExpression : public Expression {
    Value value;

public:
    LiteralExpression(Value value) : value(std::move(value)) {}

    std::string To_String() const override {
        return "Literal(" + to_string(value.type) + ", " + value.lexeme + ")";
    }
};
