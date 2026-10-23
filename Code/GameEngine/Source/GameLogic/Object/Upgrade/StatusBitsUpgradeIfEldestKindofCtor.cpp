// cl: /DNDEBUG /MD /GX
//
// ??0StatusBitsUpgradeIfEldestKindof@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004B4A32, 84 bytes. Behavior-side ctor (rowed instance factory
// 0x250076 news 0x20 with this pinned 2-arg ctor as its sole raw caller
// at 0x25009D).
//
// Shape follows the rowed StatusBitsUpgrade sibling over 0x4B4960: EH
// prologue via /GX plus the declared-only base dtor, an eldest-frame cache
// member at +0x1C refreshed from the GameLogic frame through its own
// trivial method (sole-called helper 0x485975, pinned here under a
// descriptive name; the +0x40 field is proven to be the frame by the rowed
// getFrame pattern), then the vtable group reinstalling the primary slot
// and the +0x0C/+0x10/+0x18 secondaries. The novtable views install the
// explicit retail slot arrays without emitting compiler-generated tables.

// The retail table at RVA 0x00857ADC: 12 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GStatusBitsUpgradeIfEldestKindof@@UAEPAXI@Z")();
void __identifier("?loadPostProcess@Rva00497805@@MAEXXZ")();
void __identifier("?Rva004B4A86Get@@YAHXZ")();
void __identifier("?xfer@StatusBitsUpgradeIfEldestKindof@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@StatusBitsUpgradeIfEldestKindof@@UBE?AW4NameKeyType@@XZ")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
}
extern "C" const void *const vtbl_00C57ADC[12] = {
	(const void *)&__identifier("??_GStatusBitsUpgradeIfEldestKindof@@UAEPAXI@Z"), // slot 0 0x004B4ADE
	(const void *)&__identifier("?loadPostProcess@Rva00497805@@MAEXXZ"), // slot 1 0x00497805
	(const void *)&__identifier("?Rva004B4A86Get@@YAHXZ"), // slot 2 0x004B4A86
	(const void *)&__identifier("?xfer@StatusBitsUpgradeIfEldestKindof@@MAEXPAVXfer@@@Z"), // slot 3 0x004B4B7C
	(const void *)&__identifier("?getModuleNameKey@StatusBitsUpgradeIfEldestKindof@@UBE?AW4NameKeyType@@XZ"), // slot 4 0x004B4A99
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 5 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 6 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 7 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 8 0x000B3FD0
	(const void *)&__identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z"), // slot 9 0x0050B238
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 10 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 11 0x000D43D0
};
// Secondary interface tables retain every retail slot and its rowed target.
extern "C" {
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?attemptUpgrade@UpgradeMux@@UAE_NABV?$BitFlags@$0IA@@@@Z")();
void __identifier("?forceRefreshUpgrade@UpgradeMux@@UAEXXZ")();
void __identifier("?get@Rva0045875FLeaNegSbbField@@QBEHXZ")();
void __identifier("?get@Rva00460AE2ByteChase32Field@@QBEEXZ")();
void __identifier("?get@Rva004B4A8CLeaNegSbbField@@QBEHXZ")();
void __identifier("?getDie@DieModule@@UAEPAVDieModuleInterface@@XZ")();
void __identifier("?getUpgradeActivationMasks@UpgradeModule@@MBEXAAUUpgradeMaskType@@0@Z")();
void __identifier("?isAlreadyUpgraded@UpgradeMux@@UBE_NXZ")();
void __identifier("?performUpgradeFX@UpgradeModule@@MAEXXZ")();
void __identifier("?requiresAllActivationUpgrades@UpgradeModule@@MBE_NXZ")();
void __identifier("?requiresAllConflictingUpgrades@UpgradeModule@@MBE_NXZ")();
void __identifier("?rva00452354@UpgradeMux@@QAEX_N@Z")();
void __identifier("?rva004CE2B0@StatusBitsUpgradeIfEldestKindof@@UAE_NPAVRva00406F9C@@@Z")();
void __identifier("?rva004CE4B0@UpgradeModule@@UAE_NPAVRva00406F9C@@@Z")();
void __identifier("?upgradeImplementation@StatusBitsUpgrade@@MAEXXZ")();
void __identifier("?upgradeMuxXfer@UpgradeMux@@MAEXPAVXfer@@@Z")();
void __identifier("?upgradeRemovalImplementation@StatusBitsUpgrade@@MAEXXZ")();
}
extern "C" const void *const vtbl_00C579D8[18] = {
	(const void *)&__identifier("?isAlreadyUpgraded@UpgradeMux@@UBE_NXZ"),
	(const void *)&__identifier("?attemptUpgrade@UpgradeMux@@UAE_NABV?$BitFlags@$0IA@@@@Z"),
	(const void *)&__identifier("?rva004CE2B0@StatusBitsUpgradeIfEldestKindof@@UAE_NPAVRva00406F9C@@@Z"),
	(const void *)&__identifier("?rva004CE4B0@UpgradeModule@@UAE_NPAVRva00406F9C@@@Z"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?forceRefreshUpgrade@UpgradeMux@@UAEXXZ"),
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"),
	(const void *)&__identifier("?get@Rva00460AE2ByteChase32Field@@QBEEXZ"),
	(const void *)&__identifier("?upgradeRemovalImplementation@StatusBitsUpgrade@@MAEXXZ"),
	(const void *)&__identifier("?rva00452354@UpgradeMux@@QAEX_N@Z"),
	(const void *)&__identifier("?upgradeImplementation@StatusBitsUpgrade@@MAEXXZ"),
	(const void *)&__identifier("?getUpgradeActivationMasks@UpgradeModule@@MBEXAAUUpgradeMaskType@@0@Z"),
	(const void *)&__identifier("?performUpgradeFX@UpgradeModule@@MAEXXZ"),
	(const void *)&__identifier("?requiresAllActivationUpgrades@UpgradeModule@@MBE_NXZ"),
	(const void *)&__identifier("?requiresAllConflictingUpgrades@UpgradeModule@@MBE_NXZ"),
	(const void *)&__identifier("?performUpgradeFX@UpgradeModule@@MAEXXZ"),
	(const void *)&__identifier("?upgradeMuxXfer@UpgradeMux@@MAEXPAVXfer@@@Z"),
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"),
};
extern "C" const void *const vtbl_00C57A20[47] = {
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?get@Rva0045875FLeaNegSbbField@@QBEHXZ"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?getDie@DieModule@@UAEPAVDieModuleInterface@@XZ"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?get@Rva004B4A8CLeaNegSbbField@@QBEHXZ"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"),
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
};
extern "C" const void *const vtbl_00C58790[];  // folded, 55 classes; via ??_7AODHordeContain@@6BIface2C@@@
#pragma comment(linker, "/alternatename:_vtbl_00C58790=??_7AODHordeContain@@6BIface2C@@@")

