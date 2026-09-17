#pragma once

#include "Declaration.hpp"

#include <vector>

class Program : public ASTNode {
public:
    std::vector<std::unique_ptr<Declaration>> declarations;
};
