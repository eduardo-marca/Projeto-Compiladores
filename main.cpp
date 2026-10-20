#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

#include "ASTDotPrinter.hpp"
#include "ASTTextPrinter.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

const std::filesystem::path standard_input_file = "examples/tests.mdn";
const std::filesystem::path standard_output_file = "output/ast.dot";

namespace {
std::string shellQuote(std::string_view value) {
    std::string quoted = "'";
    for (const char character : value) {
        if (character == '\'') {
            quoted += "'\\''";
        } else {
            quoted += character;
        }
    }
    return quoted + "'";
}
} // namespace

struct Arguments {
    std::filesystem::path input_file;

    bool ast = false;
    bool ast_dot = false;
    bool ast_svg = false;
    bool ast_png = false;
    bool old_print = false;
    bool tokens = false;
    bool verbose = false;

    std::filesystem::path output;
};

void print_help() {
    std::cout << "Maiden Compiler\n"
                 "\n"
                 "Usage:\n"
                 "    maiden [options] <input>\n"
                 "\n"
                 "Options:\n"
                 "    -h, --help             Show this help message\n"
                 "    -t, --tokens           Print lexical tokens\n"
                 "    -a, --ast              Print the AST as indented text\n"
                 "    --ast-dot              Write the AST as a DOT graph\n"
                 "    --ast-svg              Write the AST as DOT and SVG\n"
                 "    --ast-png              Write the AST as DOT and PNG\n"
                 "    --old-print            Print the AST in the old text format\n"
                 "    --verbose              Enable verbose output\n"
                 "    -o, --output <file>    Specify output file\n";
}

bool parse_arguments(int argc, char* argv[], Arguments& args) {
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            print_help();
            return false;
        }

        if (arg == "-t" || arg == "--tokens") {
            args.tokens = true;
        } else if (arg == "-a" || arg == "--ast") {
            args.ast = true;
        } else if (arg == "--ast-dot") {
            args.ast_dot = true;
        } else if (arg == "--ast-svg") {
            args.ast_svg = true;
        } else if (arg == "--ast-png") {
            args.ast_png = true;
        } else if (arg == "--old-print") {
            args.old_print = true;
        } else if (arg == "--verbose") {
            args.verbose = true;
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 >= argc) {
                std::cerr << "Error: " << arg << " requires an argument\n";
                return false;
            }

            args.output = argv[++i];
        } else if (arg[0] == '-') {
            std::cerr << "Unknown option: " << arg << '\n';
            return false;
        } else {
            if (!args.input_file.empty()) {
                std::cerr << "Error: multiple input files\n";
                return false;
            }

            args.input_file = arg;
        }
    }

    if (args.input_file.empty()) {
        std::cout << "no input file specified, using standard: " << standard_input_file
                  << std::endl;
        args.input_file = standard_input_file;
    }

    return true;
}

int main(int argc, char* argv[]) {
    Arguments args;

    if (!parse_arguments(argc, argv, args)) {
        return 1;
    }

    std::ifstream file(args.input_file);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << args.input_file << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string file_contents = buffer.str();

    Lexer lexer(file_contents);
    auto tokens = lexer.getTokens();

    if (args.tokens) {
        for (auto token : tokens)
            std::cout << token.ToString() << std::endl;
    }

    Parser parser(tokens);
    auto program = parser.parse();

    if (args.old_print) {
        for (auto& statement : program->items) {
            std::cout << statement->To_String() << std::endl;
        }
    }

    if (args.ast) {
        ASTTextPrinter printer;
        std::cout << printer.generate(*program);
    }

    if (args.ast_dot || args.ast_svg || args.ast_png) {
        ASTDotPrinter printer;
        if (args.output.empty()) {
            args.output = standard_output_file;
        }
        if (!args.output.parent_path().empty()) {
            std::error_code error;
            std::filesystem::create_directories(args.output.parent_path(), error);
            if (error) {
                std::cerr << "Failed to create AST output directory: "
                          << args.output.parent_path() << std::endl;
                return 1;
            }
        }
        std::ofstream file(args.output);

        if (!file.is_open()) {
            std::cerr << "Failed to open AST output file: " << args.output << std::endl;
            return 1;
        }
        printer.print(*program, file);
    }

    if (args.ast_svg) {
        std::filesystem::path imagePath = args.output;
        imagePath.replace_extension(".svg");
        const std::string command = "dot -Tsvg " + shellQuote(args.output.string()) + " -o " +
                                    shellQuote(imagePath.string());
        if (std::system(command.c_str()) != 0) {
            std::cerr << "Failed to render AST SVG with Graphviz.\n";
            return 1;
        }
    }

    if (args.ast_png) {
        std::filesystem::path imagePath = args.output;
        imagePath.replace_extension(".png");
        const std::string command = "dot -Tpng " + shellQuote(args.output.string()) + " -o " +
                                    shellQuote(imagePath.string());
        if (std::system(command.c_str()) != 0) {
            std::cerr << "Failed to render AST PNG with Graphviz.\n";
            return 1;
        }
    }

    return 0;
}
