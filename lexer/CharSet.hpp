#pragma once

#include <array>

class CharSet {
public:
    // CharSet com todos os caracteres
    static CharSet any();
    // CharSet com nenhum caractere
    static CharSet none();
    
    // CharSet com range incluso
    static CharSet range(char first, char last);
    // CharSet com um único caractere
    static CharSet single(char c);

    // Verfica se um caractere está contido
    bool contains(char c) const;

    // adiciona um caractere
    CharSet& add(char c);
    // adiciona um range de caracteres
    CharSet& addRange(char first, char last);

    // remove um caractere
    CharSet& remove(char c);
    // remove um range de caracteres
    CharSet& removeRange(char first, char last);

    // Faz a união dos CharSet
    CharSet& unite(const CharSet& other);
    // Faz a interseção dos CharSet
    CharSet& intersect(const CharSet& other);
    // Faz a diferença dos CharSet
    CharSet& subtract(const CharSet& other);

private:
    // para cada caractere ASCII, marca se está incluso ou não
    std::array<bool, 256> chars{};
};

// CharSets predefinidos para uso geral
namespace CharSets {

    inline CharSet Digit() {
        return CharSet::range('0', '9');
    }

    inline CharSet Lowercase() {
        return CharSet::range('a', 'z');
    }

    inline CharSet Uppercase() {
        return CharSet::range('A', 'Z');
    }

    inline CharSet Letter() {
        return Lowercase()
            .unite(Uppercase());
    }

    inline CharSet IdentifierStart() {
        return Letter()
            .add('_');
    }

    inline CharSet IdentifierContinue() {
        return IdentifierStart()
            .unite(Digit());
    }

    inline CharSet StringCharacter() {
        return CharSet::any()
            .remove('"')
            .remove('\n');
    }

    inline CharSet LineCommentCharacter() {
        return CharSet::any()
            .remove('\n');
    }

    inline CharSet BlockCommentCharacter() {
        return CharSet::any();
    }

    inline CharSet Whitespace() {
        return CharSet::single(' ')
            .add('\t')
            .add('\n')
            .add('\r');
    }

    inline CharSet Any() {
        return CharSet::any();
    }
}
