// cl: /DNDEBUG /MD
//
// ??0W3DSailModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x000D078F,
// 60 bytes. Draw-side ctor completing the W3DSailModelDraw file-unit (name
// getter rowed at 0xD0810 returning the W3DSailModelDraw literal; pool key
// rowed at 0xD07CB; ModuleData factory rowed at 0x64FD3; behavior instance
// factory rowed at 0x64F98 with this ctor as sole raw caller).
//
// Shape: frameless single-base ctor over the W3DScriptedModelDraw base
// 0xC0DD8 with a float zero and a flag zero around the derived vtable slots
// stored explicitly via pointer casts (W3DTreeDraw precedent: no virtuals are
// declared anywhere so no vtable is emitted here; the immediates are
// DIR32-masked in comparison). Zero new pins (base resolves via the existing
// W3DScriptedModelDraw pin). Row supersedes the ctor pin.

extern "C" const unsigned char __identifier("??_7Rva000CA119@@6BRva000CA119_B2@@@")[];
extern "C" const unsigned char __identifier("??_7W3DTankDraw@@6BDrawInterfaceA@@@")[];

extern "C" const unsigned char __identifier("??_7W3DSailModelDraw@@6B@")[];

class Thing;
class ModuleData;

class W3DScriptedModelDraw
{
public:
	W3DScriptedModelDraw(Thing *thing, const ModuleData *moduleData);

private:
	unsigned char m_pad[0x2E8];
};

class W3DSailModelDraw : public W3DScriptedModelDraw
{
public:
	W3DSailModelDraw(Thing *thing, const ModuleData *moduleData);

private:
	float m_2E8;
	bool m_flag2EC;
};

// ??0W3DSailModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0xD078F
W3DSailModelDraw::W3DSailModelDraw(Thing *thing, const ModuleData *moduleData) :
	W3DScriptedModelDraw(thing, moduleData)
{
	*(unsigned int *)this = (unsigned int)__identifier("??_7W3DSailModelDraw@@6B@");
	*(unsigned int *)((char *)this + 0x0C) = ((unsigned int)__identifier("??_7W3DTankDraw@@6BDrawInterfaceA@@@"));
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)__identifier("??_7Rva000CA119@@6BRva000CA119_B2@@@"));
	m_2E8 = 0.0f;
	m_flag2EC = false;
}
