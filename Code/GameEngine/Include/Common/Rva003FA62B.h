#pragma once
#include <vector>
#include "RegionTurnObserverView.h"

// Native constructor3FA6B4 and its20-byte allocation at210D1D fix the extent.
// Callback3FA464 and clear3FA5B9 independently access8-byte records at+4.
// Original application and record identities remain unknown.
struct BfmePod8 { void *m_ptr; unsigned int m_val; };
struct Rva003FA62BOwner;
class Rva003FA62B : public RegionTurnObserverView
{
public:
    Rva003FA62B(Rva003FA62BOwner *);
    ~Rva003FA62B();
    virtual void BeginTurn(int, int);
    void clear();
private:
    _STL::vector<BfmePod8> m_records04;
    Rva003FA62BOwner *m_owner10;
};

typedef char Rva003FA62BRecordSizeCheck[sizeof(BfmePod8)==8 ? 1 : -1];
typedef char Rva003FA62BSizeCheck[sizeof(Rva003FA62B)==20 ? 1 : -1];
