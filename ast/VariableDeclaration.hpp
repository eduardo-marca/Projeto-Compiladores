#pragma once

#include "Statement.hpp"
#include "Expression.hpp"
#include "Type.hpp"
#include "ASTVisitor.hpp"

#include <string>

enum class Mutability {
    Let,
    Var
};

class VariableDeclaration : public Declaration {
    Mutability mutability;
    Type type;
    std::string name;
    ExpressionPtr initializer;

public:
    VariableDeclaration(Mutability mutability, Type type, std::string name, ExpressionPtr initializer)
        : mutability(mutability), type(type), name(name), initializer(move(initializer)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    Type getType() const { return type; }
    const std::string& getName() const { return name; }
    const ExpressionPtr& getInitializer() const { return initializer; }
};
