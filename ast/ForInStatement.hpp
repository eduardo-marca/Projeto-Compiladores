#pragma once

#include "Statement.hpp"
#include "Expression.hpp"
#include "ASTVisitor.hpp"

class ForInStatement : public Statement {
public:
    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }
};
