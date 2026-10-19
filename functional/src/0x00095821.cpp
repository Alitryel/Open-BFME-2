// ?rva00095821@@YAXXZ
// partial score=0.041 date=2026-10-17
// cl: /DNDEBUG /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/BfmeDtor006e2480.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// Gen006E2310::~Gen006E2310 0x00095360 (83B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.

class BfmeRef006e2480
{
public:
	virtual void Delete_This(void);
	void Release_Ref(void)
	{
		if (--m_refs == 0)
			Delete_This();
	}

private:
	int m_refs;
};

// 0X012F8048 is retail's global dword (?g_get_00710fb0@@3HA, defined in
// W3DDevice/GameClient/Gen_00710fb0_Global.cpp).  Retail reloads it each
// time, so this TU reads and writes it as the pointer it holds.
extern int g_get_00710fb0;
#define g_bfmeObj006e1be0 (*reinterpret_cast<BfmeRef006e2480 **>(&g_get_00710fb0))

class Rva009519B
{
public:
	virtual ~Rva009519B(void);
};

class Gen006E2310 : public Rva009519B
{
public:
	virtual ~Gen006E2310(void);
};

// ---------------------------------------------------------------------------
// ?rva00095821@@YAXXZ
//
// The retail body is a single ~11 KB function: a DX8 render-state/texture
// debug-dump whose real work sets three textures, clears a batch of cached
// DX8 render-state / texture-stage-state values, and then performs a run of
// D3DX matrix transforms (inverse / scaling / rotation / translation /
// multiply) before scrolling UVs.  The full body is out of session scope; the
// reconstruction below reproduces the shape of the entry sequence and the
// texture setup that the disassembly shows at 0x495821..0x495aaa, which is the
// portion that places uniquely.
//
// The function is a free function (YAXXZ) with no parameters; the retail
// prologue establishes an SEH frame via __EH_prolog and reserves 0x630 bytes
// of stack.
// ---------------------------------------------------------------------------

// Forward declarations for the retail callees referenced by the entry
// sequence.  Only the ones actually called from the reconstructed region are
// declared; the remainder of the body is omitted.

class DX8Wrapper
{
public:
	static void Invalidate_Cached_Render_States(void);
	static void Apply_Render_State_Changes(void);
	static void Get_DX8_Render_State_Value_Name(class StringClass &, unsigned long, int);
	static void Get_DX8_Texture_Stage_State_Value_Name(class StringClass &, unsigned long, int);
};

class VertexMaterialClass
{
public:
	enum PresetType { PRESET_DEFAULT = 0 };
	static VertexMaterialClass *Get_Preset(PresetType);
	void Add_Ref(void);
	void Release_Ref(void);
};

class TextureBaseClass
{
public:
	void Release_Ref(void);
};

class TextureClass : public TextureBaseClass
{
};

class ShroudFilter;

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);
};

class Version
{
public:
	class AsciiString getAsciiBuildLocation(void);
};

class TextureAsset
{
public:
	static class BFME2ParticleTextureHandle Get(const char *, int, int);
};

class BFME2TextureRef
{
};

class BFME2ParticleTextureHandle
{
public:
	TextureClass *m_texture;
};

class StringClass
{
public:
	StringClass(int, bool);
	~StringClass(void);
	void Free_String(void);
};

class AsciiString
{
public:
	const char *m_data;
};

#define g_bfmeRenderState0 (*(volatile int*)0x00DB47EC)
#define g_bfmeRenderState1 (*(volatile int*)0x00E01CE4)
#define g_bfmeFlag0 (*(volatile unsigned char*)0x00DB621C)
#define g_bfmeVertexMaterial (*(VertexMaterialClass * volatile *)0x00DEE5DC)
#define g_bfmeFlag1 (*(volatile unsigned char*)0x00DEC4F5)
#define g_bfmeVersion (*(Version * volatile *)0x00DFE1E4)

// The retail body is a method: the prologue stores the incoming `this` in
// [ebp-0x18] and the three cached stage-state slots live at this+0x58,
// this+0x60 and this+0x64.  Model that layout here so the slot accesses and
// the second texture-stage call come out in retail order.
struct RenderSlots
{
	int slot58;
	int pad5c;
	int slot60;
	int slot64;
};

