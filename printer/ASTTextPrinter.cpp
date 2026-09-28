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
    result += "(";
    node.left->accept(*this);
    result += " ";
    result += to_string(node.op);
    result += " ";
    node.right->accept(*this);
    result += ")";
}

void ASTTextPrinter::visit(const CallExpression& node) {
    addIndentation();
    result += "Call(";
    incrementIndent();
    addIndentation();
    result += "Callee: ";
    node.callee->accept(*this);
    result += '\n';
    addIndentation();
    result += "Args: ";
    for (int i = 0; i < node.arguments.size(); i++) {
        node.arguments[i]->accept(*this);
        if (i != node.arguments.size() - 1)
            result += ", ";
    }
    result += ")";
}

void ASTTextPrinter::visit(const CastExpression& node) {
    result += "Cast(";
    node.expression->accept(*this);
    result += " As ";
    result += to_string(node.type);
    result += ")";
}

void ASTTextPrinter::visit(const IndexExpression& node) {
    result += "Index(";
    node.expression->accept(*this);
    result += " at ";
    node.index->accept(*this);
    result += ")";
}

void ASTTextPrinter::visit(const RangeExpression& node) {
    result += "Range(";
    node.left->accept(*this);
    result += " to ";
    node.right->accept(*this);
    result += ")";
}

void ASTTextPrinter::visit(const UnaryExpression& node) {
    result += "(";
    if (node.postfix) {
        node.operand->accept(*this);
        result += " ";
        result += to_string(node.op);
    } else {
        result += to_string(node.op);
        result += " ";
        node.operand->accept(*this);
    }
    result += ")";
}

void ASTTextPrinter::visit(const AssignmentExpression& node) {
    result += "(";
    node.left->accept(*this);
    result += " " + to_string(node.op) + " ";
    node.right->accept(*this);
    result += ")";
}

void ASTTextPrinter::visit(const LiteralExpression& node) {
    result += node.To_String();
}

void ASTTextPrinter::visit(const IdentifierExpression& node) {
    result += node.name;
}

void ASTTextPrinter::visit(const ArrayLiteral& node) {
    result += "[";
    for (int i = 0; i < node.elements.size(); i++) {
        node.elements[i]->accept(*this);
        if (i != node.elements.size() - 1)
            result += ", ";
    }
    result += "]";
}

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

void ASTTextPrinter::visit(const BlockStatement& node) {
    for (auto& blockItem : node.items) {
        addIndentation();
        blockItem->accept(*this);
        result += '\n';
    }
}

void ASTTextPrinter::visit(const IfStatement& node) {
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
    decrementIndent();
}

void ASTTextPrinter::visit(const WhileStatement& node) {
    addIndentation();
    result += "WhileStatement:\n";
    incrementIndent();
    addIndentation();
    result += "Condition: ";
    node.getCondition()->accept(*this);
    result += "\n";
    addIndentation();
    result += "Body:      ";
    node.getBody()->accept(*this);
    result += "\n";
    decrementIndent();
}

void ASTTextPrinter::visit(const IteratorForStatement& node) {
    addIndentation();
    result += "For " + node.variable + " in ";
    node.iterable->accept(*this);
    result += ":\n";
    incrementIndent();
    node.body->accept(*this);
    decrementIndent();
}

void ASTTextPrinter::visit(const TradicionalForStatement& node) {}

void ASTTextPrinter::visit(const ReturnStatement& node) {}

void ASTTextPrinter::visit(const FunctionDeclaration& node) {}

void ASTTextPrinter::visit(const Program& node) {
    for (auto& blockItem : node.items) {
        blockItem->accept(*this);
    }
}
