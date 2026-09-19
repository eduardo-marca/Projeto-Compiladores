#pragma once

#include <stdexcept>

class LexicalError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;  
};
