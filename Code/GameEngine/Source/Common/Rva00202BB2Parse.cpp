// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
//
// ?Rva00202BB2Parse@@YAXPAVINI@@@Z, retail 0x00202BB2, 126 bytes.
// Chain lane: calls 0x00202B6C (Rva00202B6C::rva00202B6C, landed just before),
// which made every callee rowed. Parses one INI token into a local
// AsciiString, maps it through the six-entry LOD table, and runs
// INI::initFromINI on the matching 0x4C-sized preset entry. Retail facts:
// - Free __cdecl function: ecx is loaded from the stack ([ebp+8]), never
//   preloaded by the caller, and the epilogue is a plain `ret`.
// - The by-value pass to rva00202B6C emits the compiler-generated
//   stack-copy construction through the PINNED StringBase copy ctor
//   (0x000365F0); the local is destroyed at the end through the ROWED
//   StringBase dtor (0x00036410), the trailing releaseBuffer call.
// - Global 0x009FE144 is spelled exactly as the sibling TU owns it
//   (TheRva00DFE144); the method call casts to Rva00202B6C* at the call
//   site because the rowed method ignores `this`.
// - FieldParse table at 0x007E3308 is DIR32-masked.

typedef int Int;
typedef bool Bool;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
struct FieldParse { const char *token; FieldParseProc parse; const void *userData; int offset; };

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *dst, const FieldParse *table);
};

class Rva00202B6C
{
public:
	Int rva00202B6C(AsciiString name);
};

