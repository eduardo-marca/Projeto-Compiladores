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

    std::unique_ptr<BlockStatement> body;

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }
};
