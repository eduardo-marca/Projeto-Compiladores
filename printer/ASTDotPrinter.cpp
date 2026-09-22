#include "ASTDotPrinter.hpp"

#include <stdexcept>

#include "AssignmentExpression.hpp"
#include "BinaryExpression.hpp"
#include "BlockStatement.hpp"
#include "ExpressionStatement.hpp"
#include "IteratorForStatement.hpp"
#include "TradicionalForStatement.hpp"
#include "ReturnStatement.hpp"
#include "FunctionDeclaration.hpp"
#include "IdentifierExpression.hpp"
#include "IfStatement.hpp"
#include "LiteralExpression.hpp"
#include "Program.hpp"
#include "UnaryExpression.hpp"
#include "VariableDeclaration.hpp"
#include "WhileStatement.hpp"

namespace {
constexpr std::string_view expressionColor = "#E3F2FD";
constexpr std::string_view statementColor = "#E8F5E9";
constexpr std::string_view declarationColor = "#FFF3E0";
constexpr std::string_view rootColor = "#EDE7F6";
}

std::string ASTDotPrinter::generate(const ASTNode& root)
{
    output.str({});
    output.clear();
    nodeIds.clear();
    nextId = 0;

    output << R"(digraph AST {
    graph [rankdir=TB, bgcolor="transparent", pad=0.2, nodesep=0.35, ranksep=0.5];
    node [shape=box, style="rounded,filled", color="#607D8B", fontname="Helvetica", fontsize=11, margin="0.15,0.08"];
    edge [fontname="Helvetica", fontsize=9, color="#546E7A"];

)";

    visitNode(root);
    output << "}\n";
    return output.str();
}

void ASTDotPrinter::print(const ASTNode& root, std::ostream& out)
{
    out << generate(root);
}

ASTDotPrinter::NodeId ASTDotPrinter::visitNode(const ASTNode& node)
{
    if (const auto found = nodeIds.find(&node); found != nodeIds.end()) {
        return found->second;
    }

    node.accept(*this);

    const auto created = nodeIds.find(&node);
    if (created == nodeIds.end()) {
        throw std::logic_error("AST visitor did not emit a DOT node");
    }
    return created->second;
}

ASTDotPrinter::NodeId ASTDotPrinter::createNode(const ASTNode& node,
                                                std::string_view label,
                                                std::string_view fillColor)
{
    if (const auto found = nodeIds.find(&node); found != nodeIds.end()) {
        return found->second;
    }

    const NodeId id = nextId++;
    nodeIds.emplace(&node, id); // Register before visiting children: cycle-safe.
    output << "    n" << id << " [label=\"" << escape(label)
           << "\", fillcolor=\"" << fillColor << "\"];\n";
    return id;
}

void ASTDotPrinter::createEdge(NodeId from, NodeId to, std::string_view role)
{
    output << "    n" << from << " -> n" << to;
    if (!role.empty()) {
        output << " [label=\"" << escape(role) << "\"]";
    }
    output << ";\n";
}

std::string ASTDotPrinter::escape(std::string_view text) const
{
    std::string escaped;
    escaped.reserve(text.size());
    for (const char character : text) {
        switch (character) {
        case '\\': escaped += "\\\\"; break;
        case '"': escaped += "\\\""; break;
        case '\n': escaped += "\\n"; break;
        case '\r': escaped += "\\r"; break;
        case '\t': escaped += "\\t"; break;
        default: escaped += character; break;
        }
    }
    return escaped;
}

void ASTDotPrinter::visit(const BinaryExpression& node)
{
    const NodeId id = createNode(node, "Binary expression\n" + to_string(node.op), expressionColor);
    if (node.left) createEdge(id, visitNode(*node.left), "left");
    if (node.right) createEdge(id, visitNode(*node.right), "right");
}

void ASTDotPrinter::visit(const UnaryExpression& node)
{
    const NodeId id = createNode(node, "Unary expression\n" + to_string(node.op), expressionColor);
    if (node.operand) createEdge(id, visitNode(*node.operand), "operand");
}

void ASTDotPrinter::visit(const AssignmentExpression& node)
{
    const NodeId id = createNode(node, "Assignment\n" + to_string(node.op), expressionColor);
    if (node.left) createEdge(id, visitNode(*node.left), "target");
    if (node.right) createEdge(id, visitNode(*node.right), "value");
}

void ASTDotPrinter::visit(const LiteralExpression& node)
{
    createNode(node, "Literal\n" + to_string(node.value.type) + ": " + node.value.lexeme,
               expressionColor);
}

void ASTDotPrinter::visit(const IdentifierExpression& node)
{
    createNode(node, "Identifier\n" + node.name, expressionColor);
}

void ASTDotPrinter::visit(const ExpressionStatement& node)
{
    const NodeId id = createNode(node, "Expression statement", statementColor);
    if (node.expression) createEdge(id, visitNode(*node.expression), "expression");
}

void ASTDotPrinter::visit(const VariableDeclaration& node)
{
    const NodeId id = createNode(node, "Variable declaration\n" + to_string(node.getType()) + " " + node.getName(),
                                 statementColor);
    if (node.getInitializer()) createEdge(id, visitNode(*node.getInitializer()), "initializer");
}

void ASTDotPrinter::visit(const BlockStatement& node)
{
    const NodeId id = createNode(node, "Block", statementColor);
    for (const auto& statement : node.items) {
        if (statement) createEdge(id, visitNode(*statement), "statement");
    }
}

void ASTDotPrinter::visit(const IfStatement& node)
{
    const NodeId id = createNode(node, "If", statementColor);
    if (node.getCondition()) createEdge(id, visitNode(*node.getCondition()), "condition");
    if (node.getThenBranch()) createEdge(id, visitNode(*node.getThenBranch()), "then");
    if (node.getElseBranch()) createEdge(id, visitNode(*node.getElseBranch()), "else");
}

void ASTDotPrinter::visit(const WhileStatement& node)
{
    const NodeId id = createNode(node, "While", statementColor);
    if (node.getCondition()) createEdge(id, visitNode(*node.getCondition()), "condition");
    if (node.getBody()) createEdge(id, visitNode(*node.getBody()), "body");
}

void ASTDotPrinter::visit(const IteratorForStatement& node)
{
    createNode(node, "For-in", statementColor);
}

void ASTDotPrinter::visit(const TradicionalForStatement& node)
{
    createNode(node, "For", statementColor);
}

void ASTDotPrinter::visit(const ReturnStatement& node)
{
    createNode(node, "Return", statementColor);
}

void ASTDotPrinter::visit(const FunctionDeclaration& node)
{
    const NodeId id = createNode(node, "Function declaration\n" + node.name + " -> " + to_string(node.returnType),
                                 declarationColor);
    if (node.body) createEdge(id, visitNode(*node.body), "body");
}

void ASTDotPrinter::visit(const Program& node)
{
    const NodeId id = createNode(node, "Program", rootColor);
    for (const auto& statement : node.items) {
        if (statement) createEdge(id, visitNode(*statement), "item");
    }
}
