// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0CrateCollideModuleData@@QAE@XZ, retail 0x004BC657, 107 bytes.
// The module-data half of CrateCollide: vtable immediate 0x00C5A660 modelled
// as an explicit first member (DemoTrapUpdateModuleDataCtor precedent, so no
// vtable is emitted and no dtor row is owed), an uninitialised word at +0x04
// retail never stores, the RequiredKindOf set at +0x08 plus the
// ForbiddenKindOf set at +0x24 both constructed through the shared memset
// helper pinned at 0x24C7B3 (Rva0024C7B3Member precedent), the owner and
// pickup flags at +0x40/+0x41/+0x42, PickupScience at +0x44 defaulting to -1,
// the ExecuteFX slot at +0x48, the ExecuteAnimation string at +0x4C copied
// from a zeroed static through the AsciiString copy ctor pinned at 0x365F0,
// the ExecuteAnimationTime and ZRise reals at +0x50/+0x54 defaulting to 0.0f
// and ExecuteAnimationFades at +0x58 defaulting to true. Field identity is
// retail's own INI table at 0x00C5A7A8 (landed buildFieldParse row) joined to
// the BFME1 field_names vote (PickupScience is CrateCollideModuleData's
// member) and the Zero Hour CrateCollide donor family. Everything lives in
// the init list in declaration order: init-list (-1) emits the leading or
// form under /O1 and the scheduler keeps the retail store order. The empty
// UpdateModuleData base (inline-empty ctor plus declared-only dtor, Topple
// precedent) is load-bearing for the EH frame: it produces the prolog plus
// the single state-0 store with no transitions; a standalone class compiles
// frameless here. The string global is an extern (DIR32-masked, no pin).

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member();

private:
	unsigned char m_data[0x1C];
};

#include "ascii_string.h"


// The retail table at RVA 0x0085A660: 31 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GUpgradeModuleData@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?name@Rva00065212Named@@QBEPBDXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
}
extern const void *const g_00C5A660[31] = {
	(const void *)&__identifier("??_GUpgradeModuleData@@UAEPAXI@Z"), // slot 0 0x004BC7E2
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?name@Rva00065212Named@@QBEPBDXZ"), // slot 2 0x00065212
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 3 0x0047A69C
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 4 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 5 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 6 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 7 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 8 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 9 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 11 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 12 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 13 0x0047A699
	(const void *)&__identifier("?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z"), // slot 14 0x000B69A1
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 15 0x0047A699
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 16 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 17 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 18 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 19 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 20 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 21 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 22 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 23 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 24 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 25 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 26 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 27 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 28 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 29 0x000D43D0
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // slot 30 0x0050B5C6
};

class UpdateModuleData
{
public:
	__declspec(dllimport) __forceinline UpdateModuleData() {}
	~UpdateModuleData();

private:
};

class CrateCollideModuleData : public UpdateModuleData
{
public:
	CrateCollideModuleData();

private:
	const void *m_vtable;				// +0x00
	unsigned int m_unused04;			// +0x04
	Rva0024C7B3Member m_requiredKindOf;		// +0x08
	Rva0024C7B3Member m_forbiddenKindOf;		// +0x24
	bool m_forbidOwnerPlayer;			// +0x40
	bool m_buildingPickup;				// +0x41
	bool m_humanOnly;				// +0x42
	int m_pickupScience;				// +0x44
	void *m_executeFX;				// +0x48
	AsciiString m_executeAnimation;			// +0x4C
	float m_executeAnimationTime;			// +0x50
	float m_executeAnimationZRise;			// +0x54
	bool m_executeAnimationFades;			// +0x58
};

CrateCollideModuleData::CrateCollideModuleData()
	: m_vtable((const void *)g_00C5A660)
	, m_forbidOwnerPlayer(false)
	, m_buildingPickup(false)
	, m_humanOnly(false)
	, m_pickupScience(-1)
	, m_executeFX(0)
	, m_executeAnimation(AsciiString::TheEmptyString)
	, m_executeAnimationTime(0.0f)
	, m_executeAnimationZRise(0.0f)
	, m_executeAnimationFades(true)
{
}
