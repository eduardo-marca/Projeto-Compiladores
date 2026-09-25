#pragma once

#include "ASTVisitor.hpp"
#include "Statement.hpp"

#include <sstream>
#include <vector>

class BlockStatement : public Statement {
  public:
    std::vector<std::unique_ptr<BlockItem>> items;

    void add(std::unique_ptr<BlockItem> item) {
        items.push_back(std::move(item));
    }

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
