#pragma once

#include "BlockItem.hpp"

#include <vector>

class Statement : public BlockItem {
public:
    virtual ~Statement() = default;
};

using StatementPtr = std::unique_ptr<Statement>;
using StatementList = std::vector<std::unique_ptr<Statement>>;
using StatementListPtr = std::unique_ptr<std::vector<std::unique_ptr<Statement>>>;
