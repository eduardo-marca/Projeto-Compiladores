#pragma once

#include "Statement.hpp"

#include <vector>

class BlockStatement : public Statement {
public:
    std::vector<StatementPtr> statements;
};
