// cl: /DNDEBUG /MD /EHsc /Ireference/shims/moduledata

// Open-BFME5: GODupBase's constructor, retail 0x001B0D20, 85 bytes. The body
// carried only a machine byte-dump row; reverse/reloc_names.csv holds the name
// with identity=real.
//
// The same two-base shape as W3DTerrainVisualBase at 0x00602C70: the root the
// ledger sees at vtable 0x01073744 with its constructor inlined to that store,
// then SubsystemInterface constructed on this + 4, then the class's own two
// vtables over both, the secondary first. Nothing else -- no members are
// touched at all.
//
// The frame carries one unwind state, for the root base, because the
// SubsystemInterface constructor is a call that can throw.

// Retail ctor 0x00306782 unwinds through 0x00779B36 to the
// canonical Snapshot destructor at 0x0049B47C.
#include "Common/Snapshot.h"

class BfmeSnapshotBase
{
public:
	virtual ~BfmeSnapshotBase() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();					// retail 0x009A1A30
	virtual ~SubsystemInterface();			// retail 0x001B4E74

private:
	int m_bfmeState;
};

class GODupBase : public BfmeSnapshotBase, public SubsystemInterface
{
public:
	GODupBase();
	virtual ~GODupBase();
};

// ??0GODupBase@@QAE@XZ
GODupBase::GODupBase()
{
}

// ??1GODupBase@@UAE@XZ, retail 0x003067D2: both vtables, ~SubsystemInterface
// on this + 4, then the Snapshot vtable inline. Its scalar deleting
// destructor 0x0030680E is slot 0 of table 0x00807D2C, and the constructor's
// EH handler 0x00779B3E serves this frame too.
GODupBase::~GODupBase()
{
}
