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

void ASTTextPrinter::addIndentation() {
    result += std::string(indentLevel * 4, ' ');
}

void ASTTextPrinter::incrementIndent() {
    indentLevel++;
}

void ASTTextPrinter::decrementIndent() {
    indentLevel--;
}

std::string ASTTextPrinter::generate(const ASTNode& root) {
    root.accept(*this);
    return result;
}

void ASTTextPrinter::visit(const BinaryExpression& node) {
    addIndentation();
    result += "(";
    node.left->accept(*this);
    result += " ";
    result += to_string(node.op);
    result += " ";
    node.right->accept(*this);
    result += ")\n";
}

void ASTTextPrinter::visit(const CallExpression& node) {}
void ASTTextPrinter::visit(const CastExpression& node) {}
void ASTTextPrinter::visit(const IndexExpression& node) {}
void ASTTextPrinter::visit(const RangeExpression& node) {}
void ASTTextPrinter::visit(const UnaryExpression& node) {}
void ASTTextPrinter::visit(const AssignmentExpression& node) {}

void ASTTextPrinter::visit(const LiteralExpression& node) {
    result += node.To_String();
}

void ASTTextPrinter::visit(const IdentifierExpression& node) {}
void ASTTextPrinter::visit(const ArrayLiteral& node) {}

void ASTTextPrinter::visit(const ExpressionStatement& node) {
    node.expression->accept(*this);
}

void ASTTextPrinter::visit(const VariableDeclaration& node) {
    addIndentation();
    result += "VariableDeclaration: ";
    result += node.getName();
    if (node.getInitializer()) {
        result += " = ";
        node.getInitializer()->accept(*this);
    }
    result += "\n";
}

void ASTTextPrinter::visit(const BlockStatement& node) {}

void ASTTextPrinter::visit(const IfStatement& node) {
    addIndentation();
    result += "IfStatement:\n";
    incrementIndent();
    addIndentation();
    result += "Condition: ";
    node.getCondition()->accept(*this);
    result += "\n";
    addIndentation();
    result += "ThenBody:\n";
    incrementIndent();
    node.getThenBranch()->accept(*this);
    decrementIndent();
    if (node.getElseBranch()) {
        addIndentation();
        result += "ElseBody:\n";
        incrementIndent();
        node.getElseBranch()->accept(*this);
        decrementIndent();
    }
}

void ASTTextPrinter::visit(const WhileStatement& node) {}
void ASTTextPrinter::visit(const IteratorForStatement& node) {}
void ASTTextPrinter::visit(const TradicionalForStatement& node) {}
void ASTTextPrinter::visit(const ReturnStatement& node) {}

void ASTTextPrinter::visit(const FunctionDeclaration& node) {}

void ASTTextPrinter::visit(const Program& node) {
    for (auto& blockItem : node.items) {
        blockItem->accept(*this);
    }
}
