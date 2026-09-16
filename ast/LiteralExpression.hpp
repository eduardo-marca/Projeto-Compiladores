#pragma once

#include "Expression.hpp"
#include "Value.hpp"

class LiteralExpression : public Expression {
    Value value;

public:
    LiteralExpression(Value value) : value(value) {}
};
