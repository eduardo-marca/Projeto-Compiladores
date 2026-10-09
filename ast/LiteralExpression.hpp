#pragma once

#include "ASTVisitor.hpp"
#include "Expression.hpp"
#include "Token.hpp"
#include "Value.hpp"

class LiteralExpression : public Expression {
  public:
    Value value;
    LiteralExpression(Value value) : value(std::move(value)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        std::string result = value.type.To_String() + " : ";
        if (value.type.primitiveType == PrimitiveType::Char)
            result += '\'';
        else if (value.type.primitiveType == PrimitiveType::String)
            result += '\"';
        result += value.lexeme;
        if (value.type.primitiveType == PrimitiveType::Char)
            result += '\'';
        else if (value.type.primitiveType == PrimitiveType::String)
            result += '\"';
        return result;
    }
};
