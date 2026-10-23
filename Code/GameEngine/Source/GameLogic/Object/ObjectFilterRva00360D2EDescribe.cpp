// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// Retail 0x00360D2E/139 (RET 4): on the same index-into-0x94-byte-table
// descriptor as the rowed ObjectFilter::isValid 0x00360CED (begin/end
// globals 0xE01E68/0xE01E6C), append to the caller's AsciiString the +0x64
// names of the pointers in the record's two vectors (+0x18 and +0x30), then
// the name of every set bit among the record's 0xDA KindOf bits (+0x48,
// through the rowed bit-name lookup Rva002AA2CF 0x002AA2CF). An index past
// the table or equal to -1 appends nothing. Concatenation is the rowed
// StringBase<char>::concat pair. The method's name is address-derived.
#include "ascii_string.h"

typedef bool Bool;

struct Rva00360D2ENamed
{
    char m_pad00[0x64];
    AsciiString m_name;	// +0x64
};

class Rva002AA2CF
{
public:
    void *rva002AA2CF(unsigned int idx);
private:
    unsigned int m_bits[8];
};

struct Rva00360D2ERecord
{
    char m_pad00[0x18];
    Rva00360D2ENamed **m_firstBegin;	// +0x18
    Rva00360D2ENamed **m_firstEnd;	// +0x1C
    char m_pad20[0x30 - 0x20];
    Rva00360D2ENamed **m_secondBegin;	// +0x30
    Rva00360D2ENamed **m_secondEnd;	// +0x34
    char m_pad38[0x48 - 0x38];
    Rva002AA2CF m_kinds;		// +0x48
    char m_pad68[0x94 - 0x68];
};

extern unsigned char *g_validityBegin;
extern unsigned char *g_validityEnd;

class ObjectFilter
{
public:
    void rva00360D2E(AsciiString &out) const;
private:
    int m_entryIndex;
};

void ObjectFilter::rva00360D2E(AsciiString &out) const
{
    int index = m_entryIndex;
    int count = (g_validityEnd - g_validityBegin) / (int)sizeof(Rva00360D2ERecord);
    if (index < count && index != -1)
    {
        Rva00360D2ERecord *record = (Rva00360D2ERecord *)g_validityBegin + index;
        for (Rva00360D2ENamed **it = record->m_firstBegin; it != record->m_firstEnd; ++it)
            out += (*it)->m_name;
        for (Rva00360D2ENamed **it2 = record->m_secondBegin; it2 != record->m_secondEnd; ++it2)
            out += (*it2)->m_name;
        Rva002AA2CF *kinds = &record->m_kinds;
        for (int bit = 0; bit < 0xDA; ++bit)
        {
            const char *name = (const char *)kinds->rva002AA2CF(bit);
            if (name)
                out += name;
        }
    }
}
