#pragma once

#include "BlockItem.hpp"

class Declaration : public BlockItem {
  public:
    virtual ~Declaration() = default;
};

using DeclarationPtr = std::unique_ptr<Declaration>;
