#pragma once

class BinaryExpression;
class UnaryExpression;
class AssignmentExpression;
class LiteralExpression;
class IdentifierExpression;
class ExpressionStatement;
class VariableDeclaration;
class FunctionDeclaration;
class BlockStatement;
class IfStatement;
class WhileStatement;
class IteratorForStatement;
class TradicionalForStatement;
class ReturnStatement;
class Program;

class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;

    // Expressions
    virtual void visit(const BinaryExpression&) = 0;
    virtual void visit(const UnaryExpression&) = 0;
    virtual void visit(const AssignmentExpression&) = 0;
    virtual void visit(const LiteralExpression&) = 0;
    virtual void visit(const IdentifierExpression&) = 0;

    // Statements
    virtual void visit(const ExpressionStatement&) = 0;
    virtual void visit(const VariableDeclaration&) = 0;
    virtual void visit(const BlockStatement&) = 0;
    virtual void visit(const IfStatement&) = 0;
    virtual void visit(const WhileStatement&) = 0;
    virtual void visit(const IteratorForStatement&) = 0;
    virtual void visit(const TradicionalForStatement&) = 0;
    virtual void visit(const ReturnStatement&) = 0;

    // Declarations
    virtual void visit(const FunctionDeclaration&) = 0;

    // Root
    virtual void visit(const Program&) = 0;
};
