#pragma once

#include "Expression.hpp"

#include <string>

class IdentifierExpression : public Expression {
    std::string name;

public:
    IdentifierExpression(std::string name) : name(name) {}
};
