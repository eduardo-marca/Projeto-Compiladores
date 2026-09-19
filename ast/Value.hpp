#pragma once

#include <variant>
#include <string>
#include <cstdint>

using Value = std::variant<
    std::monostate,
    std::int64_t,
    double,
    bool,
    char,
    std::string
>;
