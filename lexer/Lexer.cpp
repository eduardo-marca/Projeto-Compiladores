#include "Lexer.hpp"
#include <optional>
#include <iostream>

Lexer::Lexer(const std::string& source) : source(source), dfa(0)
{
    dfa.buildLexerDFA();

    reserved_words["if"] = TokenType::IF;
    reserved_words["else"] = TokenType::ELSE;
    reserved_words["while"] = TokenType::WHILE;
    reserved_words["for"] = TokenType::FOR;
    reserved_words["fn"] = TokenType::FN;
    reserved_words["return"] = TokenType::RETURN;
    reserved_words["as"] = TokenType::AS;
    reserved_words["var"] = TokenType::VAR;
    reserved_words["let"] = TokenType::LET;
    reserved_words["in"] = TokenType::IN;
    reserved_words["not"] = TokenType::NOT;
    reserved_words["or"] = TokenType::OR;
    reserved_words["and"] = TokenType::AND;
    reserved_words["xor"] = TokenType::XOR;
    reserved_words["Int"] = TokenType::INT_TYPE;
    reserved_words["Float"] = TokenType::FLOAT_TYPE;
    reserved_words["Bool"] = TokenType::BOOL_TYPE;
    reserved_words["Char"] = TokenType::CHAR_TYPE;
    reserved_words["String"] = TokenType::STRING_TYPE;
    reserved_words["Void"] = TokenType::VOID_TYPE;
    reserved_words["true"] = TokenType::TRUE_LITERAL;
    reserved_words["false"] = TokenType::FALSE_LITERAL;
}

Token Lexer::nextToken()
{
    while(position < source.size() && std::isspace(source[position])) {
        position++;
    }

    if(position == source.size()) return Token(TokenType::END_OF_FILE, "");

    std::size_t start = position;

    State state = dfa.getInitialState();

    std::size_t lastFinalPosition = start;
    std::optional<TokenType> lastToken;

    while(position < source.size()) {
        char c = source[position];

        auto next = dfa.transition(state, c);

        if(!next.has_value())
            break;

        state = *next;
        position++;

        if(dfa.isFinal(state)) {
            lastFinalPosition = position;
            lastToken = dfa.tokenType(state);
        }

        //std::cout << state << std::endl;
    }

    if(!lastToken.has_value()) {
        std::cerr << "Could Not Recognize Token" << std::endl;
    }

    position = lastFinalPosition;

    std::string lexeme = source.substr(start, position - start);

    Token token = Token(*lastToken, lexeme);

    if(token.type == TokenType::IDENTIFIER) {
        if(reserved_words.count(token.lexeme)) token.type = reserved_words[lexeme];
    }

    return token;
}
