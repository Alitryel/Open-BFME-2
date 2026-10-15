// cl: /O1 /G7 /arch:SSE /MD /EHsc- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// ?rva00282135@Rva00282135@@QAEXXZ, retail 0x00282135, 126 bytes: empties the area-record vector one entry at a time (listener beforeRemove/afterRemove around each pop_back) then swaps it with an empty vector and resets nextID. Bank evidence W7 (U1/S2); neutral names.
// stlport
#include <vector>
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
#include "AreaSetEntryView.h"
// The implicit Rva0027EA49 destructor owns the existing 13-byte retail body
// at 0x0027EA49: release the retained pointer at +4 via fastcall 0x0007DEEF.
// Its complete bytes and relocation equal the former standalone definition.
// Keep the row beside this vector consumer, without a second strong copy.
struct Rva0027EA49 { int m_00; AreaRefValueView m_04; };
typedef _STL::vector<Rva0027EA49> AreaRecordVector;
template <> AreaRecordVector::~vector();
class Rva00281A33Listener {
public:
    virtual void unused();
    virtual void insert(void *, int);
    virtual void afterRemove(void *, int);
    virtual void beforeRemove(void *, int);
};
class Rva00281A33List {
public:
    void forEach(void (Rva00281A33Listener::*)(void *, int), void *, int);
    unsigned char storage[0x10];
};
class Rva00282135 {
    Rva00281A33List listeners;
    int nextID;
    AreaRecordVector entries;
public:
    void rva00282135();
};
void Rva00282135::rva00282135() {
    while (!entries.empty()) {
        AreaRetainedObjectView *const &target = entries.back().m_04.pointer;
        listeners.forEach(&Rva00281A33Listener::beforeRemove, this, reinterpret_cast<int>(target));
        entries.pop_back();
        listeners.forEach(&Rva00281A33Listener::afterRemove, this, reinterpret_cast<int>(target));
    }
    AreaRecordVector().swap(entries);
    nextID = 1;
}
template void AreaRecordVector::swap(AreaRecordVector &);
