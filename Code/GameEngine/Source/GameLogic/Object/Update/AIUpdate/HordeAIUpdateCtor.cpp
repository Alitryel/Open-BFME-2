// cl: /DNDEBUG /MD /GX
// The shared headers declare these members with the access/virtual spelling
// the referring objects use; this TU emits the paired definition spelling.
// Same function, same address: bind the header spelling here.
extern "C" const void *const vtbl_00C50538[];  // folded, 2 classes; via ??_7HordeWorkerAIUpdate@@6BDBaseM1@@@
#pragma comment(linker, "/alternatename:_vtbl_00C50538=??_7HordeWorkerAIUpdate@@6BDBaseM1@@@")
extern "C" const void *const vtbl_00C52F88[];  // folded, 12 classes; via ??_7DeployStyleAIUpdate@@6BDBaseM4@@@
#pragma comment(linker, "/alternatename:_vtbl_00C52F88=??_7DeployStyleAIUpdate@@6BDBaseM4@@@")

#pragma comment(linker, "/alternatename:??1Rva0026E9BDBase@@UAE@XZ=??1Rva0026E9BDBase@@QAE@XZ")

//
// ??0HordeAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0049A7F3,
// 113 bytes. Behavior-side ctor completing the HordeAIUpdate file-unit
// (behavior instance factory rowed at 0x24E525 news 0x444 with this pinned
// 2-arg ctor as its caller at 0x24E54F; poolkey rowed at 0x49A67C; name
// getter rowed at 0x49A6C1).
//
// Shape follows AssaultTransport precedent over the same pinned opaque
// Transport base 0x26E9BD (thing plus data): volatile-first double store
// at +0x3E4 (C52EE8-then-C50868) plus the five behavior vtable slots
// (+0x00/+0x0C/+0x10/+0x20/+0x24 via explicit members) plus setWakeFrame
// awake-through-none tail. The class declares no virtuals of its own: the
// stores land from explicit members in body order with the setWakeFrame
// push/mov-ecx setup hoisted above them by the scheduler (WallUpgrade
// scheduling notes). /GX for the EH prologue plus the single mid-body
// state store; the defined-empty base dtor arms it while resolving its own
// unwind reference in-TU (PrisonDock precedent: a defined base dtor is what
// the linker needs). The pinned HordeWorkerAIUpdate ctor at 0x49AD15 calls
// this body at base position (Transport-pattern shared base, GarrisonContain
// precedent); this row documents the HordeAIUpdate side of the share. Zero
// other new pins (base ctor resolves via the existing Rva0026E9BDBase pin;
// setWakeFrame resolves via the new Rva0026E9BDBase-spelling alias pin at
// 0x44DF71 placed alongside).

extern "C" const void *const vtbl_00C50528[];  // ??_7Rva0049A64B@@6BRva0026E836_M3@@@
#pragma comment(linker, "/alternatename:_vtbl_00C50528=??_7Rva0049A64B@@6BRva0026E836_M3@@@")
extern "C" const void *const vtbl_00C5052C[];  // ??_7Rva0049A64B@@6BRva0026E836_B2@@@
#pragma comment(linker, "/alternatename:_vtbl_00C5052C=??_7Rva0049A64B@@6BRva0026E836_B2@@@")
extern "C" const void *const vtbl_00C505F8[];  // ??_7Rva0049A64B@@6BRva0026E836_Root@@@
#pragma comment(linker, "/alternatename:_vtbl_00C505F8=??_7Rva0049A64B@@6BRva0026E836_Root@@@")
extern "C" const void *const vtbl_00C52EE8[];  // ??_7DockUpdateInterface@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C52EE8=??_7DockUpdateInterface@@6B@")
// Retail VA C50868: 20-slot secondary-interface table. Both constructors
// install it at +3E4. The next table starts at C508B8 (worker +20 table).
// Entries bind directly to existing code owners; no new function aliases.
extern "C" {
void __identifier("?rva0049A880@Rva0049A64B@@UAE_NH@Z")();
void __identifier("?rva0049A8A1@Rva0049A64B@@UAE_NHPAUCoord3D@@PAH@Z")();
void __identifier("?rva0049A6D7@Rva0049A6D7@@QAE_NHHH@Z")();
void __identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z")();
void __identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z")();
void __identifier("?rva0049A8FA@Rva0049A64B@@UAEXHPAUCoord3D@@@Z")();
void __identifier("??_9@$BBE@AE")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?rva0049A973@HordeAIUpdate@@UAE_NPAVObject@@H@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const HordeAIUpdateInterface3E4Table[20] = {
	(const void *)&__identifier("?rva0049A880@Rva0049A64B@@UAE_NH@Z"), // 0 0x0089A880
	(const void *)&__identifier("?rva0049A8A1@Rva0049A64B@@UAE_NHPAUCoord3D@@PAH@Z"), // 1 0x0089A8A1
	(const void *)&__identifier("?rva0049A6D7@Rva0049A6D7@@QAE_NHHH@Z"), // 2 0x0089A6D7
	(const void *)&__identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z"), // 3 0x009CB9FA
	(const void *)&__identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z"), // 4 0x0090B5F1
	(const void *)&__identifier("?rva0049A8FA@Rva0049A64B@@UAEXHPAUCoord3D@@@Z"), // 5 0x0089A8FA
	(const void *)&__identifier("??_9@$BBE@AE"), // 6 0x009CB26F
	(const void *)&__identifier("??_9@$BBE@AE"), // 7 0x009CB26F
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // 8 0x0087A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // 9 0x0087A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // 10 0x0087A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // 11 0x0087A69C
	(const void *)&__identifier("?rva0049A973@HordeAIUpdate@@UAE_NPAVObject@@H@Z"), // 12 0x0089A973
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // 13 0x0087A69C
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // 14 0x0090B5C6
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // 15 0x0087A69C
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // 16 0x009CB9FF
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // 17 0x0087A69C
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // 18 0x0090B5C6
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // 19 0x0087A699
};

class Thing;
class ModuleData;
class Object;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class Rva0026E9BDBase
{
public:
	Rva0026E9BDBase(Thing *thing, const ModuleData *moduleData);
	~Rva0026E9BDBase() { m_p3E4 = 0; }

protected:
	void setWakeFrame(Object *object, unsigned int frame);

	const void *m_vtable;			// +0x00
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;			// +0x08
	const void *m_p0C;			// +0x0C
	const void *m_p10;			// +0x10
	unsigned char m_pad14[0x20 - 0x14];
	const void *m_p20;			// +0x20
	const void *m_p24;			// +0x24
	unsigned char m_pad28[0x3E4 - 0x28];
	const void *m_p3E4;			// +0x3E4
};

class HordeAIUpdate : public Rva0026E9BDBase
{
public:
	HordeAIUpdate(Thing *thing, const ModuleData *moduleData);
};

// ??0HordeAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0049A7F3
HordeAIUpdate::HordeAIUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva0026E9BDBase(thing, moduleData)
{
	*(const void * volatile *)&m_p3E4 = (const void *)((unsigned int)vtbl_00C52EE8);
	_ReadWriteBarrier();
	m_vtable = (const void *)((unsigned int)vtbl_00C505F8);
	m_p0C = (const void *)((unsigned int)vtbl_00C50538);
	m_p10 = (const void *)((unsigned int)vtbl_00C5052C);
	m_p20 = (const void *)((unsigned int)vtbl_00C50528);
	m_p24 = (const void *)((unsigned int)vtbl_00C52F88);
	m_p3E4 = (const void *)HordeAIUpdateInterface3E4Table;
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}
