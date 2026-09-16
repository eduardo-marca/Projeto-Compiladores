#pragma once

#include "Statement.hpp"
#include "Expression.hpp"
#include "Type.hpp"

#include <string>

class VariableDeclaration : public Statement {
    Type type;
    std::string name;
    ExpressionPtr initializer;

public:
    VariableDeclaration(Type type, std::string name, ExpressionPtr initializer)
        : type(type), name(name), initializer(move(initializer)) {}
};
