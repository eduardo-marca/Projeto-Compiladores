#pragma once

#include <optional>

struct Type {
    enum class Kind {
        Int,
        Float,
        Bool,
        Char,
        String,
        Void,
        Array
    };

    Kind kind;
    std::optional<std::size_t> arraySize;

    Type(Kind kind, std::optional<std::size_t> arraySize = std::nullopt)
        : kind(kind), arraySize(arraySize) {}
};
