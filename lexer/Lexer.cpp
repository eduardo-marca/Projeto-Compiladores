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

std::vector<Token> Lexer::getTokens()
{
    std::vector<Token> tokens;
    Token cur = nextToken();

    while(cur.type != TokenType::END_OF_FILE) {
        if(cur.type != TokenType::COMMENT) tokens.push_back(cur);
        cur = nextToken();
    }
    tokens.push_back(cur);

    return tokens;
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
        throw error(line, startColumn, "Não foi possível identificar o Token");
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
    if(token.type == TokenType::INT_LITERAL) {
        token.value.val = std::stoll(token.lexeme);
        token.value.type = Type::Int;
        token.value.lexeme = token.lexeme;
    }
    else if(token.type == TokenType::FLOAT_LITERAL) {
        token.value.val = std::stod(token.lexeme);
        token.value.type = Type::Float;
        token.value.lexeme = token.lexeme;
    }
    else if(token.type == TokenType::TRUE_LITERAL) {
        token.value.val = true;
        token.value.type = Type::Bool;
        token.value.lexeme = token.lexeme;
    }
    else if(token.type == TokenType::FALSE_LITERAL) {
        token.value.val = false;
        token.value.type = Type::Bool;
        token.value.lexeme = token.lexeme;
    }
    else if(token.type == TokenType::CHAR_LITERAL) {
        token.value.val = token.lexeme[1];
        token.value.type = Type::Char;
        token.value.lexeme = token.lexeme[1];
    }
    else if(token.type == TokenType::STRING_LITERAL) {
        token.value.val = token.lexeme.substr(1, token.lexeme.size()-2);
        token.value.type = Type::String;
        token.value.lexeme = token.lexeme.substr(1, token.lexeme.size()-2);
    }

    return token;
}

LexicalError Lexer::error(const int line, const int column, std::string_view message)
{
    std::ostringstream oss;

    oss << "Erro lexical em "
    << line
    << ":"
    << column
    << ": "
    << message;

    return LexicalError(oss.str());
}
