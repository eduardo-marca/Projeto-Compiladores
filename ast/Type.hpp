#pragma once

enum class PrimitiveType { Void, Int, Float, Bool, Char, String, Undefined };

inline std::string to_string(PrimitiveType type) {
    if (type == PrimitiveType::Void)
        return "Void";
    else if (type == PrimitiveType::Int)
        return "Int";
    else if (type == PrimitiveType::Float)
        return "Float";
    else if (type == PrimitiveType::Bool)
        return "Bool";
    else if (type == PrimitiveType::Char)
        return "Char";
    else if (type == PrimitiveType::String)
        return "String";
    else if (type == PrimitiveType::Undefined)
        return "Undefined";
    else
        return "Unknow";
}

class Type {
  public:
    PrimitiveType primitiveType = PrimitiveType::Undefined;
    bool isArray = false;
    size_t arraySize = 0;

    Type(PrimitiveType primitiveType = PrimitiveType::Undefined, bool isArray = false,
         size_t arraySize = 0)
        : primitiveType(primitiveType), isArray(isArray), arraySize(arraySize) {}

    std::string To_String() const {
        std::string result = to_string(primitiveType);
        if (isArray)
            result += "[]";
        return result;
    }
};
