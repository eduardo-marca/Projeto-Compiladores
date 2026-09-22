#pragma once

#include "AST.hpp"

class BlockItem : public ASTNode {
public:
    virtual ~BlockItem() = default;
};

using BlockItemPtr = std::unique_ptr<BlockItem>;
