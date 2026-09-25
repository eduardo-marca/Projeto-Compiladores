#pragma once

#include <string>

#include "BlockStatement.hpp"
#include "ForStatement.hpp"

class IteratorForStatement : public ForStatement {
  public:
    std::string variable;
    ExpressionPtr iterable;
    BlockPtr body;

    IteratorForStatement(std::string variable, ExpressionPtr iterable, BlockPtr body)
        : variable(variable), iterable(std::move(iterable)), body(std::move(body)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        std::ostringstream oss;
        oss << "ForIn(" << variable << ", " << iterable->To_String() << ", " << std::endl
            << body->To_String() << ")";
        return oss.str();
    }
};
