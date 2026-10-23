// cl: /O1 /DNDEBUG /MD /GX /Ireference/shims/moduledata
//
// ??1Rva004E179A@@UAE@XZ 81B @0x004E179A: ModuleData dtor with three
// AsciiString members at +0x4/+0x8/+0xC (inlined releaseBuffer calls
// via rowed 0x00036410) plus Snapshot vtable restore to 0x007BB554.
// Derived vtable 0x00861B78 stored at entry. Unlock lane: landing unblocks
// 0x004E1CFA/28. Evidence: EH prolog 0x00791A74 plus states 2/1/0 plus
// three releaseBuffer plus second vtable 0x007BB554 plus ret, callers at
// 0x004E183A 0x004E1CFD. The canonical Snapshot header supplies the base dtor;
// The shared record declaration supplies the native four-slot derived table.

#include "Rva004E179A.h"

// ??1Rva004E179A@@UAE@XZ
Rva004E179A::~Rva004E179A()
{
}

// ?Rva004E179ADelete@@YAXPAVRva004E179A@@@Z absent-from-retail
void Rva004E179ADelete(Rva004E179A *p)
{
	delete p;
}

// Native C61B78 slots 1 and 2 point to B3FD0 and 4E1794.
void Rva004E179A::LoadPostProcess() {}
const char *Rva004E179A::GetSnapshotName() { return "SpawnBuilding"; }
