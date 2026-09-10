#pragma once

#include <string>

enum class TokenType {
    // Id and keywords
    IDENTIFIER,
    IF,
    ELSE,
    WHILE,
    FOR,
    FN,
    RETURN,
    VAR,
    LET,
    AS,
    IN,
    NOT,
    OR,
    AND,
    XOR,

    // Comment
    COMMENT,

    // Literals
    INT_LITERAL,
    FLOAT_LITERAL,
    TRUE_LITERAL, // true
    FALSE_LITERAL, // false
    CHAR_LITERAL,
    STRING_LITERAL,

    // Types
    INT_TYPE, // Int
    FLOAT_TYPE, // Float
    BOOL_TYPE, // Bool
    CHAR_TYPE, // Char
    STRING_TYPE, // String
    VOID_TYPE, // Void

    // Arithmetic operators
    PLUS, // +
    MINUS, // - 
    STAR, // *
    SLASH, // /
    CARET, // ^
    PERCENT, // %
    PLUS_EQUAL, // +=
    MINUS_EQUAL, // - =
    STAR_EQUAL, // *=
    SLASH_EQUAL, // /=
    CARET_EQUAL, // ^=
    PERCENT_EQUAL, // %=
    INCREMENT, // ++
    DECREMENT, // --

    // Relational operators
    EQUAL, // ==
    LEFT_ANGLE, // <
    RIGHT_ANGLE, // >
    LEFT_ANGLE_EQUAL, // <=
    RIGHT_ANGLE_EQUAL, // >=
    EXCLAMATION_EQUAL, // !=
    
    // Unique tokens
    UNDERSCORE, // _
    ASSIGN, // =
    QUOTE, // "
    COMMA, // ,
    POINT, // .
    RANGE, // ..
    SEMICOLON, // ;
    COLON, // :
    EXCLAMATION, // !
    APOSTROPHE, // '
    ARROW, // ->

    LEFT_PAREN, // (
    RIGHT_PAREN, // )
    LEFT_BRACKET, // [
    RIGHT_BRACKET, // ]
    LEFT_BRACE, // {
    RIGHT_BRACE, // }

    END_OF_FILE,

    Unknown
};

inline std::string to_string(TokenType tokenType) {
    switch (tokenType) {
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::IF: return "IF";
        case TokenType::ELSE: return "ELSE";
        case TokenType::WHILE: return "WHILE";
        case TokenType::FOR: return "FOR";
        case TokenType::FN: return "FN";
        case TokenType::RETURN: return "RETURN";
        case TokenType::VAR: return "VAR";
        case TokenType::LET: return "LET";
        case TokenType::AS: return "AS";
        case TokenType::IN: return "IN";
        case TokenType::NOT: return "NOT";
        case TokenType::OR: return "OR";
        case TokenType::AND: return "AND";
        case TokenType::XOR: return "XOR";
        case TokenType::COMMENT: return "COMMENT";
        case TokenType::INT_LITERAL: return "INT_LITERAL";
        case TokenType::FLOAT_LITERAL: return "FLOAT_LITERAL";
        case TokenType::TRUE_LITERAL: return "TRUE_LITERAL";
        case TokenType::FALSE_LITERAL: return "FALSE_LITERAL";
        case TokenType::CHAR_LITERAL: return "CHAR_LITERAL";
        case TokenType::STRING_LITERAL: return "STRING_LITERAL";
        case TokenType::INT_TYPE: return "INT_TYPE";
        case TokenType::FLOAT_TYPE: return "FLOAT_TYPE";
        case TokenType::BOOL_TYPE: return "BOOL_TYPE";
        case TokenType::CHAR_TYPE: return "CHAR_TYPE";
        case TokenType::STRING_TYPE: return "STRING_TYPE";
        case TokenType::VOID_TYPE: return "VOID_TYPE";
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::STAR: return "STAR";
        case TokenType::SLASH: return "SLASH";
        case TokenType::CARET: return "CARET";
        case TokenType::PERCENT: return "PERCENT";
        case TokenType::PLUS_EQUAL: return "PLUS_EQUAL";
        case TokenType::MINUS_EQUAL: return "MINUS_EQUAL";
        case TokenType::STAR_EQUAL: return "STAR_EQUAL";
        case TokenType::SLASH_EQUAL: return "SLASH_EQUAL";
        case TokenType::CARET_EQUAL: return "CARET_EQUAL";
        case TokenType::PERCENT_EQUAL: return "PERCENT_EQUAL";
        case TokenType::INCREMENT: return "INCREMENT";
        case TokenType::DECREMENT: return "DECREMENT";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::LEFT_ANGLE: return "LEFT_ANGLE";
        case TokenType::RIGHT_ANGLE: return "RIGHT_ANGLE";
        case TokenType::LEFT_ANGLE_EQUAL: return "LEFT_ANGLE_EQUAL";
        case TokenType::RIGHT_ANGLE_EQUAL: return "RIGHT_ANGLE_EQUAL";
        case TokenType::EXCLAMATION_EQUAL: return "EXCLAMATION_EQUAL";
        case TokenType::UNDERSCORE: return "UNDERSCORE";
        case TokenType::ASSIGN: return "ASSIGN";
        case TokenType::QUOTE: return "QUOTE";
        case TokenType::COMMA: return "COMMA";
        case TokenType::POINT: return "POINT";
        case TokenType::RANGE: return "RANGE";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::COLON: return "COLON";
        case TokenType::EXCLAMATION: return "EXCLAMATION";
        case TokenType::APOSTROPHE: return "APOSTROPHE";
        case TokenType::ARROW: return "ARROW";
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::LEFT_BRACKET: return "LEFT_BRACKET";
        case TokenType::RIGHT_BRACKET: return "RIGHT_BRACKET";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        default: return "Unknown";
    }
}
