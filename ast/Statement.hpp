#pragma once

#include "AST.hpp"

#include <vector>

class Statement : public ASTNode {
public:
    virtual ~Statement() = default;
};

using StatementPtr = std::unique_ptr<Statement>;
using StatementList = std::vector<std::unique_ptr<Statement>>;
using StatementListPtr = std::unique_ptr<std::vector<std::unique_ptr<Statement>>>;
