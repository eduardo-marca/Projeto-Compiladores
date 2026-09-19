#pragma once

#include <vector>

#include "Declaration.hpp"

using StatementList = std::vector<std::unique_ptr<Statement>>;

class Program : public ASTNode {
public:
    std::vector<std::unique_ptr<Declaration>> declarations;

    std::unique_ptr<StatementList> statements;
};

using ProgramPtr = std::unique_ptr<Program>;
