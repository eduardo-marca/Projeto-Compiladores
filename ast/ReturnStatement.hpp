#pragma once

#include "Statement.hpp"
#include "Expression.hpp"
#include "ASTVisitor.hpp"

class ReturnStatement : public Statement {
public:
    ExpressionPtr value;

    ReturnStatement(ExpressionPtr value) : value(std::move(value)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        std::ostringstream oss;
        oss << "Return(";
        if (value) oss << value->To_String();
        else oss << "Void";
        oss << ")";
        return oss.str();
    }
};
