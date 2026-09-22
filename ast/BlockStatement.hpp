#pragma once

#include "Statement.hpp"
#include "ASTVisitor.hpp"

#include <vector>
#include <sstream>

class BlockStatement : public Statement {
public:
    StatementListPtr statements;

    BlockStatement(StatementListPtr statements) : statements(std::move(statements)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        std::ostringstream oss;
        oss << "Block(" << std::endl;
        for(auto& statement : *statements) {
            oss << '\t' << statement->To_String() << std::endl;
        }
        oss << ")";
        return oss.str();
    }
};

using BlockPtr = std::unique_ptr<BlockStatement>;
