#pragma once

#include <string>

#include "Type.hpp"

struct Parameter {
    std::string name;
    Type type;

    Parameter(std::string name, Type type) : name(name), type(type) {}
};
