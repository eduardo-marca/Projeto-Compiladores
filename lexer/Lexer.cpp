#include "Lexer.hpp"
#include <optional>
#include <iostream>

Lexer::Lexer(const std::string& source) : source(source), dfa(0)
{
    dfa.buildLexerDFA();

    // registra as palavras reservadas da linguagem
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
    // ignora espaços e fim de linha
    while(position < source.size() && std::isspace(source[position])) {
        column++;
        if(source[position] == '\n') {
            column = 1;
            line++;
        }
        position++;
    }

    // se está no final, retorna EOF
    if(position == source.size()) return Token(TokenType::END_OF_FILE, "", line, column);

    // guarda posição inicial
    std::size_t start = position;
    int startColumn = column;

    State state = dfa.getInitialState();

    // guarda último token encontrado e sua posição
    std::size_t lastFinalPosition = start;
    std::optional<TokenType> lastToken = std::nullopt;

    while(position < source.size()) {
        char c = source[position];

        // pede próximo estado ao DFA
        auto next = dfa.transition(state, c);

        // se transição não existe, para o loop
        if(!next.has_value())
            break;

        state = *next;
        position++;
        column++;

        // se é estado final, guarda seu token e posição
        if(dfa.isFinal(state)) {
            lastFinalPosition = position;
            lastToken = dfa.tokenType(state);
        }
    }

    // se não encontrou nenhum token, lança erro léxico
    if(!lastToken.has_value()) {
        std::cerr << "Could Not Recognize Token" << std::endl;
        exit(-1);
    }

    // retorna para posição do último token
    position = lastFinalPosition;

    // acha o lexema do token e cria um token
    std::string lexeme = source.substr(start, position - start);

    Token token = Token(*lastToken, lexeme, line, startColumn);

    // se token for do tipo identificador, verifica se é palavra reservada
    if(token.type == TokenType::IDENTIFIER) {
        if(reserved_words.count(token.lexeme)) token.type = reserved_words[lexeme];
    }

    return token;
}
