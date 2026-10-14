// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ??4Rva002191FE@@QAEAAV0@ABV0@@Z @0x002191FE 59B
// Honest-address copy-assignment for int plus three AsciiStrings.
// Retail: self-check (cmp esi,edi je skip), dword copy at +0, three
// StringBase<char>::set calls at +4/+8/+0xC via rowed 0x000366F0, return
// *this (mov eax,esi ret 4). Caller 0x0021DEA2 in 56B body; neighbours
// 0x0021915B/0x0021929D share flags. No donor; honest Rva name.
#include "ascii_string.h"

class Rva002191FE
{
public:
    Rva002191FE &operator=(const Rva002191FE &other);
private:
    int m_0;
    AsciiString m_4;
    AsciiString m_8;
    AsciiString m_C;
};

Rva002191FE &Rva002191FE::operator=(const Rva002191FE &other)
{
    if (this != &other) {
        m_0 = other.m_0;
        m_4 = other.m_4;
        m_8 = other.m_8;
        m_C = other.m_C;
    }
    return *this;
}

// ??4Rva0021918C@@QAEAAV0@ABV0@@Z @0x0021918C 55B: the same self-checked
// copy-assignment shape over three AsciiStrings (+0/+4/+8) then a dword at
// +0xC. No donor; honest Rva name.
class Rva0021918C
{
public:
    Rva0021918C &operator=(const Rva0021918C &other);
private:
    AsciiString m_0;
    AsciiString m_4;
    AsciiString m_8;
    int m_C;
};

Rva0021918C &Rva0021918C::operator=(const Rva0021918C &other)
{
    if (this != &other) {
        m_0 = other.m_0;
        m_4 = other.m_4;
        m_8 = other.m_8;
        m_C = other.m_C;
    }
    return *this;
}

// ??4Rva002191C3@@QAEAAV0@ABV0@@Z @0x002191C3 59B: a dword at +0, two
// AsciiStrings at +4/+8, then dwords at +0xC/+0x10. No donor; honest Rva name.
class Rva002191C3
{
public:
    Rva002191C3 &operator=(const Rva002191C3 &other);
private:
    int m_0;
    AsciiString m_4;
    AsciiString m_8;
    int m_C;
    int m_10;
};

Rva002191C3 &Rva002191C3::operator=(const Rva002191C3 &other)
{
    if (this != &other) {
        m_0 = other.m_0;
        m_4 = other.m_4;
        m_8 = other.m_8;
        m_C = other.m_C;
        m_10 = other.m_10;
    }
    return *this;
}
