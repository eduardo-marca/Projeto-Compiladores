#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Lexer.hpp"

int main() {
    std::ifstream file("codes/ex2.m");

    if(!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // Read the entire file buffer into the stringstream
    std::string file_contents = buffer.str();

    Lexer lexer(file_contents);

    Token token = lexer.nextToken();
    while(token.type != TokenType::EndOfFile) {
        std::cout << token.ToString() << std::endl;
        token = lexer.nextToken();
    }
    std::cout << token.ToString() << std::endl;

    return 0;
}
