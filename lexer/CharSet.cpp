#include "CharSet.hpp"

namespace {

constexpr std::size_t charCount = 256;

std::size_t indexOf(char c)
{
    return static_cast<unsigned char>(c);
}

}

CharSet CharSet::any()
{
    CharSet cs;
    cs.chars.fill(true);
    return cs;
}

CharSet CharSet::none()
{
    return CharSet{};
}

CharSet CharSet::digit()
{
    return CharSet::range('0', '9');
}

CharSet CharSet::letter()
{
    return CharSet::range('a', 'z')
            .unite(CharSet::range('A', 'Z'));
}

CharSet CharSet::whitespace()
{
    return CharSet{}
        .add(' ')
        .add('\t')
        .add('\n');
}

CharSet CharSet::identifierStart()
{
    return CharSet::letter()
            .unite(CharSet::single('_'));
}

CharSet CharSet::identifier()
{
    return CharSet::identifierStart()
            .unite(CharSet::digit());
}

CharSet CharSet::stringChar()
{
    return CharSet::any()
        .remove('"')
        .remove('\n');
}

CharSet CharSet::lineCommentCharacter()
{
    return CharSet::any()
        .remove('\n');
}

CharSet CharSet::blockCommentCharacter()
{
    return CharSet::any();
}

CharSet CharSet::range(char first, char last)
{
    CharSet cs;
    cs.addRange(first, last);
    return cs;
}

CharSet CharSet::single(char c)
{
    CharSet cs;
    cs.chars[static_cast<unsigned char>(c)] = true;
    return cs;
}

bool CharSet::contains(char c) const
{
    return chars[indexOf(c)];
}

CharSet &CharSet::add(char c)
{
    chars[indexOf(c)] = true;
    return *this;
}

CharSet &CharSet::addRange(char first, char last)
{
    const auto start = indexOf(first);
    const auto end = indexOf(last);

    if(start > end)
        return *this;

    for(std::size_t i = start; i <= end; i++)
        chars[i] = true;

    return *this;
}

CharSet &CharSet::remove(char c)
{
    chars[indexOf(c)] = false;
    return *this;
}

CharSet &CharSet::removeRange(char first, char last)
{
    const auto start = indexOf(first);
    const auto end = indexOf(last);

    if(start > end)
        return *this;

    for(std::size_t i = start; i <= end; i++)
        chars[i] = false;

    return *this;
}

CharSet &CharSet::unite(const CharSet &other)
{
    for(std::size_t i = 0; i < charCount; i++)
        chars[i] = chars[i] || other.chars[i];

    return *this;
}

CharSet &CharSet::intersect(const CharSet &other)
{
    for(std::size_t i = 0; i < charCount; i++)
        chars[i] = chars[i] && other.chars[i];

    return *this;
}

CharSet &CharSet::subtract(const CharSet &other)
{
    for(std::size_t i = 0; i < charCount; i++)
        chars[i] = chars[i] && !other.chars[i];

    return *this;
}
