#pragma once

#include <cctype>

enum class CharClass {
    Letter,
    Digit,
    Underscore,
    Space,
    Tab,
    EndOfLine,

    Plus,
    Minus,
    Star,
    Slash,
    Caret,
    Percent,

    Equal,
    Less,
    Greater,
    Exclamation,

    Quote,
    Comma,
    Point,
    Semicolon,
    Colon,
    Question,
    Apostrophe,

    LParen,
    RParen,
    LBracket,
    RBracket,
    LCurly,
    RCurly,

    Other
};

inline CharClass classify(char c) {
    const unsigned char value = static_cast<unsigned char>(c);

    if(std::isalpha(value))
        return CharClass::Letter;

    if (std::isdigit(value))
        return CharClass::Digit;
        
    switch (c) {
        case ' ': return CharClass::Space;
        case '\t': return CharClass::Tab;
        case '\n': return CharClass::EndOfLine;
        case '+': return CharClass::Plus;
        case '-': return CharClass::Minus;
        case '*': return CharClass::Star;
        case '/': return CharClass::Slash;
        case '^': return CharClass::Caret;
        case '%': return CharClass::Percent;
        case '=': return CharClass::Equal;
        case '<': return CharClass::Less;
        case '>': return CharClass::Greater;
        case '!': return CharClass::Exclamation;
        case '_': return CharClass::Underscore;
        case '"': return CharClass::Quote;
        case ',': return CharClass::Comma;
        case '.': return CharClass::Point;
        case ';': return CharClass::Semicolon;
        case ':': return CharClass::Colon;
        case '?': return CharClass::Question;
        case '\'': return CharClass::Apostrophe;

        case '(': return CharClass::LParen;
        case ')': return CharClass::RParen;
        case '[': return CharClass::LBracket;
        case ']': return CharClass::RBracket;
        case '{': return CharClass::LCurly;
        case '}': return CharClass::RCurly;
        default:  return CharClass::Other;
    }
}
