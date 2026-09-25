#pragma once

#include <unordered_map>
#include <unordered_set>

#include "CharSet.hpp"
#include "Token.hpp"
#include <optional>

using State = int;
using Symbol = char;

class DFA {
  public:
    DFA(State initial) : initialState(initial) {}

    // adiciona transição ao DFA
    void addTransition(State from, CharSet symbols, State to);

    // marca estado como final com seu token
    void setFinal(State state, TokenType type);

    // retorna estado da transição, caso exista
    std::optional<State> transition(State state, Symbol symbol) const;

    // diz se um estado é final
    bool isFinal(State state) const;

    // retorna token associado ao etado, se existir
    std::optional<TokenType> tokenType(State state) const;

    // retorna o estado inicial
    State getInitialState() const;

    // adiciona transições e estados finais ao DFA
    void buildLexerDFA();

  private:
    State initialState;

    std::unordered_map<State, std::unordered_map<Symbol, State>> transitions;

    std::unordered_map<State, TokenType> finalStates;
};
