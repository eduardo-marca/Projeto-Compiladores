#pragma once

#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>

#include "AST.hpp"
#include "ASTVisitor.hpp"

class ASTDotPrinter final : public ASTVisitor {
  public:
    std::string generate(const ASTNode& root);
    void print(const ASTNode& root, std::ostream& out);

  private:
    using NodeId = int;

    NodeId nextId = 0;
    std::ostringstream output;
    std::unordered_map<const ASTNode*, NodeId> nodeIds;

    NodeId visitNode(const ASTNode& node);
    NodeId createNode(const ASTNode& node, std::string_view label, std::string_view fillColor);
    void createEdge(NodeId from, NodeId to, std::string_view role = {});

    std::string escape(std::string_view text) const;

    // Expressions
    void visit(const BinaryExpression& node) override;
    void visit(const CallExpression& node) override;
    void visit(const CastExpression& node) override;
    void visit(const IndexExpression& node) override;
    void visit(const RangeExpression& node) override;
    void visit(const UnaryExpression& node) override;
    void visit(const AssignmentExpression& node) override;
    void visit(const LiteralExpression& node) override;
    void visit(const IdentifierExpression& node) override;
    void visit(const ArrayLiteral& node) override;

    // Statements
    void visit(const ExpressionStatement& node) override;
    void visit(const VariableDeclaration& node) override;
    void visit(const BlockStatement& node) override;
    void visit(const IfStatement& node) override;
    void visit(const WhileStatement& node) override;
    void visit(const IteratorForStatement& node) override;
    void visit(const TradicionalForStatement& node) override;
    void visit(const ReturnStatement& node) override;

    // Declarations and root
    void visit(const FunctionDeclaration& node) override;
    void visit(const Program& node) override;
};
