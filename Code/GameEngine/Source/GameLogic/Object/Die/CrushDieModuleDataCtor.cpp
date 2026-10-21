// cl: /O1 /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0CrushDieModuleData@@QAE@XZ, retail 0x002539B3, 82 bytes.
// CrushDie ModuleData default ctor over the pinned SEH intermediate base
// (??0DestroyDieModuleData@@QAE@XZ at 0x253510, shared with the Die family). The
// virtual base (KeepObjectDie/CreateObjectDieModuleDataCtor precedent)
// carries the vptr the compiler installs itself right after the base call;
// the DIR32 slot is patched from retail like any other vtable install, so
// no ??_7 pin is owed. The four crush-sound references at +0x38 (BFME1
// donor field m_crushSounds) are built through the array-construction helper
// at 0x629512 (existing ??_L fold pins). Retail pushes element size 4,
// count 4, nulling ctor VA 0x726BE6 and counted-handle dtor VA 0x50F149.
// The existing Rva0010F149Handle view supplies those exact callback ABIs;
// its declaration-only members preserve the native EH frame. The original
// handle type remains unidentified. The four crush-sound percent slots
// +0x48 take 100 through the donor loop below, unrolled to stosd form.
// Size 0x58 (0x38 base + 16-byte sounds + 16-byte percents) matches the
// 0x253A27 factory news in the rowed CrushDieModuleDataFriendNew TU.
// Identity: ModuleFactory registers "CrushDie" to factory 0x253A27 which
// sole-calls this ctor (pin 3628, superseded by this row), plus the rowed
// crush-sound parse proc 0x253A05.

// Retail passes the nulling constructor at 0x00326BE6 and the counted-handle
// destructor at 0x0010F149 to the array helper. These are the existing handle
// providers; they do not construct or destroy a full AudioEventRTS object.
struct Rva0010F149Handle
{
	Rva0010F149Handle();
	~Rva0010F149Handle();
	void *m_target;
};

class Xfer;

#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

// The Die-family intermediate adds no destructible members: its dtor is the
// inline Snapshot-vptr restore CreateCrateDieModuleDataDtor.cpp also emits
// (retail 0x0049B47C), not a strong definition of this unit's own.
class __declspec(novtable) DestroyDieModuleData : public Snapshot
{
public:
	DestroyDieModuleData();
	virtual ~DestroyDieModuleData() {}

private:
	unsigned char m_pad[0x38 - 4];
};

enum
{
	CRUSH_COUNT = 4,
};

class CrushDieModuleData : public DestroyDieModuleData
{
public:
	CrushDieModuleData();

private:
	Rva0010F149Handle m_crushSounds[CRUSH_COUNT]; // +0x38
	int m_crushSoundPercent[CRUSH_COUNT]; // +0x48
};

// ??0CrushDieModuleData@@QAE@XZ @0x2539B3
inline CrushDieModuleData::CrushDieModuleData()
{
	for (int i = 0; i < CRUSH_COUNT; ++i)
		m_crushSoundPercent[i] = 100;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeCrushDieModuleDataInlineAnchor@@YAXPAVCrushDieModuleData@@@Z absent-from-retail
void _bfmeCrushDieModuleDataInlineAnchor(CrushDieModuleData *crushDieModuleData)
{
    crushDieModuleData->CrushDieModuleData::CrushDieModuleData();
}
#pragma inline_depth()
