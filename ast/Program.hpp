#pragma once

#include <vector>

#include "ASTVisitor.hpp"
#include "Declaration.hpp"
#include "Statement.hpp"

class Program : public ASTNode {
  public:
    std::vector<std::unique_ptr<BlockItem>> items;

    Program(std::vector<std::unique_ptr<BlockItem>> items) : items(std::move(items)) {}

    void accept(ASTVisitor& visitor) const override {
        visitor.visit(*this);
    }
};

using ProgramPtr = std::unique_ptr<Program>;
