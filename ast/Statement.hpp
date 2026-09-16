#pragma once

#include <memory>
#include "AST.hpp"

using StatementPtr = std::unique_ptr<Statement>;

class Statement : public ASTNode {

};