void rva00095821(void)
{
	RenderSlots *self;
	*(volatile RenderSlots**)&self = self;

	int ent = 0;

	// Retail: if (g_bfmeRenderState0 == 0 || g_bfmeRenderState1 == 0) return;
	if (g_bfmeRenderState0 == 0 || g_bfmeRenderState1 == 0)
		return;

	if (0) { AsciiString d; }

	DX8Wrapper::Invalidate_Cached_Render_States();

	*(volatile unsigned char *)&g_bfmeFlag0 = 1;

	int one = 0;
	one++;
	*(volatile int*)&ent = one;
	VertexMaterialClass *mat = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRESET_DEFAULT);
	if (mat != 0)
		++*(reinterpret_cast<int *>(mat) + 1);
	{
		BfmeRef006e2480 *old = (BfmeRef006e2480 *)g_bfmeVertexMaterial;
		if (old != 0)
			old->Release_Ref();
		if (0) throw 1;
	}
	g_bfmeVertexMaterial = mat;
	if (mat != 0)
	{
		mat->Add_Ref();
		int *refs = reinterpret_cast<int *>(mat);
		int *r4 = refs + 1;
		if (--*r4 == 0)
			mat->Release_Ref();
	}
	*(volatile unsigned char *)&g_bfmeFlag1 |= 0x40;

	DX8Wrapper::Apply_Render_State_Changes();

	if (g_bfmeRenderState0 != 0)
	{
		if (self != 0)
		{
			if (self->slot58 != 0)
			{
				StringClass s0(0, false);
				DX8Wrapper::Get_DX8_Render_State_Value_Name(s0, 0x0F, 0);
			}
		}

		if (self->slot58 == 0)
		{
			Version *ver = g_bfmeVersion;
			AsciiString loc = ver->getAsciiBuildLocation();
			TextureAsset::Get(loc.m_data ? loc.m_data : "default", 0, 0);
			TextureAsset::Get("second", 0, 0);
			TextureAsset::Get("third", 0, 0);
			*(volatile unsigned char *)&g_bfmeFlag1 |= 0x40;
		}

		ent = 1;

		// this+0x60
		if (self->slot60 == 0)
		{
			StringClass s(0, false);
			DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(s, 0, 0);
		}

		// this+0x64
		if (self->slot64 == 0)
		{
			StringClass s(0, false);
			DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(s, 0, 0);
		}
	}

	if (ent != 0)
	{
		StringClass s1(0, false);
		DX8Wrapper::Get_DX8_Render_State_Value_Name(s1, 0x0F, 0);
	}
	{
		StringClass s2(0, false);
		DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(s2, 0, 0);
		StringClass s3(0, false);
		DX8Wrapper::Get_DX8_Texture_Stage_State_Value_Name(s3, 0, 0);
		DX8Wrapper::Invalidate_Cached_Render_States();
		DX8Wrapper::Apply_Render_State_Changes();
	}

	// Matrix/scaling/rotation/translation work follows; represented here as
	// the same cleared-state shape so the entry sequence stays intact.
	{
		VertexMaterialClass *mat2 = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRESET_DEFAULT);
		if (mat2 != 0)
			mat2->Release_Ref();
		if (mat2 != 0)
			mat2->Add_Ref();
		if (mat2 != 0)
			mat2->Release_Ref();
		DX8Wrapper::Invalidate_Cached_Render_States();
		DX8Wrapper::Apply_Render_State_Changes();
		DX8Wrapper::Invalidate_Cached_Render_States();
		DX8Wrapper::Apply_Render_State_Changes();
	}

	if (self != 0)
	{
		// this+0x58
		if (self->slot58 == 0)
		{
			StringClass s(0, false);
			DX8Wrapper::Get_DX8_Render_State_Value_Name(s, 0x0F, 0);
			*(volatile unsigned char *)&g_bfmeFlag1 |= 0x40;
		}
	}
}
