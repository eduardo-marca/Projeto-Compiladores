#pragma once

#include <array>

class CharSet {
public:
    static CharSet any();
    static CharSet none();
    
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
