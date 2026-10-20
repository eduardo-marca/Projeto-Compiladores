#pragma once

#include "ASTVisitor.hpp"
#include "Expression.hpp"
#include "Statement.hpp"
#include "Type.hpp"

#include <string>

enum class Mutability { Let, Var };

inline std::string to_string(Mutability mutability) {
    return mutability == Mutability::Let ? "let" : "var";
}

class VariableDeclaration : public Declaration {
    Mutability mutability;
    Type type;
    std::string name;
    ExpressionPtr initializer;

  public:
    VariableDeclaration(Mutability mutability, Type type, std::string name,
                        ExpressionPtr initializer)
        : mutability(mutability), type(type), name(name), initializer(move(initializer)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    Type getType() const {
        return type;
    }
    Mutability getMutability() const {
        return mutability;
    }
    const std::string& getName() const {
        return name;
    }
    const ExpressionPtr& getInitializer() const {
        return initializer;
    }
};
