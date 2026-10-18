// cl: /DNDEBUG /MD /EHs
//
// ?Rva003FD7CEParse@@YAXPAVINI@@@Z, retail 0x003FD7CE, 95 bytes.
// Chain: calls 0x0021294A which just landed. Parses one INI token via rowed
// getNextToken 0x0002DF97, builds a StringBase<char> via rowed ctor
// 0x00037BA0, creates a Rva003FD789 via rowed 0x0021294A on the global at
// 0x009FE1C8, tears down the temp via rowed releaseBuffer 0x00036410, then
// inits the new object from the FieldParse table at 0x00837CD8 via rowed
// initFromINI 0x0002DE78. Prev 0x003FD789 is the Rva003FD789 dtor.
class INI;
typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
struct FieldParse { const char *token; FieldParseProc parse; const void *userData; int offset; };
template <typename T> class StringBase;
class Rva0021294A;
class Rva003FD789;

template <typename T>
class StringBase
{
	friend void Rva003FD7CEParse(INI *ini);
public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
private:
	StringBase(const char *text);
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *obj, const FieldParse *table);
};

class Rva0021294A
{
public:
	Rva003FD789 *rva0021294A(const StringBase<char> &str);
};

class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;
struct LookupListRec { const char *name; int value; };
// The retail lookup list at RVA 0x009C18A8 (8 names and the null terminator).
extern const LookupListRec g_00DC18A8[9] = { { "SHADOW_DECAL", 12355808 }, { "SHADOW_VOLUME_NEW", 12355760 }, { "SHADOW_DIRECTIONAL_PROJECTION", 12355708 }, { "SHADOW_ADDITIVE_DECAL", 12355656 }, { "SHADOW_VOLUME_NON_SELF_2", 12355600 }, { "SHADOW_ALPHA_DECAL_DYNAMIC", 12355540 }, { "SHADOW_MERGE_DECAL", 12355492 }, { "SHADOW_VOLUME_OR_DECAL", 12355440 }, { 0, 0 } };
extern "C" {
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseBitString16@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x00837CD8: 7 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00837CD8[8] = {
	{ "Model", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
	{ "Pos", (FieldParseProc)&__identifier("?parseCoord3D@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x20 },
	{ "Frame", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
	{ "HasAnim", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
	{ "Xfer", (FieldParseProc)&__identifier("?parseBool@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x11 },
	{ "OrientAngle", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14 },
	{ "Shadow", (FieldParseProc)&__identifier("?parseBitString16@INI@@SAXPAV1@PAX1PBX@Z"), g_00DC18A8, 0x18 },
	{ 0, 0, 0, 0 }
};

void __cdecl Rva003FD7CEParse(INI *ini)
{
	const char *token = ini->getNextToken(0);
	if (token == 0)
		return;
	Rva003FD789 *item;
	{
		StringBase<char> name(token);
		item = ((Rva0021294A *)TheLivingWorldManager)->rva0021294A(name);
	}
	ini->initFromINI(item, g_00837CD8);
}

// TheLivingWorldManager (the data ledger's name): matched references place it at VA 0xdfe1c8.
LivingWorldManager *TheLivingWorldManager = 0;
