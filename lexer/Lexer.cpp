#include "Lexer.hpp"
#include <optional>
#include <iostream>

Lexer::Lexer(const std::string& source) : source(source), dfa(0)
{
    dfa.buildLexerDFA();
}

Token Lexer::nextToken()
{
    while(position < source.size() && std::isspace(source[position])) {
        position++;
    }

    if(position == source.size()) return Token(TokenType::EndOfFile, "");

    std::size_t start = position;

    State state = dfa.getInitialState();

    std::size_t lastFinalPosition = start;
    std::optional<TokenType> lastToken;

    while(position < source.size()) {
        char c = source[position];

        auto next = dfa.transition(state, classify(c));

        if(!next.has_value())
            break;

        state = *next;
        position++;

        if(dfa.isFinal(state)) {
            lastFinalPosition = position;
            lastToken = dfa.tokenType(state);
        }
    }

    if(!lastToken.has_value()) {
        std::cerr << "Could Not Recognize Token" << std::endl;
    }

    position = lastFinalPosition;

    std::string lexeme = source.substr(start, position - start);

    Token token = Token(*lastToken, lexeme);

    if(token.type == TokenType::UniqueToken) {
        if(token.lexeme == ";") token.type = TokenType::Semicolon;
        else if(token.lexeme == "(") token.type = TokenType::LParen;
        else if(token.lexeme == ")") token.type = TokenType::RParen;
        else if(token.lexeme == "[") token.type = TokenType::LBracket;
        else if(token.lexeme == "]") token.type = TokenType::RBracket;
        else if(token.lexeme == "{") token.type = TokenType::LCurly;
        else if(token.lexeme == "}") token.type = TokenType::RCurly;
        else if(token.lexeme == ",") token.type = TokenType::Comma;
        else if(token.lexeme == ":") token.type = TokenType::Colon;
        else if(token.lexeme == "?") token.type = TokenType::Question;
        else token.type = TokenType::Unknown;
    }
    else if(token.type == TokenType::Identifier) {
        if(token.lexeme == "if") token.type = TokenType::If;
        else if(token.lexeme == "else") token.type = TokenType::Else;
        else if(token.lexeme == "while") token.type = TokenType::While;
        else if(token.lexeme == "for") token.type = TokenType::For;
        else if(token.lexeme == "fn") token.type = TokenType::Fn;
        else if(token.lexeme == "return") token.type = TokenType::Return;
        else if(token.lexeme == "var") token.type = TokenType::Var;
        else if(token.lexeme == "let") token.type = TokenType::Let;
        else if(token.lexeme == "in") token.type = TokenType::In;
        else if(token.lexeme == "not") token.type = TokenType::Not;
        else if(token.lexeme == "or") token.type = TokenType::Or;
        else if(token.lexeme == "and") token.type = TokenType::And;
        else if(token.lexeme == "xor") token.type = TokenType::Xor;
        else if(token.lexeme == "Int") token.type = TokenType::IntType;
        else if(token.lexeme == "Float") token.type = TokenType::FloatType;
        else if(token.lexeme == "Bool") token.type = TokenType::BoolType;
        else if(token.lexeme == "Char") token.type = TokenType::CharType;
        else if(token.lexeme == "String") token.type = TokenType::StringType;
    }

    return token;
}
