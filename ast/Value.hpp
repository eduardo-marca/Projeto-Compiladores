#pragma once

#include <string>
#include "Type.hpp"

class Value {
public:
    Type type;
    std::string val;

    Value(Type type, std::string val) : type(type), val(val) {}
};
