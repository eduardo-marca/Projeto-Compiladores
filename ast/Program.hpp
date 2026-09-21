#pragma once

#include <vector>

#include "Declaration.hpp"
#include "Statement.hpp"

class Program : public ASTNode {
public:
    std::vector<std::unique_ptr<Declaration>> declarations;

    std::unique_ptr<StatementList> statements;
};

using ProgramPtr = std::unique_ptr<Program>;
