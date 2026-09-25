#pragma once

#include "ASTVisitor.hpp"
#include "Statement.hpp"

#include <sstream>
#include <vector>

class BlockStatement : public Statement {
  public:
    std::vector<std::unique_ptr<BlockItem>> items;

    BlockStatement(std::vector<std::unique_ptr<BlockItem>> items) : items(std::move(items)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }

    std::string To_String() const override {
        std::ostringstream oss;
        oss << "Block(" << std::endl;
        for (auto& item : items) {
            oss << '\t' << item->To_String() << std::endl;
        }
        oss << ")";
        return oss.str();
    }
};

using BlockPtr = std::unique_ptr<BlockStatement>;
