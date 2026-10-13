// cl: /DNDEBUG /MD /GX /Ireference/shims/moduledata
//
// W3DTornadoDrawModuleData file-unit (parse + ctor).
//
// ?buildFieldParse@W3DTornadoDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x000D16A3, 17 bytes. Single-table parse proc (table 0x00BCE150)
// through the rowed MultiIniFieldParse::add at 0x2BC6E. Row supersedes the
// parse pin.
//
// ??0W3DTornadoDrawModuleData@@QAE@XZ, retail 0x000D16B4, 67 bytes.
// Tornado draw ModuleData ctor: RadiusDecalTemplate member at +8 builds
// through the pinned 0x330E5D ctor (BFME1 RadiusDecal.h donor class),
// DecalCount at +0x3C clears and DecalMaxRadius at +0x40 loads from the
// 0x00BCE190 pool. Table 0x00BCE150 proves the three fields at identical
// offsets; factory 0x65171 (news 0x44, sole caller) proves the class size.
// Row supersedes the ctor pin.

class MultiIniFieldParse;
class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	static void parseUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	static void parseRadiusDecalTemplate(INI *ini, void *instance, void *store, const void *userData);

private:
	unsigned char m_data[0x34];
};

// Retail VA 0x00BCE150 (.rdata): 3 field records and a zero sentinel.
extern const FieldParse g_00BCE150[] = {
	{ "DecalTemplate", &RadiusDecalTemplate::parseRadiusDecalTemplate, 0, 0x8 },
	{ "DecalCount", &INI::parseUnsignedInt, 0, 0x3C },
	{ "DecalMaxRadius", &INI::parseReal, 0, 0x40 },
	{ 0, 0, 0, 0 }
};

extern "C" const void *const vtbl_00BCE198[];  // ??_7W3DTornadoDrawModuleData@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BCE198=??_7W3DTornadoDrawModuleData@@6B@")

#include "Common/Snapshot.h"

class UpdateModuleData
{
public:
	__declspec(dllimport) __forceinline UpdateModuleData() {}
	~UpdateModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }

private:
};

class W3DTornadoDrawModuleData : public UpdateModuleData
{
public:
	W3DTornadoDrawModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x00 vtable (init-list store lands between the implicit base call
	// and the implicit member call per the GiantBird precedent).
	const void *m_vtable;
	// +0x04 unstored gap.
	unsigned int m_unused04;
	// +0x08 DecalTemplate (table offset, via pinned 0x330E5D).
	RadiusDecalTemplate m_decalTemplate;
	// +0x3C DecalCount (table offset).
	int m_decalCount;
	// +0x40 DecalMaxRadius (table offset).
	float m_decalMaxRadius;
};

// ??0W3DTornadoDrawModuleData@@QAE@XZ @0x000D16B4
W3DTornadoDrawModuleData::W3DTornadoDrawModuleData()
	: m_vtable(reinterpret_cast<const void *>(((unsigned int)vtbl_00BCE198)))
{
	m_decalCount &= 0;
	m_decalMaxRadius = 200.0f;
}

// ?buildFieldParse@W3DTornadoDrawModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x000D16A3
void W3DTornadoDrawModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_00BCE150, 0);
}
