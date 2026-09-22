#pragma once

#include "Declaration.hpp"
#include "ASTVisitor.hpp"
#include "Type.hpp"
#include "BlockStatement.hpp"
#include "Parameter.hpp"

#include <string>
#include <vector>

class FunctionDeclaration : public Declaration {
public:
    std::string name;
    std::vector<Parameter> parameters;
    Type returnType;
    BlockPtr body;

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    FunctionDeclaration(std::string name, std::vector<Parameter> parameters, Type returnType, BlockPtr body)
        : name(name), parameters(parameters), returnType(returnType), body(std::move(body)) {}
};
