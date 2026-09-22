#pragma once

enum class Type {
    Void,
    Int,
    Float,
    Bool,
    Char,
    String,
    Undefined
};

inline std::string to_string(Type type) {
    if(type == Type::Void) return "Void";
    else if(type == Type::Int) return "Int";
    else if(type == Type::Float) return "Float";
    else if(type == Type::Bool) return "Bool";
    else if(type == Type::Char) return "Char";
    else if(type == Type::String) return "String";
    else return "Unknow";
}
