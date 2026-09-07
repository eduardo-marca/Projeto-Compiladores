#pragma once

#include <unordered_set>
#include <unordered_map>

#include <optional>
#include "Token.hpp"
#include "CharClass.hpp"

using State = int;

class DFA {
public:
    using Symbol = char;

    DFA(State initial) : initialState(initial) {}

    void addTransition(State from, CharClass symbol, State to);

    void setFinal(State state, TokenType type);

    std::optional<State> transition(State state, CharClass symbol) const;

    bool isFinal(State state) const;

    std::optional<TokenType> tokenType(State state) const;

    State getInitialState() const;

    void buildLexerDFA();

private:
    State initialState;
    
    std::unordered_map<
        State,
        std::unordered_map<CharClass, State>
    > transitions;
    
    std::unordered_map<State, TokenType> finalStates;
};
