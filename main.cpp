#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <cstdlib>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "ASTDotPrinter.hpp"

const std::filesystem::path standard_input_file = "codes/tests.mdn";
const std::filesystem::path standard_output_file = "output/ast.dot";

struct Arguments {
    std::filesystem::path input_file;

    bool ast = false;
    bool ast_svg = false;
    bool ast_png = false;
    bool tokens = false;
    bool verbose = false;

    std::filesystem::path output;
};

void print_help() {
    std::cout <<
        "Maiden Compiler\n"
        "\n"
        "Usage:\n"
        "    maiden [options] <input>\n"
        "\n"
        "Options:\n"
        "    -h, --help             Show this help message\n"
        "    -t, --tokens           Print lexical tokens\n"
        "    -a, --ast              Print the AST and write its DOT graph\n"
        "    --ast-svg              Write the AST DOT graph (for SVG rendering)\n"
        "    --ast-png              Write the AST DOT graph (for PNG rendering)\n"
        "    --verbose              Enable verbose output\n"
        "    -o, --output <file>    Specify output file\n";
}

bool parse_arguments (int argc, char* argv[], Arguments& args) {
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            print_help();
            return false;
        }

        if (arg == "-t" || arg == "--tokens") {
            args.tokens = true;
        }
        else if (arg == "-a" || arg == "--ast") {
            args.ast = true;
        }
        else if (arg == "--ast-svg") {
            args.ast_svg = true;
        }
        else if (arg == "--ast-png") {
            args.ast_png = true;
        }
        else if (arg == "--verbose") {
            args.verbose = true;
        }
        else if (arg == "-o" || arg == "--output") {
            if (i + 1 >= argc) {
                std::cerr << "Error: " << arg << " requires an argument\n";
                return false;
            }

            args.output = argv[++i];
        }
        else if (arg[0] == '-') {
            std::cerr << "Unknown option: " << arg << '\n';
            return false;
        }
        else {
            if (!args.input_file.empty()) {
                std::cerr << "Error: multiple input files\n";
                return false;
            }

            args.input_file = arg;
        }
    }

    if (args.input_file.empty()) {
        std::cout << "no input file specified, using standard: " << standard_input_file << std::endl;
        args.input_file = standard_input_file;
    }

    if (args.output.empty()) {

        std::cout << "no output file specified, using standard: " << standard_output_file << std::endl;
        args.output = standard_output_file;
    }

    return true;
}

int main(int argc, char *argv[]) {
    Arguments args;

    if(!parse_arguments(argc, argv, args)) {
        return 1;
    }

    std::ifstream file(args.input_file);

    if(!file.is_open()) {
        std::cerr << "Failed to open the file: " << args.input_file << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string file_contents = buffer.str();

    Lexer lexer(file_contents);
    auto tokens = lexer.getTokens();

    if (args.tokens) {
        for(auto token : tokens) std::cout << token.ToString() << std::endl;
    }

    Parser parser(tokens);
    auto program = parser.parse();

    if (args.ast) {
        for(auto& statement : program->items) {
            std::cout << statement->To_String() << std::endl;
        }
    }

    ASTDotPrinter printer;

    if (args.ast_svg || args.ast_png) {
        std::ofstream file(args.output);
        if (!file.is_open()) {
            std::cerr << "Failed to open AST output file: " << args.output << std::endl;
            return 1;
        }
        printer.print(*program, file);
    }

    if(args.ast_svg) {
        std::system(
            "dot -Tsvg output/ast.dot -o output/ast.svg"
        );
    }

    if(args.ast_png) {
        std::system(
            "dot -Tsvg output/ast.dot -o output/ast.png"
        );
    }
    
    return 0;
}
