// cl: /O1 /Ireference/shims/moduledata

#include "Common/Snapshot.h"

// Zero Hour's Snapshot.h, which many ported units still include, declares the
// destructor nonvirtual and out of line (??1Snapshot@@QAE@XZ). Retail has one
// Snapshot destructor, the exported virtual ??1Snapshot@@UAE@XZ at 0x0049B47C
// (a store of vtable 0x00BBB554); its derived destructors call it or inline
// that store. The QAE spelling is that header's view of the same function.
#pragma comment(linker, "/alternatename:??1Snapshot@@QAE@XZ=??1Snapshot@@UAE@XZ")

// The generated assignment: nothing to copy, not even the vtable.
typedef Snapshot &(Snapshot::*SnapshotAssign)(const Snapshot &);

SnapshotAssign g_snapshotAssign = &Snapshot::operator=;

// Snapshot's constructors and destructor are header inlines: 145 other units
// emit them as select-any copies, which plain definitions here collided
// with. The anchor keeps this unit's copies for the rows; it is not retail
// code.
#pragma inline_depth(0)
// ?_bfmeSnapshotInlineAnchor@@YAXPAVSnapshot@@@Z absent-from-retail
void _bfmeSnapshotInlineAnchor(Snapshot *snapshot)
{
    snapshot->Snapshot::Snapshot();
    snapshot->Snapshot::Snapshot(*snapshot);
    snapshot->Snapshot::~Snapshot();
}
#pragma inline_depth()
