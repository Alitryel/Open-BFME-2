// ??0AutoAbilityBehaviorModuleData@@QAE@XZ
// partial score=0.93 date=2026-10-14
// ??0AutoAbilityBehaviorModuleData@@QAE@XZ
// partial score=0.97 date=2026-10-04
// ??0AutoAbilityBehaviorModuleData@@QAE@XZ
// cl: /O1 /arch:SSE /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0AutoAbilityBehaviorModuleData@@QAE@XZ, retail 0x0045A2E7, 135 bytes.
// Auto-acquire behavior data over own INI table 0x00C41690 (SpecialAbility,
// MaxScanRange, MinScanRange, WorkingRadius, StartsActive,
// BaseMaxRangeFromStartPos, AdjustAttackMeleePosition, Query, AllowSelf,
// IdleTimeSeconds; offsets read from the retail table). MaxScanRange at +8,
// MinScanRange at +0xC, WorkingRadius at +0x10 and IdleTimeSeconds at +0x14
// null as floats; SpecialAbility at +0x18 is a name string (inline null
// AsciiString ctor, external dtor via the rowed 0x36410 pin, first EH
// state); ForbiddenStatus at +0x1C is a 128-bit status mask whose inline
// ctor resets it through the rowed bitset<128>::reset at 0x0024CA24 (plus
// a redundant 16-byte memset in the body, AttachUpdate precedent) with an
// opaque TU-local dtor for the second EH state; the six 8-byte Query
// entries at +0x2C build through the rowed ehvec helper at 0x00629512 with
// the rowed element ctor 0x0045A1D9 and dtor 0x0045A226; StartsActive,
// BaseMaxRangeFromStartPos and AdjustAttackMeleePosition null while
// AllowSelf at +0x5F is true. Size 0x60 matches the ModuleData factory at
// 0x0024AFE5 news. Row supersedes the ctor pin.
//
// THE MEMSET MUST BE CALLED AS ?ji_006291ae@@YAXXZ. The rowed 0x006291AE is
// not a memset body but the 6-byte import thunk `jmp ds:[0xBBA6C0]`, so it is
// only reachable through that mangled name. A TU-local `void
// Rva006291AEMemset(void*,int,unsigned)` -- what the banked attempt declared
// -- leaves the call site UNRESOLVED: the resolver has no row or pin for that
// name, so the call target stays a self-relative placeholder (the disassembly
// reads `call 0x45a35a`, the next instruction) and the whole tail
// desynchronises. With the ji_ spelling plus the alternatename pragma the
// relocation binds to 0x006291AE and everything from `xor ebx,ebx` through
// the epilogue matches retail byte for byte.
//
// ORDER LAW (proven by three failed shapes): retail calls the
// ForbiddenStatus reset BEFORE the Query ehvec, but a member array always
// ehvecs in the init-list ahead of every body statement, so the reset
// cannot be a body statement. It is the body of the mask member's own
// inline ctor, emitted transparently between the SpecialAbility init and
// the array ehvec. The Query element ctor and dtor stay declared-only:
// twin's init at 0x45A1D9 is the element ctor under its construction name
// and the 0x45A226 thunk is its dtor, so the TU references both through the
// ledger rows and the elements stay opaque exactly like the original TU saw
// them; defining them locally over-tracks the array into a third EH state.
// Array placement new is NOT a substitute: this toolchain emits a count
// cookie plus a null-check guard plus a third EH state for it. The empty-dtor
// mask is NOT a substitute either: only members with real (non-empty) dtors
// earn EH states, and the funclet table proves the two tracked entries are
// SpecialAbility and ForbiddenStatus with the array unwinding inside ehvec.
//
// The four null floats belong in the BODY, not the init list: in the init
// list MSVC6 hoists their `xorps xmm0,xmm0` above the register pushes and the
// first diff moves from +0x0F to +0x0B (58/135 exact). As body assignments
// they land after `mov esi,ecx` where retail has them (62/135).
//
// ORDER LAW (proved by eleven bodies): retail's memset argument pushes
// (`push 0x10; push ebx; push edi`) are emitted BEFORE the three byte stores
// at +0x5C/+0x5D/+0x5E and the `mov BYTE PTR [esi+0x5F],0x1`, with the four
// float stores interleaved between the second and third pushes. MSVC6
// schedules those seven scalar stores plus the four movss as ONE unsplittable
// block, so no statement order, no volatile-qualified write and no flag set
// reproduces that interleave.

#include <bitset>
#include <cstring>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	char *m_data;
};

class ForbiddenStatusMask
{
public:
	ForbiddenStatusMask()
	{
		((_STL::bitset<128> *)m_words)->reset();
	}

private:
	unsigned long m_words[4];
};

class Rva003623E5Member
{
public:
	void construct();
};

// The Query element must be the ROWED AutoAbilityQueryEntry so that the ehvec
// constructor/destructor arguments resolve to the ledger's real addresses
// 0x0045A1D9 and 0x0045A226; a private `struct` with the same layout leaves
// both pointers as unresolved garbage immediates.
class AutoAbilityQueryEntry
{
public:
	AutoAbilityQueryEntry();
	~AutoAbilityQueryEntry();

private:
	int m_state;
	Rva003623E5Member m_filter;
};

class AutoAbilityBehaviorModuleData
{
public:
	AutoAbilityBehaviorModuleData();

private:
	const void *m_vtable; // +0
	int m_gap04; // +4
	float m_maxScanRange; // +8, MaxScanRange
	float m_minScanRange; // +0xC, MinScanRange
	float m_workingRadius; // +0x10, WorkingRadius
	float m_idleTimeSeconds; // +0x14, IdleTimeSeconds
	AsciiString m_specialAbility; // +0x18, SpecialAbility
	ForbiddenStatusMask m_forbiddenStatus; // +0x1C, ForbiddenStatus
	AutoAbilityQueryEntry m_query[6]; // +0x2C, Query
	bool m_startsActive; // +0x5C, StartsActive
	bool m_baseMaxRangeFromStartPos; // +0x5D, BaseMaxRangeFromStartPos
	bool m_adjustAttackMeleePosition; // +0x5E, AdjustAttackMeleePosition
	bool m_allowSelf; // +0x5F, AllowSelf
};

// ??0AutoAbilityBehaviorModuleData@@QAE@XZ @0x0045A2E7
AutoAbilityBehaviorModuleData::AutoAbilityBehaviorModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C41568))
	, m_maxScanRange(0.0f)
	, m_minScanRange(0.0f)
	, m_workingRadius(0.0f)
	, m_idleTimeSeconds(0.0f)
	, m_specialAbility()
	, m_forbiddenStatus()
{
	m_startsActive = false;
	m_baseMaxRangeFromStartPos = false;
	m_adjustAttackMeleePosition = false;
	m_allowSelf = true;
	// Retail keeps &mask live in EDI from its birth at +0x4F to the second
	// ehvec call at +0x6A, so it saves EDI in the prolog. Naming the address
	// before the call is what widens its live range across the whole tail;
	// left implicit the register dies inside memset's arguments.
	ForbiddenStatusMask *mask = &m_forbiddenStatus;
	ji_006291ae(mask, 0, sizeof(ForbiddenStatusMask));
}