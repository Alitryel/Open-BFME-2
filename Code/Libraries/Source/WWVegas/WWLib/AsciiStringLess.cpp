// cl: /O1 /DNDEBUG /MD

// Free AsciiString::operator< at 0x0005598C (23B). Leaf over the matched
// StringBase<char>::compare row at 0x69D6.

typedef bool Bool;

template <typename T> class StringBase
{
public:
    int compare(const StringBase<T> &that) const;

private:
    void *m_data;
};

class AsciiString : public StringBase<char>
{
};

inline Bool operator<(const AsciiString &left, const AsciiString &right)
{
    return (left.compare(right) < 0) || false;
}

#pragma inline_depth(0)
// ?bfmeEmitAsciiStringLess@@YAXPBVAsciiString@@0@Z present-unmatched
void bfmeEmitAsciiStringLess(const AsciiString *asciiString, const AsciiString *b)
{
    operator<(*asciiString, *b);
}
#pragma inline_depth()
