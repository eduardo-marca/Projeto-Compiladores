#pragma once

#include <memory>

class ASTNode {
public:
    virtual ~ASTNode() = default;
};

using ASTPtr = std::unique_ptr<ASTNode>;
