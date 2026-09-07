#include "Lexer.hpp"
#include <optional>
#include <iostream>

Lexer::Lexer(const std::string& source) : source(source), dfa(0)
{
    dfa.buildLexerDFA();

    reserved_words["if"] = TokenType::If;
    reserved_words["else"] = TokenType::Else;
    reserved_words["while"] = TokenType::While;
    reserved_words["for"] = TokenType::For;
    reserved_words["fn"] = TokenType::Fn;
    reserved_words["return"] = TokenType::Return;
    reserved_words["as"] = TokenType::As;
    reserved_words["var"] = TokenType::Var;
    reserved_words["let"] = TokenType::Let;
    reserved_words["in"] = TokenType::In;
    reserved_words["not"] = TokenType::Not;
    reserved_words["or"] = TokenType::Or;
    reserved_words["and"] = TokenType::And;
    reserved_words["xor"] = TokenType::Xor;
    reserved_words["Int"] = TokenType::IntType;
    reserved_words["Float"] = TokenType::FloatType;
    reserved_words["Bool"] = TokenType::BoolType;
    reserved_words["Char"] = TokenType::CharType;
    reserved_words["String"] = TokenType::StringType;
    reserved_words["true"] = TokenType::TrueLiteral;
    reserved_words["false"] = TokenType::FalseLiteral;
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

    if(token.type == TokenType::Identifier) {
        if(reserved_words.count(token.lexeme)) token.type = reserved_words[lexeme];
    }

    return token;
}
