#pragma once

#include "Statement.hpp"
#include "Expression.hpp"
#include "Type.hpp"
#include "ASTVisitor.hpp"

#include <string>

class VariableDeclaration : public Statement {
    Type type;
    std::string name;
    ExpressionPtr initializer;

public:
    VariableDeclaration(Type type, std::string name, ExpressionPtr initializer)
        : type(type), name(name), initializer(move(initializer)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    Type getType() const { return type; }
    const std::string& getName() const { return name; }
    const ExpressionPtr& getInitializer() const { return initializer; }
};
