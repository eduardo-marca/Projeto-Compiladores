#pragma once

#include "Expression.hpp"
#include "ASTVisitor.hpp"

#include <string>

class IdentifierExpression : public Expression {
public:
    std::string name;

    IdentifierExpression(std::string name) : name(name) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        return name;
    }
};
