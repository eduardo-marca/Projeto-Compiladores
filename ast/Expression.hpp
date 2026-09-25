#pragma once

#include "AST.hpp"

class Expression : public ASTNode {
  public:
    virtual ~Expression() = default;
};

using ExpressionPtr = std::unique_ptr<Expression>;
