#pragma once

#include "AST.hpp"

class Statement : public ASTNode {
public:
    virtual ~Statement() = default;
};

using StatementPtr = std::unique_ptr<Statement>;
