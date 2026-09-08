#pragma once

#include <array>

class CharSet {
public:
    static CharSet any();
    static CharSet none();
    static CharSet digit();
    static CharSet letter();
    static CharSet whitespace();
    static CharSet identifierStart();
    static CharSet identifier();
    static CharSet stringChar();
    static CharSet lineCommentCharacter();
    static CharSet blockCommentCharacter();
    
    static CharSet range(char first, char last);
    static CharSet single(char c);

    bool contains(char c) const;

    CharSet& add(char c);
    CharSet& addRange(char first, char last);

    CharSet& remove(char c);
    CharSet& removeRange(char first, char last);

    CharSet& unite(const CharSet& other);
    CharSet& intersect(const CharSet& other);
    CharSet& subtract(const CharSet& other);

private:
    std::array<bool, 256> chars{};
};
