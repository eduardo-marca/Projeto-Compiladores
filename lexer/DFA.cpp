#include "DFA.hpp"

void DFA::addTransition(State from, CharSet symbols, State to)
{
    for(int i = 0; i < 256; i++) {
        char c = static_cast<char>(i);
        if(symbols.contains(c)) transitions[from][c] = to;
    }
}

void DFA::setFinal(State state, TokenType type)
{
    finalStates[state] = type;
}

std::optional<State> DFA::transition(State state, Symbol symbol) const
{
    const auto stateIt = transitions.find(state);
    if(stateIt != transitions.end())
    {
        const auto symbolIt = stateIt->second.find(symbol);
        if(symbolIt != stateIt->second.end())
            return symbolIt->second;
    }

    return std::nullopt;
}

bool DFA::isFinal(State state) const
{
    return finalStates.count(state) != 0;
}

std::optional<TokenType> DFA::tokenType(State state) const
{
    if(isFinal(state)) return finalStates.find(state)->second;
    return std::nullopt;
}

State DFA::getInitialState() const
{
    return initialState;
}

void DFA::buildLexerDFA()
{
    // Minus and arrow
    addTransition(0, CharSet::single('-'), 3);
    setFinal(3, TokenType::MINUS);
    addTransition(3, CharSet::single('>'), 1);
    setFinal(1, TokenType::ARROW);
    addTransition(3, CharSet::single('='), 2);
    setFinal(2, TokenType::MINUS_EQUAL);
    addTransition(3, CharSet::single('-'), 4);
    setFinal(4, TokenType::DECREMENT);

    // Int and float literals
    addTransition(3, CharSets::Digit(), 5);
    addTransition(0, CharSets::Digit(), 5);
    addTransition(5, CharSets::Digit(), 5);
    setFinal(5, TokenType::INT_LITERAL);
    addTransition(5, CharSet::single('.'), 6);
    addTransition(6, CharSets::Digit(), 7);
    addTransition(7, CharSets::Digit(), 7);
    setFinal(7, TokenType::FLOAT_LITERAL);

    // Char literal
    addTransition(0, CharSet::single('\''), 8);
    addTransition(8, CharSets::StringCharacter(), 9);
    addTransition(9, CharSet::single('\''), 10);
    setFinal(10, TokenType::CHAR_LITERAL);

    // String literal
    addTransition(0, CharSet::single('\"'), 11);
    addTransition(11, CharSets::StringCharacter(), 12);
    addTransition(12, CharSets::StringCharacter(), 12);
    addTransition(12, CharSet::single('\"'), 13);
    setFinal(13, TokenType::STRING_LITERAL);

    // Division and comments
    addTransition(0, CharSet::single('/'), 15);
    setFinal(15, TokenType::SLASH);
    addTransition(15, CharSet::single('='), 14);
    setFinal(14, TokenType::SLASH_EQUAL);
    addTransition(15, CharSet::single('/'), 16);
    addTransition(16, CharSets::LineCommentCharacter(), 16);
    setFinal(16, TokenType::COMMENT);
    addTransition(15, CharSet::single('*'), 17);
    addTransition(17, CharSets::BlockCommentCharacter().remove('*'), 17);
    addTransition(17, CharSet::single('*'), 18);
    addTransition(18, CharSets::BlockCommentCharacter().remove('*').remove('/'), 17);
    addTransition(18, CharSet::single('*'), 18);
    addTransition(18, CharSet::single('/'), 19);
    setFinal(19, TokenType::COMMENT);

    // Addition
    addTransition(0, CharSet::single('+'), 20);
    setFinal(20, TokenType::PLUS);
    addTransition(20, CharSet::single('+'), 21);
    setFinal(21, TokenType::INCREMENT);
    addTransition(20, CharSet::single('='), 22);
    setFinal(22, TokenType::PLUS_EQUAL);

    // Relational and arithmetic operators
    // <=
    addTransition(0, CharSet::single('<'), 23);
    setFinal(23, TokenType::LEFT_ANGLE);
    addTransition(23, CharSet::single('='), 24);
    setFinal(24, TokenType::LEFT_ANGLE_EQUAL);

    // >=
    addTransition(0, CharSet::single('>'), 25);
    setFinal(25, TokenType::RIGHT_ANGLE);
    addTransition(25, CharSet::single('='), 26);
    setFinal(26, TokenType::RIGHT_ANGLE_EQUAL);

    // !=
    addTransition(0, CharSet::single('!'), 27);
    setFinal(27, TokenType::EXCLAMATION);
    addTransition(27, CharSet::single('='), 28);
    setFinal(28, TokenType::EXCLAMATION_EQUAL);

    // ==
    addTransition(0, CharSet::single('='), 29);
    setFinal(29, TokenType::ASSIGN);
    addTransition(29, CharSet::single('='), 30);
    setFinal(30, TokenType::EQUAL);

    // *=
    addTransition(0, CharSet::single('*'), 31);
    setFinal(31, TokenType::STAR);
    addTransition(31, CharSet::single('='), 32);
    setFinal(32, TokenType::STAR_EQUAL);

    // ^=
    addTransition(0, CharSet::single('^'), 33);
    setFinal(33, TokenType::CARET);
    addTransition(33, CharSet::single('='), 34);
    setFinal(34, TokenType::CARET_EQUAL);

    // %=
    addTransition(0, CharSet::single('%'), 35);
    setFinal(35, TokenType::PERCENT);
    addTransition(35, CharSet::single('='), 36);
    setFinal(36, TokenType::PERCENT_EQUAL);

    // ..
    addTransition(0, CharSet::single('.'), 37);
    setFinal(37, TokenType::POINT);
    addTransition(37, CharSet::single('.'), 38);
    setFinal(38, TokenType::RANGE);

    // Identifier
    addTransition(0, CharSets::IdentifierStart(), 39);
    addTransition(39, CharSets::IdentifierContinue(), 39);
    setFinal(39, TokenType::IDENTIFIER);

    // Unique tokens
    addTransition(0, CharSet::single('('), 40);
    setFinal(40, TokenType::LEFT_PAREN);

    addTransition(0, CharSet::single(')'), 41);
    setFinal(41, TokenType::RIGHT_PAREN);

    addTransition(0, CharSet::single('{'), 42);
    setFinal(42, TokenType::LEFT_BRACE);

    addTransition(0, CharSet::single('}'), 43);
    setFinal(43, TokenType::RIGHT_BRACE);

    addTransition(0, CharSet::single('['), 44);
    setFinal(44, TokenType::LEFT_BRACKET);

    addTransition(0, CharSet::single(']'), 45);
    setFinal(45, TokenType::RIGHT_BRACKET);

    addTransition(0, CharSet::single(';'), 46);
    setFinal(46, TokenType::SEMICOLON);

    addTransition(0, CharSet::single(','), 47);
    setFinal(47, TokenType::COMMA);

    addTransition(0, CharSet::single(':'), 48);
    setFinal(48, TokenType::COLON);

    addTransition(0, CharSet::single('?'), 49);
    setFinal(49, TokenType::QUESTION);
}