class Thing;
class ModuleData;

class __declspec(novtable) StatusBitsUpgrade
{
public:
	StatusBitsUpgrade(Thing *thing, const ModuleData *moduleData);
	virtual ~StatusBitsUpgrade();

protected:
	unsigned char m_pad04[0x08];
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned char m_pad14[0x04];
	const void *m_slot18;
};

struct StatusBitsEldestFrame
{
	StatusBitsEldestFrame *cacheGameLogicFrame(void);

private:
	int m_cachedFrame;
};

class __declspec(novtable) StatusBitsUpgradeIfEldestKindof : public StatusBitsUpgrade
{
public:
	StatusBitsUpgradeIfEldestKindof(Thing *thing, const ModuleData *moduleData);

private:
	StatusBitsEldestFrame m_eldestFrame;
};

// ??0StatusBitsUpgradeIfEldestKindof@@QAE@PAVThing@@PBVModuleData@@@Z
StatusBitsUpgradeIfEldestKindof::StatusBitsUpgradeIfEldestKindof(Thing *thing, const ModuleData *moduleData)
	: StatusBitsUpgrade(thing, moduleData)
{
	m_eldestFrame.cacheGameLogicFrame();
	int *vtab = (int *)this;
	*vtab = ((unsigned int)vtbl_00C57ADC);
	int *sec0C = (int *)&m_secondary0C;
	*sec0C = (int)vtbl_00C57A20;
	int *sec10 = (int *)&m_secondary10;
	*sec10 = (int)vtbl_00C579D8;
	int *slot18 = (int *)&m_slot18;
	*slot18 = (int)((unsigned int)vtbl_00C58790);
}
