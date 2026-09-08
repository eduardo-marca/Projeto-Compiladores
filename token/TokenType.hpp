#pragma once

#include <string>

enum class TokenType {
    // Id and instructions
    Identifier,
    If,
    Else,
    While,
    For,
    Fn,
    Return,
    Var,
    Let,
    In,
    Not,
    Or,
    And,
    Xor,
    As,
    Comment,

    // Literals
    IntLiteral,
    FloatLiteral,
    TrueLiteral, // true
    FalseLiteral, // false
    CharLiteral,
    StringLiteral,

    // Types
    IntType, // Int
    FloatType, // Float
    BoolType, // Bool
    CharType, // Char
    StringType, // String
    VoidType, // Void

    // Arithmetic operators
    Plus, // +
    Minus, // - 
    Star, // *
    Slash, // /
    Caret, // ^
    Modulo, // %
    PlusAssign, // +=
    MinusAssign, // - =
    StarAssign, // *=
    SlashAssign, // /=
    CaretAssign, // ^=
    PercentAssign, // %=
    Increment, // ++
    Decrement, // --

    // Relational operators
    Equal, // ==
    Less, // <
    Greater, // >
    LessEqual, // <=
    GreaterEqual, // >=
    NotEqual, // !=
    
    // Unique tokens
    UniqueToken,
    Assign, // =
    Quote, // "
    Comma, // ,
    Point, // .
    Range, // ..
    Semicolon, // ;
    Colon, // :
    Question, // ?
    Apostrophe, // '
    Arrow, // ->

    LParen,
    RParen,
    LBracket,
    RBracket,
    LCurly,
    RCurly,

    EndOfFile,

    Unknown
};

inline std::string to_string(TokenType tokenType) {
    switch (tokenType) {
        case TokenType::Identifier: return "Identifier";
        case TokenType::If: return "If";
        case TokenType::Else: return "Else";
        case TokenType::While: return "While";
        case TokenType::For: return "For";
        case TokenType::Fn: return "Fn";
        case TokenType::Return: return "Return";
        case TokenType::Var: return "Var";
        case TokenType::Let: return "Let";
        case TokenType::In: return "In";
        case TokenType::Not: return "Not";
        case TokenType::Or: return "Or";
        case TokenType::And: return "And";
        case TokenType::Xor: return "Xor";
        case TokenType::As: return "As";
        case TokenType::Comment: return "Comment";
        case TokenType::IntLiteral: return "IntLiteral";
        case TokenType::FloatLiteral: return "FloatLiteral";
        case TokenType::TrueLiteral: return "TrueLiteral";
        case TokenType::FalseLiteral: return "FalseLiteral";
        case TokenType::CharLiteral: return "CharLiteral";
        case TokenType::StringLiteral: return "StringLiteral";
        case TokenType::IntType: return "IntType";
        case TokenType::FloatType: return "FloatType";
        case TokenType::BoolType: return "BoolType";
        case TokenType::CharType: return "CharType";
        case TokenType::StringType: return "StringType";
        case TokenType::VoidType: return "VoidType";
        case TokenType::Plus: return "Plus";
        case TokenType::Minus: return "Minus";
        case TokenType::Star: return "Star";
        case TokenType::Slash: return "Slash";
        case TokenType::Caret: return "Caret";
        case TokenType::Modulo: return "Modulo";
        case TokenType::PlusAssign: return "PlusAssign";
        case TokenType::MinusAssign: return "MinusAssign";
        case TokenType::StarAssign: return "StarAssign";
        case TokenType::SlashAssign: return "SlashAssign";
        case TokenType::CaretAssign: return "CaretAssign";
        case TokenType::PercentAssign: return "PercentAssign";
        case TokenType::Increment: return "Increment";
        case TokenType::Decrement: return "Decrement";
        case TokenType::Equal: return "Equal";
        case TokenType::Less: return "Less";
        case TokenType::Greater: return "Greater";
        case TokenType::LessEqual: return "LessEqual";
        case TokenType::GreaterEqual: return "GreaterEqual";
        case TokenType::NotEqual: return "NotEqual";
        case TokenType::UniqueToken: return "UniqueToken";
        case TokenType::Assign: return "Assign";
        case TokenType::Quote: return "Quote";
        case TokenType::Comma: return "Comma";
        case TokenType::Point: return "Point";
        case TokenType::Range: return "Range";
        case TokenType::Semicolon: return "Semicolon";
        case TokenType::Colon: return "Colon";
        case TokenType::Question: return "Question";
        case TokenType::Apostrophe: return "Apostrophe";
        case TokenType::Arrow: return "Arrow";
        case TokenType::LParen: return "LParen";
        case TokenType::RParen: return "RParen";
        case TokenType::LBracket: return "LBracket";
        case TokenType::RBracket: return "RBracket";
        case TokenType::LCurly: return "LCurly";
        case TokenType::RCurly: return "RCurly";
        case TokenType::Unknown: return "Unknown";
        case TokenType::EndOfFile: return "EndOfFile";
        default: return "Unknown";
    }
}
