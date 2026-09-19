#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Lexer.hpp"
#include "Parser.hpp"

int main() {
    std::ifstream file("codes/ex6.m");

    if(!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string file_contents = buffer.str();

    Lexer lexer(file_contents);

    auto tokens = lexer.getTokens();
    //for(auto token : tokens) std::cout << token.ToString() << std::endl;

    Parser parser(tokens);

    auto program = parser.parse();

    for(auto& statement : *(program->statements)) {
        std::cout << statement->To_String() << std::endl;
    }

    return 0;
}
