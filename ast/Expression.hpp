#pragma once

#include <memory>
#include "AST.hpp"

using ExpressionPtr = std::unique_ptr<Expression>;

class Expression : public ASTNode {

};
