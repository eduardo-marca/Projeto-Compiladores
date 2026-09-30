#pragma once

#include <cstdint>
#include <string>
#include <variant>

#include "Type.hpp"

class Value {
  public:
    Type type;
    std::string lexeme;
    std::variant<std::monostate, std::int64_t, double, bool, char, std::string> val;

    std::string To_String() const {
        return "Value(" + type.To_String() + ", " + lexeme + ")";
    }
};
