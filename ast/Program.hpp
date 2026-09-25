#pragma once

#include <vector>

#include "ASTVisitor.hpp"
#include "Declaration.hpp"
#include "Statement.hpp"

class Program : public ASTNode {
  public:
    std::vector<std::unique_ptr<BlockItem>> items;

    void add(std::unique_ptr<BlockItem> item) {
        items.push_back(std::move(item));
    }

    // std::vector<std::unique_ptr<Declaration>> declarations;

    // std::unique_ptr<StatementList> statements;

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }
};

using ProgramPtr = std::unique_ptr<Program>;
