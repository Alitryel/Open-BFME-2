// cl: /O1 /Ireference/shims/bfme2_ascii
// Native 0x00564B1A / 39: assign two StringBase<char> members at +4/+8.
// Both calls reach the rowed copy-set body at 0x000366F0. No original
// class name or complete object size is established. The untouched prefix
// is opaque; it is not declared to be a vtable or given a semantic type.
// StringBase semantics come from its shared header and matched target body.
#include "string_base.h"

class Rva00564B1A
{
    unsigned char m_unknown[4];
    StringBase<char> m_first;
    StringBase<char> m_second;
public:
    Rva00564B1A& rva00564B1A(const Rva00564B1A& other);
};

// ?Rva00564B1A::rva00564B1A present-unmatched
Rva00564B1A& Rva00564B1A::rva00564B1A(const Rva00564B1A& other)
{
    m_first.set(other.m_first);
    m_second.set(other.m_second);
    return *this;
}
