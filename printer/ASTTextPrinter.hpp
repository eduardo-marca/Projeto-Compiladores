#pragma once

#include <cstddef>
#include <sstream>
#include <string>
#include <string_view>

#include "AST.hpp"
#include "ASTVisitor.hpp"

class ASTTextPrinter final : public ASTVisitor {
  public:
    std::string generate(const ASTNode& root);

  private:
    std::ostringstream output;
    std::size_t indentLevel = 0;

    void writeLine(std::string_view text);
    void visitNode(const ASTNode& node);
    void visitChild(std::string_view label, const ASTNode* child);

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
