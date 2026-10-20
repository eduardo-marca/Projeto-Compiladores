#include "ASTTextPrinter.hpp"

#include "ArrayLiteral.hpp"
#include "AssignmentExpression.hpp"
#include "BinaryExpression.hpp"
#include "BlockStatement.hpp"
#include "CallExpression.hpp"
#include "CastExpression.hpp"
#include "ExpressionStatement.hpp"
#include "FunctionDeclaration.hpp"
#include "IdentifierExpression.hpp"
#include "IfStatement.hpp"
#include "IndexExpression.hpp"
#include "IteratorForStatement.hpp"
#include "LiteralExpression.hpp"
#include "Program.hpp"
#include "RangeExpression.hpp"
#include "ReturnStatement.hpp"
#include "TradicionalForStatement.hpp"
#include "UnaryExpression.hpp"
#include "VariableDeclaration.hpp"
#include "WhileStatement.hpp"

void ASTTextPrinter::writeLine(std::string_view text) {
    output << std::string(indentLevel * 2, ' ') << text << '\n';
}

void ASTTextPrinter::visitNode(const ASTNode& node) {
    node.accept(*this);
}

void ASTTextPrinter::visitChild(std::string_view label, const ASTNode* child) {
    writeLine(std::string(label) + ":");
    ++indentLevel;
    if (child) {
        visitNode(*child);
    } else {
        writeLine("<none>");
    }
    indentLevel--;
}

std::string ASTTextPrinter::generate(const ASTNode& root) {
    output.str({});
    output.clear();
    indentLevel = 0;
    visitNode(root);
    return output.str();
}

void ASTTextPrinter::visit(const BinaryExpression& node) {
    writeLine("BinaryExpression (" + to_string(node.op) + ")");
    indentLevel++;
    visitChild("left", node.left.get());
    visitChild("right", node.right.get());
    indentLevel--;
}

void ASTTextPrinter::visit(const CallExpression& node) {
    writeLine("CallExpression");
    indentLevel++;
    visitChild("callee", node.callee.get());
    if (node.arguments.empty()) {
        writeLine("arguments: []");
    } else {
        writeLine("arguments:");
        ++indentLevel;
        for (std::size_t index = 0; index < node.arguments.size(); ++index) {
            visitChild("argument " + std::to_string(index), node.arguments[index].get());
        }
        indentLevel--;
    }
    indentLevel--;
}

void ASTTextPrinter::visit(const CastExpression& node) {
    writeLine("CastExpression (" + node.type.To_String() + ")");
    indentLevel++;
    visitChild("expression", node.expression.get());
    indentLevel--;
}

void ASTTextPrinter::visit(const IndexExpression& node) {
    writeLine("IndexExpression");
    indentLevel++;
    visitChild("object", node.expression.get());
    visitChild("index", node.index.get());
    indentLevel--;
}

void ASTTextPrinter::visit(const RangeExpression& node) {
    writeLine("RangeExpression");
    indentLevel++;
    visitChild("start", node.left.get());
    visitChild("end", node.right.get());
    indentLevel--;
}

void ASTTextPrinter::visit(const UnaryExpression& node) {
    const std::string position = node.postfix ? "postfix" : "prefix";
    writeLine("UnaryExpression (" + position + " " + to_string(node.op) + ")");
    indentLevel++;
    visitChild("operand", node.operand.get());
    indentLevel--;
}

void ASTTextPrinter::visit(const AssignmentExpression& node) {
    writeLine("AssignmentExpression (" + to_string(node.op) + ")");
    indentLevel++;
    visitChild("target", node.left.get());
    visitChild("value", node.right.get());
    indentLevel--;
}

void ASTTextPrinter::visit(const LiteralExpression& node) {
    writeLine("Literal: " + node.To_String());
}

void ASTTextPrinter::visit(const IdentifierExpression& node) {
    writeLine("Identifier: " + node.name);
}

void ASTTextPrinter::visit(const ArrayLiteral& node) {
    writeLine("ArrayLiteral");
    indentLevel++;
    if (node.elements.empty()) {
        writeLine("<empty>");
    } else {
        for (std::size_t index = 0; index < node.elements.size(); ++index) {
            visitChild("element " + std::to_string(index), node.elements[index].get());
        }
    }
    indentLevel--;
}

void ASTTextPrinter::visit(const ExpressionStatement& node) {
    writeLine("ExpressionStatement");
    indentLevel++;
    visitChild("expression", node.expression.get());
    indentLevel--;
}

void ASTTextPrinter::visit(const VariableDeclaration& node) {
    writeLine("VariableDeclaration (" + to_string(node.getMutability()) + ")");
    indentLevel++;
    writeLine("name: " + node.getName());
    writeLine("type: " + node.getType().To_String());
    visitChild("initializer", node.getInitializer().get());
    indentLevel--;
}

void ASTTextPrinter::visit(const BlockStatement& node) {
    writeLine("Block");
    indentLevel++;
    if (node.items.empty()) {
        writeLine("<empty>");
    } else {
        for (const auto& item : node.items) {
            if (item) {
                visitNode(*item);
            } else {
                writeLine("<none>");
            }
        }
    }
    indentLevel--;
}

void ASTTextPrinter::visit(const IfStatement& node) {
    writeLine("IfStatement");
    indentLevel++;
    visitChild("condition", node.getCondition().get());
    visitChild("then", node.getThenBranch().get());
    if (node.getElseBranch()) {
        visitChild("else", node.getElseBranch().get());
    }
    indentLevel--;
}

void ASTTextPrinter::visit(const WhileStatement& node) {
    writeLine("WhileStatement");
    indentLevel++;
    visitChild("condition", node.getCondition().get());
    visitChild("body", node.getBody().get());
    indentLevel--;
}

void ASTTextPrinter::visit(const IteratorForStatement& node) {
    writeLine("IteratorForStatement");
    indentLevel++;
    writeLine("variable: " + node.variable);
    visitChild("iterable", node.iterable.get());
    visitChild("body", node.body.get());
    indentLevel--;
}

void ASTTextPrinter::visit(const TradicionalForStatement& node) {
    writeLine("TraditionalForStatement");
    indentLevel++;
    visitChild("initializer", node.initialization.get());
    visitChild("condition", node.condition.get());
    visitChild("increment", node.increment.get());
    visitChild("body", node.body.get());
    indentLevel--;
}

void ASTTextPrinter::visit(const ReturnStatement& node) {
    writeLine("ReturnStatement");
    indentLevel++;
    visitChild("value", node.value.get());
    indentLevel--;
}

void ASTTextPrinter::visit(const FunctionDeclaration& node) {
    writeLine("FunctionDeclaration");
    indentLevel++;
    writeLine("name: " + node.name);
    writeLine("return type: " + node.returnType.To_String());
    if (node.parameters.empty()) {
        writeLine("parameters: []");
    } else {
        writeLine("parameters:");
        indentLevel++;
        for (const auto& parameter : node.parameters) {
            writeLine(parameter.name + ": " + parameter.type.To_String());
        }
        indentLevel--;
    }
    visitChild("body", node.body.get());
    indentLevel--;
}

void ASTTextPrinter::visit(const Program& node) {
    writeLine("Program");
    indentLevel++;
    if (node.items.empty()) {
        writeLine("<empty>");
    } else {
        for (const auto& item : node.items) {
            if (item) {
                visitNode(*item);
            } else {
                writeLine("<none>");
            }
        }
    }
    indentLevel--;
}
