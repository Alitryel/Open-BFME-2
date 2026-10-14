// cl: /Ireference/shims/bfme2_ascii /EHsc
//
// ?getNthInList@ObjectTypes@@QBE?AVAsciiString@@I@Z @0x002041AC 53B: bounds-checked
// AsciiString getter over the pointer pair at +8/+0xc; out of range yields the
// exported AsciiString::TheEmptyString at 0x009E0878. Evidence: StringBase copy pin
// 0x000365F0; callers 0x00206011 0x003A17E6 0x003C2532 0x003C7511 0x003E826D 0x003E8351.
// Zero Hour's ObjectTypes::getNthInList: the list's names live in the
// vector at +8 (vptr and list name ahead of it).

#include "ascii_string.h"


class ObjectTypes
{
public:
    char pad[8];
    // The begin field reads twice with different scheduling: the count
    // computation folds it into a direct `sub edx,[ecx+8]` (single use, no
    // homing) while the fetch re-fetches it (`mov ecx,[ecx+8]` plus indexed
    // lea). A single spelling serves only one side, so the union carries
    // both: the plain member for count, the volatile member for the fetch
    // (EvaBucketAdvance/Rva00056F61Find precedent).
    union {
        AsciiString *m_start;
        AsciiString * volatile m_startVolatile;
    };
    AsciiString *m_end;
    AsciiString getNthInList(unsigned int index) const;
};

AsciiString ObjectTypes::getNthInList(unsigned int index) const
{
    unsigned int count = (unsigned)(((char *)m_end - (char *)m_start) >> 2);
    const AsciiString *p;
    if (index < count)
        p = m_startVolatile + index;
    else
        p = &AsciiString::TheEmptyString;
    return *p;
}
