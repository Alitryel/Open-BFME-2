// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD /Ireference/shims/moduledata
//
// ??0BuildingBehaviorModuleData@@QAE@XZ, retail 0x00456489, 65 bytes.
// ModuleData default ctor: vtable 0xC40798 plus a four-element window-name
// member at +0x08 built in place through the compiler's eh vector
// constructor iterator (rowed ??_L at 0x629512). The table at 0xC40748
// (NightWindowName@8, FireWindowName@0x14, GlowWindowName@0x20,
// FireName@0x2C) proves four 12-byte elements; the factory at 0x24ABAF
// news 0x38, so the layout is vtable plus a 4-byte gap plus the array.
// The element setup/teardown addresses the helper takes travel as DIR32
// slots the patcher copies from retail (CrushDieModuleDataCtor precedent),
// so element linkage stays local here. Each entry leads with its window
// name (AsciiString with inline null init and declared teardown resolving
// through the folded 0x36410 pin, Topple precedent); the trailing 8 bytes
// are opaque. The opaque member teardown is also what arms the single EH
// state: with fully-defined elements the toolchain proves non-throwing
// and drops the retail frame. Member-array setup hoists above the explicit
// vtable store while the helper call stays below it, reproducing the retail
// order. Identity: ModuleFactory registers "BuildingBehavior" to factory
// 0x24ABAF which sole-calls this ctor; the rowed pool key at 0x4561C1 ends
// where the rowed parse proc at 0x456206 begins.

// TU-local string with inline null init; the declared teardown resolves
// through the existing folded AsciiString pin at 0x36410.
#include "ascii_string.h"

// A window-name entry: 12 bytes (retail element size).
class BuildingWindowName
{
public:
	BuildingWindowName() {}
	~BuildingWindowName() {}

private:
	AsciiString m_name; // +0x00, the parsed window name
	unsigned char m_pad[8]; // +0x04, opaque trailing bytes
};

extern "C" const void *const vtbl_00C40798[];  // ??_7BuildingBehaviorModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C40798=??_7BuildingBehaviorModuleData@@6B@")

// Retail's state-0 unwind funclet jumps to 0x0049B47C, the ModuleData-family
// dtor fold that restores the Snapshot vptr 0x00BBB554; the base dtor is
// that reset (WallHubBehaviorModuleDataCtor precedent).
#include "Common/Snapshot.h"

// Empty base (inline-empty ctor plus non-trivial dtor): load-bearing for
// the EH state machine, advancing the state to 0 with no emitted code so
// the array construction below is bracketed exactly as retail (Topple
// precedent).
class BuildingBehaviorModuleDataBase
{
public:
	BuildingBehaviorModuleDataBase() {}
	~BuildingBehaviorModuleDataBase() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }

private:
};

class BuildingBehaviorModuleData : public BuildingBehaviorModuleDataBase
{
public:
	BuildingBehaviorModuleData();

private:
	void *m_vtable; // +0x00, explicit store (no virtuals declared)
	int m_unused04; // +0x04, unstored gap (DemoTrap precedent)
	BuildingWindowName m_windows[4]; // +0x08
};

// ??0BuildingBehaviorModuleData@@QAE@XZ @0x00456489
BuildingBehaviorModuleData::BuildingBehaviorModuleData()
	: m_vtable(reinterpret_cast<void *>(((unsigned int)vtbl_00C40798)))
{
}
