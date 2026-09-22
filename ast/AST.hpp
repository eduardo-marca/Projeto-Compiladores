#pragma once

#include <memory>
#include <string>

class ASTVisitor;

class ASTNode {
public:
    virtual ~ASTNode() = default;

    virtual void accept(ASTVisitor& visitor) const = 0;

    virtual std::string To_String() const {
        return "ASTNode()";
    }
};

using ASTPtr = std::unique_ptr<ASTNode>;
