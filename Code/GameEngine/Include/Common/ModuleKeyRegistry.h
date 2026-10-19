// Module-key registry lifetime and virtual interface from retail C549F0.
// Original class and entry spellings remain unknown. The set stores module
// pointers; key collection reads each pointed object's member at +8.
#ifndef BFME_MODULE_KEY_REGISTRY_H
#define BFME_MODULE_KEY_REGISTRY_H
#include <set>
class Rva003ED658;
struct Rva004ABDDCEntry;
class Rva004ABE53Dtor
{
public:
    __declspec(noinline) Rva004ABE53Dtor();
    __declspec(noinline) ~Rva004ABE53Dtor();
    virtual Rva003ED658 rva004ABDDC();
private:
    _STL::set<Rva004ABDDCEntry *> m_entries;
    unsigned char m_opaque10;
    unsigned char m_destroying;
};
#endif
