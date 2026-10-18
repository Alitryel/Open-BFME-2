// cl: /DNDEBUG /MD /GX
//
// ??0RandomSoundSelectorClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x004CBC2B, 124 bytes. Behavior-side ctor over the rowed opaque
// intermediate base 0x252B68 (0x0C: vtable + 8 pad, DrawableModule-derived):
// two-phase +0x0C slot (BE2B78 first via sourced-before address-take,
// C5F368 second) plus vtable C5F378 plus float at +0x10 via
// GetGameClientRandomValueReal(0.0f, 1.0f, file, 0x62) (rowed 0x234111,
// x87 fld1/fldz + fstp, no /arch:SSE) plus conditional int at +0x14 via
// the global holder at 0xDFE77C (slot1F, int return; ScriptEngine_setFrame
// precedent) else zero. The rowed instance factory 0x252D2A (news 0x18)
// is the sole raw caller. Row supersedes the ctor pin.

extern "C" const void *const vtbl_00BE2B78[];  // folded, 9 classes; via ??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BE2B78=??_7ClearanceTestingSlowDeathBehaviorIface5@@6B@")
// The retail table at RVA 0x0085F378: 19 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva00252B68@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Rva004CBCA7Get@@YAHXZ")();
void __identifier("?xfer@RandomSoundSelectorClientBehavior@@MAEXPAVXfer@@@Z")();
void __identifier("?rva0004CBCAD@RandomSoundSelectorClientBehavior@@SA?AW4NameKeyType@@XZ")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?Set_Animation@RenderObjClass@@UAEXPAVHAnimClass@@MH@Z")();
void __identifier("?get@Rva000CA841MovLeaNegSbbField@@QBEHXZ")();
}
extern const void *const g_00C5F378[19] = {
	(const void *)&__identifier("??_GRva00252B68@@UAEPAXI@Z"), // slot 0 0x00254C2F
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?Rva004CBCA7Get@@YAHXZ"), // slot 2 0x004CBCA7
	(const void *)&__identifier("?xfer@RandomSoundSelectorClientBehavior@@MAEXPAVXfer@@@Z"), // slot 3 0x004CBD7C
	(const void *)&__identifier("?rva0004CBCAD@RandomSoundSelectorClientBehavior@@SA?AW4NameKeyType@@XZ"), // slot 4 0x004CBCAD
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 5 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 6 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 7 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 8 0x000B3FD0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 9 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 10 0x000D43D0
	(const void *)&__identifier("?Set_Animation@RenderObjClass@@UAEXPAVHAnimClass@@MH@Z"), // slot 11 0x000D1407
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 12 0x000D43D0
	(const void *)&__identifier("?get@Rva000CA841MovLeaNegSbbField@@QBEHXZ"), // slot 13 0x000CA841
	(const void *)&__identifier("?get@Rva000CA841MovLeaNegSbbField@@QBEHXZ"), // slot 14 0x000CA841
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 15 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 16 0x000D43D0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 17 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 18 0x000B3FD0
};
// The retail table at RVA 0x0085F368: 3 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("?rva004CBDCF@Rva004CBDCF@@QAE_NHPAURva002C99FB@@@Z")();
void __identifier("?rva004CBE31@Rva004CBE31@@QAE_NABVAsciiString@@PAURva002C99FB@@@Z")();
void __identifier("?getSelectedValue@RandomSoundSelectorClientBehavior@@UAE_NPAI@Z")();
}
extern const void *const g_00C5F368[3] = {
	(const void *)&__identifier("?rva004CBDCF@Rva004CBDCF@@QAE_NHPAURva002C99FB@@@Z"), // slot 0 0x004CBDCF
	(const void *)&__identifier("?rva004CBE31@Rva004CBE31@@QAE_NABVAsciiString@@PAURva002C99FB@@@Z"), // slot 1 0x004CBE31
	(const void *)&__identifier("?getSelectedValue@RandomSoundSelectorClientBehavior@@UAE_NPAI@Z"), // slot 2 0x004CBD44
};

class ClientFrameSubsystem; extern class GameClient *TheGameClient;

class Thing;
class ModuleData;

typedef float Real;
Real GetGameClientRandomValueReal(Real lo, Real hi, char *file, int line);

class Rva00252B68
{
public:
	Rva00252B68(Thing *thing, const ModuleData *moduleData);
	~Rva00252B68();

protected:
	const void *m_vtable;
	unsigned char m_pad[0x0C - 4];
};

class Rva00DFE77CHolder
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual int slot1F();
};

#define TheRva00DFE77C (*(Rva00DFE77CHolder **)&TheGameClient)

class RandomSoundSelectorClientBehavior : public Rva00252B68
{
public:
	RandomSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData);

private:
	const void *m_0C;
	float m_10;
	int m_14;
};

// ??0RandomSoundSelectorClientBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x004CBC2B
RandomSoundSelectorClientBehavior::RandomSoundSelectorClientBehavior(Thing *thing, const ModuleData *moduleData)
	: Rva00252B68(thing, moduleData)
{
	int *slot0C = (int *)&m_0C;
	*slot0C = (int)((unsigned int)vtbl_00BE2B78);
	m_vtable = g_00C5F378;
	m_0C = g_00C5F368;
	m_10 = GetGameClientRandomValueReal(0.0f, 1.0f, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\Drawable\\Behavior\\RandomSoundSelectorClientBehavior.cpp", 0x62);
	Rva00DFE77CHolder *holder = TheRva00DFE77C;
	if (holder != 0)
		m_14 = holder->slot1F();
	else
		m_14 = 0;
}
