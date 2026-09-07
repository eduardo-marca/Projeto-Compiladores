#include "DFA.hpp"

void DFA::addTransition(State from, CharClass symbol, State to)
{
    transitions[from][symbol] = to;
}

void DFA::setFinal(State state, TokenType type)
{
    finalStates[state] = type;
}

std::optional<State> DFA::transition(State state, CharClass symbol) const
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
    // Minus, Arrow
    addTransition(0, CharClass::Minus, 3);
    setFinal(3, TokenType::Minus);
    addTransition(3, CharClass::Greater, 1);
    setFinal(1, TokenType::Arrow);
    addTransition(3, CharClass::Equal, 2);
    setFinal(2, TokenType::MinusAssign);
    addTransition(3, CharClass::Minus, 4);
    setFinal(4, TokenType::Decrement);
    addTransition(3, CharClass::Digit, 5);
    
    // Numbers
    addTransition(0, CharClass::Digit, 5);
    addTransition(5, CharClass::Digit, 5);
    setFinal(5, TokenType::IntLiteral);
    addTransition(5, CharClass::Point, 6);
    addTransition(6, CharClass::Digit, 7);
    addTransition(7, CharClass::Digit, 7);
    setFinal(7, TokenType::FloatLiteral);

    // Char literal
    addTransition(0, CharClass::Apostrophe, 8);
    addTransition(8, CharClass::Digit, 9);
    addTransition(8, CharClass::Letter, 9);
    addTransition(9, CharClass::Apostrophe, 10);
    setFinal(10, TokenType::CharLiteral);

    // String literal
    addTransition(0, CharClass::Quote, 11);
    addTransition(11, CharClass::Digit, 12);
    addTransition(11, CharClass::Letter, 12);
    addTransition(12, CharClass::Digit, 12);
    addTransition(12, CharClass::Letter, 12);
    addTransition(12, CharClass::Quote, 13);
    setFinal(13, TokenType::StringLiteral);

    // Division and comment
    addTransition(0, CharClass::Slash, 15);
    setFinal(14, TokenType::Slash);
    addTransition(15, CharClass::Equal, 14);
    setFinal(14, TokenType::SlashAssign);
    addTransition(15, CharClass::Slash, 16);
    addTransition(16, CharClass::Digit, 16);
    addTransition(16, CharClass::Letter, 16);
    setFinal(14, TokenType::Comment);

    // Plus
    addTransition(0, CharClass::Plus, 17);
    setFinal(17, TokenType::Plus);
    addTransition(17, CharClass::Plus, 18);
    setFinal(18, TokenType::Increment);
    addTransition(17, CharClass::Equal, 20);
    setFinal(20, TokenType::PlusAssign);

    // Unique
    addTransition(0, CharClass::Semicolon, 19);
    addTransition(0, CharClass::LParen, 19);
    addTransition(0, CharClass::RParen, 19);
    addTransition(0, CharClass::LBracket, 19);
    addTransition(0, CharClass::RBracket, 19);
    addTransition(0, CharClass::LCurly, 19);
    addTransition(0, CharClass::RCurly, 19);
    addTransition(0, CharClass::Comma, 19);
    addTransition(0, CharClass::Colon, 19);
    addTransition(0, CharClass::Question, 19);
    setFinal(19, TokenType::UniqueToken);

    // Relational
    // <=
    addTransition(0, CharClass::Less, 21);
    setFinal(21, TokenType::Less);
    addTransition(21, CharClass::Equal, 22);
    setFinal(22, TokenType::LessEqual);

    // >=
    addTransition(0, CharClass::Greater, 23);
    setFinal(23, TokenType::Greater);
    addTransition(23, CharClass::Equal, 24);
    setFinal(24, TokenType::GreaterEqual);

    // !=
    addTransition(0, CharClass::Exclamation, 25);
    setFinal(25, TokenType::Not);
    addTransition(25, CharClass::Equal, 26);
    setFinal(26, TokenType::NotEqual);

    // ==
    addTransition(0, CharClass::Equal, 27);
    setFinal(27, TokenType::Assign);
    addTransition(27, CharClass::Equal, 28);
    setFinal(28, TokenType::Equal);

    // Identifier
    addTransition(0, CharClass::Letter, 29);
    addTransition(0, CharClass::Underscore, 29);
    addTransition(29, CharClass::Letter, 29);
    addTransition(29, CharClass::Digit, 29);
    addTransition(29, CharClass::Underscore, 29);
    setFinal(29, TokenType::Identifier);

    // Arithmetic operations
    // *=
    addTransition(0, CharClass::Star, 30);
    setFinal(30, TokenType::Star);
    addTransition(30, CharClass::Equal, 31);
    setFinal(31, TokenType::StarAssign);

    // ^=
    addTransition(0, CharClass::Caret, 32);
    setFinal(32, TokenType::Caret);
    addTransition(32, CharClass::Equal, 33);
    setFinal(33, TokenType::CaretAssign);

    // %=
    addTransition(0, CharClass::Percent, 34);
    setFinal(34, TokenType::Percent);
    addTransition(34, CharClass::Equal, 35);
    setFinal(35, TokenType::PercentAssign);

    // Point and Range
    addTransition(0, CharClass::Point, 36);
    setFinal(36, TokenType::Point);
    addTransition(36, CharClass::Point, 37);
    setFinal(37, TokenType::Range);
}