struct Rva00DFE144Globals;
extern Rva00DFE144Globals *TheRva00DFE144;
// The retail name list at RVA 0x009B960C (47 names and the null terminator).
extern const char *const g_00DB960C[48] = { "Low", "Medium", "High", "UltraHigh", "VeryLow", "Low", "Medium", "High", "UltraHigh", "VeryLow", "Low", "Medium", "High", "UltraHigh", "Off", "Low", "High", "Low", "Medium", "High", "UltraHigh", "Off", "Low", "Medium", "High", "UltraHigh", "Low", "Medium", "High", "Low", "Medium", "High", "Low", "Medium", "High", "UltraHigh", "VeryLow", "Low", "Medium", "High", "VeryHigh", "Low", "High", "XX", "P3", "P4", "K7", 0 };
struct LookupListRec { const char *name; int value; };
// The retail lookup list at RVA 0x009B9630 (19 names and the null terminator).
extern const LookupListRec g_00DB9630[20] = { { "VeryLow", 12465996 }, { "Medium", 12465980 }, { "UltraHigh", 12465956 }, { "Low", 12465980 }, { "Low", 12465988 }, { "High", 12465968 }, { "Off", 12465996 }, { "Medium", 12465980 }, { "UltraHigh", 12465996 }, { "Medium", 12465980 }, { "Low", 12465988 }, { "High", 12465996 }, { "Medium", 12465980 }, { "UltraHigh", 12466000 }, { "Low", 12465988 }, { "High", 12465448 }, { "Low", 12465980 }, { "XX", 12464892 }, { "P4", 12464884 }, { 0, 0 } };
// The retail lookup list at RVA 0x009B9660 (13 names and the null terminator).
extern const LookupListRec g_00DB9660[14] = { { "Off", 12465996 }, { "Medium", 12465980 }, { "UltraHigh", 12465996 }, { "Medium", 12465980 }, { "Low", 12465988 }, { "High", 12465996 }, { "Medium", 12465980 }, { "UltraHigh", 12466000 }, { "Low", 12465988 }, { "High", 12465448 }, { "Low", 12465980 }, { "XX", 12464892 }, { "P4", 12464884 }, { 0, 0 } };
// The retail lookup list at RVA 0x009B9650 (15 names and the null terminator).
extern const LookupListRec g_00DB9650[16] = { { "Low", 12465988 }, { "High", 12465968 }, { "Off", 12465996 }, { "Medium", 12465980 }, { "UltraHigh", 12465996 }, { "Medium", 12465980 }, { "Low", 12465988 }, { "High", 12465996 }, { "Medium", 12465980 }, { "UltraHigh", 12466000 }, { "Low", 12465988 }, { "High", 12465448 }, { "Low", 12465980 }, { "XX", 12464892 }, { "P4", 12464884 }, { 0, 0 } };
// The retail name list at RVA 0x009B961C (43 names and the null terminator).
extern const char *const g_00DB961C[44] = { "VeryLow", "Low", "Medium", "High", "UltraHigh", "VeryLow", "Low", "Medium", "High", "UltraHigh", "Off", "Low", "High", "Low", "Medium", "High", "UltraHigh", "Off", "Low", "Medium", "High", "UltraHigh", "Low", "Medium", "High", "Low", "Medium", "High", "Low", "Medium", "High", "UltraHigh", "VeryLow", "Low", "Medium", "High", "VeryHigh", "Low", "High", "XX", "P3", "P4", "K7", 0 };
// The retail name list at RVA 0x009B968C (15 names and the null terminator).
extern const char *const g_00DB968C[16] = { "Low", "Medium", "High", "UltraHigh", "VeryLow", "Low", "Medium", "High", "VeryHigh", "Low", "High", "XX", "P3", "P4", "K7", 0 };
// The retail name list at RVA 0x009B9644 (33 names and the null terminator).
extern const char *const g_00DB9644[34] = { "Off", "Low", "High", "Low", "Medium", "High", "UltraHigh", "Off", "Low", "Medium", "High", "UltraHigh", "Low", "Medium", "High", "Low", "Medium", "High", "Low", "Medium", "High", "UltraHigh", "VeryLow", "Low", "Medium", "High", "VeryHigh", "Low", "High", "XX", "P3", "P4", "K7", 0 };
// The retail name list at RVA 0x0081B6A4 (7 names and the null terminator).
extern const char *const g_00C1B6A4[8] = { "NONE", "ULTRA_HIGH_ONLY", "HIGH_OR_ABOVE", "MEDIUM_OR_ABOVE", "LOW_OR_ABOVE", "VERY_LOW_OR_ABOVE", "ALWAYS_RENDER", 0 };
extern "C" {
void __identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x007E3308: 30 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_007E3308[31] = {
	{ "ModelLOD", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00DB960C, 0x0 },
	{ "EffectsLOD", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00DB9630, 0x4 },
	{ "MaxParticleCount", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
	{ "UseShadowVolumes", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
	{ "UseShadowDecals", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xD },
	{ "UseShadowMapping", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xE },
	{ "ShadowLOD", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00DB9660, 0x10 },
	{ "UseTerrainNormalMap", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14 },
	{ "UseDistanceDependantTerrainTextures", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x15 },
	{ "WaterLOD", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00DB9650, 0x18 },
	{ "ShowSoftWaterEdge", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1C },
	{ "MaxTankTrackEdges", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x20 },
	{ "MaxTankTrackOpaqueEdges", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x24 },
	{ "MaxTankTrackFadeDelay", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x28 },
	{ "ShowProps", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x30 },
	{ "TextureReductionFactor", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x2C },
	{ "AnimationDetail", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00DB961C, 0x34 },
	{ "ShaderLOD", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00DB968C, 0x38 },
	{ "ShaderMaterialReplacement", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x3C },
	{ "UseHeatEffects", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x3D },
	{ "DecalLOD", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00DB9644, 0x40 },
	{ "MinParticlePriority", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00C1B6A4, 0x44 },
	{ "MinParticleSkipPriority", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), g_00C1B6A4, 0x48 },
	{ "MinimumFPS", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x0 },
	{ "ParticleSkipMask", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
	{ "DebrisSkipMask", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
	{ "SlowDeathScale", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
	{ "MaximumAmbientStreams", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x0 },
	{ "AllowDolby", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
	{ "AllowReverb", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x5 },
	{ 0, 0, 0, 0 }
};

// ?Rva00202BB2Parse@@YAXPAVINI@@@Z
void Rva00202BB2Parse(INI *ini)
{
	AsciiString name;
	name.set(ini->getNextToken(0));
	if (TheRva00DFE144 != 0)
	{
		Int idx = ((Rva00202B6C *)TheRva00DFE144)->rva00202B6C(name);
		if (idx != -1)
			ini->initFromINI((char *)TheRva00DFE144 + idx * 0x4c, g_007E3308);
	}
}
