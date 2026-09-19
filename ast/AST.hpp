#pragma once

#include <memory>
#include <string>

class ASTNode {
public:
    virtual ~ASTNode() = default;

    virtual std::string To_String() const {
        return "ASTNode()";
    }
};

using ASTPtr = std::unique_ptr<ASTNode>;
