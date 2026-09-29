#pragma once

#include <string>

#include "AST.hpp"
#include "ASTVisitor.hpp"

class ASTTextPrinter final : public ASTVisitor {
  private:
    std::string result;
    int indentLevel;

    void addIndentation();
    void incrementIndent();
    void decrementIndent();

  public:
    ASTTextPrinter() : indentLevel(0) {}

    std::string generate(const ASTNode& root);

  private:
    void visitNode(const ASTNode& node);

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
    void visit(const BlockStatement& node) override;
    void visit(const IfStatement& node) override;
    void visit(const WhileStatement& node) override;
    void visit(const IteratorForStatement& node) override;
    void visit(const TradicionalForStatement& node) override;
    void visit(const ReturnStatement& node) override;

    // Declarations and root
    void visit(const FunctionDeclaration& node) override;
    void visit(const VariableDeclaration& node) override;
    void visit(const Program& node) override;
};
