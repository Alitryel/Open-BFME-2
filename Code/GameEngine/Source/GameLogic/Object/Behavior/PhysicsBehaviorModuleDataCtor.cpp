// cl: /GX /DNDEBUG /MD

// PhysicsBehaviorModuleData default constructor @0x390119 (176B). Identity:
// the factory 0x24E774 (landed PhysicsBehaviorModuleDataFriendNew.cpp) news
// 0x5C and calls this ctor as its sole raw caller; the INI table at 0x00C19DE8
// (landed buildFieldParse row) names every member and offset below. Vtable
// 0x0084ED70 pinned as ??_7PhysicsBehaviorModuleData@@6B@.
//
// Every constant default sits in the member initializer list, which MSVC
// emits in declaration order; that interleaving is what keeps 1.3, 0.33, 0.66
// and 5.0 live together from the entry (xmm0-xmm3) and lets the vtable store
// sink below the zeroing. The three shock times are body assignments from the
// int global at 0x009BA4E4 (BFME 2's logic frame rate, 5): one second, two
// seconds, one second. Earlier attempts wrote every store in the body in retail
// order and pinned it with volatile members, which left 0.33 on demand in xmm0.
// The +0x28 slot has no INI field and keeps an address-derived name.

extern int BfmeLogicFramesPerSecond;

// The retail table at RVA 0x0084ED70: 31 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRadarObject@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?name@Rva00065212Named@@QBEPBDXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
}
extern "C" const void *const vtbl_0084ED70[31] = {
	(const void *)&__identifier("??_GRadarObject@@UAEPAXI@Z"), // slot 0 0x004A10FD
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
};

class PhysicsBehaviorModuleData : public UpdateModuleData
{
public:
	PhysicsBehaviorModuleData();

private:
	const void *m_vtable; // +0x00, retail vtable 0x0084ED70
	unsigned int m_unused04;
	float m_firstHeight;
	float m_secondHeight;
	float m_firstPercentIndent;
	float m_secondPercentIndent;
	int m_shockStunnedTimeLow;
	int m_shockStunnedTimeHigh;
	int m_shockStandingTime;
	int m_bounceCount;
	float m_unk28;
	float m_bounceFirstHeight;
	float m_bounceSecondHeight;
	float m_bounceFirstPercentIndent;
	float m_bounceSecondPercentIndent;
	float m_curveFlattenMinDist;
	bool m_tumbleRandomly;
	bool m_orientToFlightPath;
	bool m_ignoreTerrainHeight;
	float m_firstPercentHeight;
	float m_secondPercentHeight;
	float m_gravityMult;
	void *m_groundHitFX;
	void *m_groundBounceFX;
	bool m_allowBouncing;
	bool m_killWhenRestingOnGround;
};

// ??0PhysicsBehaviorModuleData@@QAE@XZ @0x00390119
PhysicsBehaviorModuleData::PhysicsBehaviorModuleData() :
	m_vtable(reinterpret_cast<const void *>(((unsigned int)vtbl_0084ED70))),
	m_firstHeight(1.3f),
	m_secondHeight(1.3f),
	m_firstPercentIndent(0.33f),
	m_secondPercentIndent(0.66f),
	m_bounceCount(2),
	m_unk28(5.0f),
	m_bounceFirstHeight(1.3f),
	m_bounceSecondHeight(1.3f),
	m_bounceFirstPercentIndent(0.33f),
	m_bounceSecondPercentIndent(0.66f),
	m_curveFlattenMinDist(0.0f),
	m_tumbleRandomly(false),
	m_orientToFlightPath(false),
	m_ignoreTerrainHeight(false),
	m_firstPercentHeight(0.33f),
	m_secondPercentHeight(0.66f),
	m_gravityMult(1.0f),
	m_groundHitFX(0),
	m_groundBounceFX(0),
	m_allowBouncing(false),
	m_killWhenRestingOnGround(false)
{
	m_shockStunnedTimeLow = BfmeLogicFramesPerSecond;
	m_shockStunnedTimeHigh = 2 * BfmeLogicFramesPerSecond;
	m_shockStandingTime = BfmeLogicFramesPerSecond;
}
// ?BfmeLogicFramesPerSecond@@3HB: the global at VA 0xdba4e4 is ?BfmeLogicFramesPerSecond@@3HA.
