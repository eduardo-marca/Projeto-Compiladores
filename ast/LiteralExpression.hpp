#pragma once

#include "Expression.hpp"
#include "Value.hpp"
#include "Token.hpp"

class LiteralExpression : public Expression {
    Value value;

public:
    LiteralExpression(Value value) : value(std::move(value)) {}
};
