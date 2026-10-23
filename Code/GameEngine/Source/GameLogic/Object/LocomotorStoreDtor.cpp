// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1LocomotorStore@@QAE@XZ, retail 0x002207C4 68B.
// LocomotorStore dtor after ctor 0x0022078E in same file area: destroys +8 via
// rowed 0x00360D26 then two StringBase<char> members at +4/+0 via rowed
// releaseBuffer 0x00036410. Order +8/+4/+0 with EH states 1/0 matches ctor
// order +0/+4/+8. Identity: prev row ctor same class, next deleting-dtor
// candidate 0x00220903 calls here then operator delete, no vtable store.
#include "ascii_string.h"

class Rva00360D26Member
{
public:
    ~Rva00360D26Member();

private:
    unsigned m_unknown;
};

class LocomotorStore
{
public:
    ~LocomotorStore();

private:
    AsciiString m_slot00;
    AsciiString m_slot04;
    Rva00360D26Member m_templates08;
};

LocomotorStore::~LocomotorStore()
{
}
