#pragma once

#include "ForStatement.hpp"
#include "BlockStatement.hpp"

class TradicionalForStatement : public ForStatement {
public:
    ExpressionPtr initialization;
    ExpressionPtr condition;
    ExpressionPtr increment;

    BlockPtr body;

    TradicionalForStatement(ExpressionPtr initialization, ExpressionPtr condition,
        ExpressionPtr increment, BlockPtr body)
    : initialization(std::move(initialization)), condition(std::move(condition)),
        increment(std::move(increment)), body(std::move(body)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        std::ostringstream oss;
        oss << "For("
        << initialization->To_String() << ", "
        << condition->To_String() << ", "
        << increment->To_String() << ", " << std::endl
        << body->To_String() << ")";
        return oss.str();
    }
};
