// cl: /MD /DNDEBUG
// BFME1 donor6d9434269164392c5ba62aaa7c15a86b5b020d76:
// game/Libraries/Source/WWVegas/WWLib/hashtemplate.h destructor, emitted by
// clean stripoptimizer.cpp under BFME2 O1/G7/MD (also exact with SSE).
// Copyright2025 Electronic Arts Inc.; GPL-3.0-or-later, as in the donor.
// Target32B has a Ghidra entry at5B6EFE and ends at RET5B6F1D.
// Caller514EAB destroys its +290 subobject at514F06; Ghidra unwind entries
// 7951B6 and79535E tail-call the same body for +290 cleanup.
// Two optional pointer fields at offsets0/4 call the verified global
// array delete2FD80. This proves the cleanup and the accessed prefix only.
// Original class/template arguments, field names, array element types and
// full object size are unknown; the donor Edge/Triangle labels are not pins.
// Class identity: AptMainMenu's +0x290 member is built by BfmeThingTTD's ctor
// (0x005B6ED1, which ends where this body starts) and destroyed here by the
// ctor's unwind funclet 0x0079535E and the dtor 0x00514EAB, so this is
// ~BfmeThingTTD (a placeholder class name).
void __cdecl operator delete[](void *);

class BfmeThingTTD
{
    void *first;
    void *second;
public:
    ~BfmeThingTTD();
};

BfmeThingTTD::~BfmeThingTTD()
{
    if (first)
        operator delete[](first);
    if (second)
        operator delete[](second);
}
