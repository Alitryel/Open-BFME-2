// ?parseCastleTemplateMaps@SidesList@@QAEXXZ
// partial score=0.938 date=2026-10-17
// ?parseCastleTemplateMaps@SidesList@@QAEXXZ
// partial score=0.93 date=2026-10-15
// ?rva0032F84F@Rva0032F84F@@QAEXXZ
// partial score=0.9 date=2026-10-15
// ?parseCastleTemplateMaps@SidesList@@QAEXXZ
// partial score=0.8581 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /EHsc /MD /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
//
// SidesList's map-file chunk parsers and writer (BFME2 SidesList.cpp).
// WorldBuilder's debug build names each body and keeps its statement order;
// its inline setters are retail's inline stores, except the by-value string
// setters, which retail calls out of line (rowed under address names below).
//
// BuildListInfo layout (target): BuildListInfoCtor.cpp, 0x80 bytes, built by
// the ctor 0x0032A0CE and destroyed by 0x0032A186 on the parser's stack.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <stdlib.h>
namespace _STL { void __cdecl free(void *block) throw(...); }
#define free _STL::free
#include <vector>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base
// wrapper (_List_iterator_base::operator!=, retail's copy is 0x006CFE40).
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
#include <set>
#undef free

#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void _Destroy<AsciiString>(AsciiString *); }
namespace _STL { template <> _Rb_tree_base<AsciiString, allocator<AsciiString> >::~_Rb_tree_base(); }
namespace _STL { template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base(); }
namespace _STL { template <> vector<AsciiString, allocator<AsciiString> >::~vector(); }
namespace _STL { template <> _Rb_tree_node<AsciiString> * allocator<_Rb_tree_node<AsciiString> >::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<_Rb_tree_node<AsciiString> *, _Rb_tree_node<AsciiString>, allocator<_Rb_tree_node<AsciiString> > >::deallocate(_Rb_tree_node<AsciiString> *, unsigned int); }
namespace _STL { template <> void _STLP_alloc_proxy<AsciiString *, AsciiString, allocator<AsciiString> >::deallocate(AsciiString *, unsigned int); }
namespace _STL { template <> void allocator<_Rb_tree_node<AsciiString> >::deallocate(_Rb_tree_node<AsciiString> *, unsigned int) const; }
namespace _STL { template <> void allocator<AsciiString>::deallocate(AsciiString *, unsigned int) const; }
// bfme link decl-only end

enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);	// 0x0009FA65
	NameKeyType nameToKey(const char *name);	// 0x00148E1A
};
extern NameKeyGenerator *TheNameKeyGenerator;

class StaticNameKey
{
public:
	NameKeyType key() const;			// 0x00148F5E
	operator NameKeyType() const { return key(); }

private:
	mutable NameKeyType m_key;
	const char *m_name;
};
extern const StaticNameKey TheKey_objectName;			// VA 0x00DBDCC4
extern const StaticNameKey TheKey_objectIsABase;		// VA 0x00DBDD0C
extern const StaticNameKey TheKey_objectBaseName;		// VA 0x00DBDD14
extern const StaticNameKey TheKey_objectBasePriority;	// VA 0x00DBDD84
extern const StaticNameKey TheKey_objectBasePhase;		// VA 0x00DBDD8C
// Preserve the data ledger's established provider spelling for this key.
class Rva00148F5ECache {
public:
    NameKeyType get();
    operator NameKeyType() { return get(); }
private:
    int m_key;
    const char *m_name;
};
extern Rva00148F5ECache TheKey_playerAIType;
extern const StaticNameKey TheKey_playerName;			// VA 0x00DBDE24
extern const StaticNameKey TheKey_teamOwner;			// VA 0x00DBD9FC
extern const StaticNameKey TheKey_teamLibraryMapName;	// VA 0x00DBDC1C
extern const StaticNameKey TheKey_teamName;			// VA 0x00DBD9F4

enum ErrorCode { ERROR_CORRUPT_FILE_FORMAT = 0xDEAD0005 };

struct DataChunkInfo
{
	AsciiString label;
	AsciiString parentLabel;
	unsigned short version;				// +0x08
	int dataSize;
};

class Dict
{
public:
	Dict(const Dict &src) : m_data(src.m_data) { if (m_data) ++*(unsigned short *)m_data; }
	~Dict() { releaseData(); }
	enum DataType { DICT_NONE = -1, DICT_BOOL = 0, DICT_INT, DICT_REAL, DICT_ASCIISTRING };
	DataType getType(int key) const;	// 0x0031317C
	bool getBool(int key, bool *exists = 0) const;	// 0x00313198
	int getInt(int key, bool *exists = 0) const;	// 0x003131CA
	AsciiString getAsciiString(int key, bool *exists = 0) const;	// 0x0031359F
	void setAsciiString(int key, const AsciiString &value);	// 0x0031375A

private:
	void releaseData();					// 0x0031339C
	void *m_data;
};

class ChunkInputStream
{
};

// The cached file stream the build-list loader reads (BFME 1's
// CachedFileInputStream), rowed under its constructor's address name: ctor
// 0x00240000, dtor 0x0023F4F0 and open 0x00308050; its close is rowed under
// Rva003079ED below. 0x20 bytes on the loader's stack.
class Rva00240000 : public ChunkInputStream
{
public:
	Rva00240000() throw();						// 0x00240000
	~Rva00240000();						// 0x0023F4F0
	bool rva00308050(AsciiString path);	// 0x00308050, open

private:
	char m_data[0x20];
};

class Rva003079ED
{
public:
	void rva003079ED();					// 0x003079ED, close
};

class DataChunkInput
{
public:
	explicit DataChunkInput(ChunkInputStream *stream);	// 0x00307316
	~DataChunkInput();					// 0x00306F01
	int readInt();						// 0x00306E78
	float readReal();					// 0x00306E56
	unsigned char readByte();			// 0x00306E9A
	NameKeyType readNameKey();			// 0x003077E0
	AsciiString readAsciiString();		// 0x0030750A
	Dict readDict();					// 0x00307833
	bool parse(void *userData);			// 0x00307AC0

private:
	char m_data[0x28];
};

// DataChunkInput's parser unregistration (WB DataChunkInput::unregisterParser),
// rowed under its address-era spelling.
class Q1Forwardee0000871A
{
public:
	void handle(int token);				// 0x00306D7B
};

// The parser binding that registers "PlayerScriptsList" on construction and
// unregisters itself on destruction; its base dtor is inline here (vtable
// 0x007C9574), its ctor out of line.
class BfmeParserRegistryVE;

class BfmeParserBindingBaseVE
{
public:
	__declspec(dllimport) __forceinline virtual ~BfmeParserBindingBaseVE() { m_registry->handle(m_token); }
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();

private:
	Q1Forwardee0000871A *m_registry;	// +0x04, the DataChunkInput
	int m_token;						// +0x08
};

class Rva003B3417 : public BfmeParserBindingBaseVE
{
public:
	Rva003B3417(void *scripts, void *count, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);	// 0x003B3417

private:
	void *m_scripts;
	void *m_count;
};

// The binding that registers "LibraryMaps" and fills one vector<AsciiString>
// per side and the count of lists read.
class LibraryMapsParser : public BfmeParserBindingBaseVE
{
public:
	LibraryMapsParser(void *lists, void *count, void *table, void *info);	// 0x00329F83

private:
	void *m_lists;
	void *m_count;
};

class ScriptList
{
public:
	ScriptList();
	ScriptList(const ScriptList &other);	// 0x003B88DA
	virtual ~ScriptList();
	void swap(ScriptList *other);		// 0x003B58DF
	void rva003B693A();					// 0x003B693A, WB discards overridden scripts
	void rva003B7362();					// 0x003B7362, WB 0xaa4f20

private:
	char m_data[0x4C - 4];
};

// ScriptList's merge of another list (WB 0xaa4840), rowed under its
// address-era spelling.
struct BfmeSubGE;
class BfmeThingGE
{
public:
	void rva003B89A7(BfmeSubGE *other);	// 0x003B89A7
};

class DataChunkOutput
{
public:
	void openDataChunk(char *name, unsigned short ver);	// 0x00307C76
	void closeDataChunk();				// 0x00306C88
	void writeNameKey(NameKeyType key);	// 0x00307D29
	void writeReal(float r);			// 0x00306CFF
	void writeInt(int i);				// 0x00306CFF
	void writeByte(unsigned char b);	// 0x00306D17
	void writeAsciiString(const AsciiString &s);	// 0x00307033
	void writeDict(const Dict &d);		// 0x00307D85
};

// class-gate: allow Coord3D the canonical data-only header cannot declare BFME 2's user copy constructor that keeps setLocation's by-value argument a stack temporary of its own (retail ebp-0x38; WB twin inlines it); same three floats
struct Coord3D
{
	float x;
	float y;
	float z;

	Coord3D() {}
	Coord3D(const Coord3D &other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
	void add(const Coord3D *a) { x += a->x; y += a->y; z += a->z; }
	void sub(const Coord3D *a) { x -= a->x; y -= a->y; z -= a->z; }
};

// The kind-of mask at +0x108 and the name at +0x64 of the template a map
// object resolves to through its override chain.
class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
	__forceinline bool isKindOf(int t) const { return (m_kindOf[t >> 3] & (1 << (t & 7))) != 0; }

private:
	char m_pad00[0x64];
	AsciiString m_name;					// +0x64
	char m_pad68[0x108 - 0x68];
	unsigned char m_kindOf[4];			// +0x108
};

// MapObject's template and location getters, rowed under their address-era
// spellings: the final-override walk 0x0030D833 and 0x0030D631.
struct BfmeSlotJA;
class BfmeThing932A { public: BfmeSlotJA *bfmeGo932A(); };
class BfmeRetBWF;
class Rva0030D631 { public: BfmeRetBWF *rva0030D631(); };

class MapObject
{
public:
	MapObject *getNext() const { return m_nextMapObject; }
	const ThingTemplate *getThingTemplate() { return (const ThingTemplate *)((BfmeThing932A *)this)->bfmeGo932A(); }
	const Coord3D *getLocation() { return (const Coord3D *)((Rva0030D631 *)this)->rva0030D631(); }
	float getAngle() const { return m_angle; }
	Dict *getProperties() { return &m_properties; }

private:
	char m_pad00[0x04];
	MapObject *m_nextMapObject;			// +0x04
	char m_pad08[0x1C - 0x08];
	float m_angle;						// +0x1C
	char m_pad20[0x24 - 0x20];
	Dict m_properties;					// +0x24
};

// A castle path: its two-real points in a vector at +0x08, the next path at
// +0x3C and its name at +0x40. The by-value point getter 0x002E3A8D keeps its
// address-era spelling (hidden return pointer explicit).
struct Rva002E3A8DPair
{
	float m_x;
	float m_y;
};

class Rva002E3A8DHolder
{
public:
	Rva002E3A8DPair *get(Rva002E3A8DPair *out, int index);	// 0x002E3A8D
	int getNumPoints() const { return m_points.size(); }
	Rva002E3A8DHolder *getNext() const { return m_next; }
	const AsciiString &getName() const { return m_name; }

private:
	char m_pad00[0x08];
	_STL::vector<Rva002E3A8DPair> m_points;	// +0x08
	char m_pad14[0x3C - 0x14];
	Rva002E3A8DHolder *m_next;			// +0x3C
	AsciiString m_name;					// +0x40
};

// The 128-byte entry SidesList::addToFactionBuildListMap 0x0032CDFE copies.
struct BfmePod128 { int a[32]; };

// A castle path point: two reals (vector<BfmeE8>::push_back 0x00539A2E).
struct BfmeE8 { float x; float y; };

// By-value AsciiString setters at BuildListInfo +0x04, +0x08 and +0x30. The
// first and last sit beside BuildListInfo's ctor and dtor; +0x08 is folded
// with another class's setter at 0x002AAE81.
class Rva0032A438 { public: void rva0032A438(AsciiString s); };
class Rva002AAE81 { public: void rva002AAE81(AsciiString s); };
class Rva0032A46C { public: void rva0032A46C(AsciiString s); };

// The by-value getter of the AsciiString at +0x04, folded with other classes'
// name getters at 0x00564DF2.
class Rva00564DF2NameView { public: AsciiString rva00564DF2() const; };

class BuildListInfo
{
	friend class SidesList;

public:
	BuildListInfo();					// 0x0032A0CE

	void setLocation(Coord3D loc) { m_location = loc; }
	void setAngle(float angle) { m_angle = angle; }
	void setInitiallyBuilt(bool built) { m_isInitiallyBuilt = built; }
	void setNumRebuilds(unsigned int rebuilds) { m_numRebuilds = rebuilds; }
	void setHealth(int health) { m_health = health; }
	void setWhiner(bool whiner) { m_whiner = whiner; }
	void setUnsellable(bool unsellable) { m_unsellable = unsellable; }
	void setRepairable(bool repairable) { m_repairable = repairable; }

	AsciiString getTemplateName() const;	// 0x000AF1DD (ICF with TerrainType::getTexture)
	AsciiString getScript() const;		// 0x0032A4A0
	const Coord3D *getLocation() const { return &m_location; }
	float getAngle() const { return m_angle; }
	bool isInitiallyBuilt() { return m_isInitiallyBuilt; }
	int getNumRebuilds() { return m_numRebuilds; }
	int getHealth() { return m_health; }
	bool getWhiner() { return m_whiner; }
	bool getUnsellable() { return m_unsellable; }
	bool getRepairable() { return m_repairable; }
	BuildListInfo *getNext() { return m_nextBuildList; }

protected:
	virtual ~BuildListInfo();			// 0x0032A186

private:
	AsciiString m_buildingName;			// +0x04
	AsciiString m_templateName;			// +0x08
	Coord3D m_location;					// +0x0C
	float m_rallyPointOffset[2];		// +0x18
	float m_angle;						// +0x20
	bool m_isInitiallyBuilt;			// +0x24
	unsigned int m_numRebuilds;			// +0x28
	BuildListInfo *m_nextBuildList;		// +0x2C
	AsciiString m_script;				// +0x30
	int m_health;						// +0x34
	bool m_whiner;						// +0x38
	bool m_unsellable;					// +0x39
	bool m_repairable;					// +0x3A
	char m_tail[0x80 - 0x3B];
};

class SidesInfo
{
public:
	BuildListInfo *getBuildList() { return m_pBuildList; }
	Dict *getDict() { return &m_dict; }
	void addToBuildList(BuildListInfo *buildList, int position);	// 0x003297FB
	void setScriptList(ScriptList *scriptList) { m_scripts.swap(scriptList); }

private:
	friend class SidesList;

	BuildListInfo *m_pBuildList;		// +0x00
	Dict m_dict;						// +0x04
	ScriptList m_scripts;				// +0x08
	_STL::vector<AsciiString> m_libraryMaps;	// +0x54
};

// The 16-byte team entries (SidesListRemoveSideAndTeams.cpp): the next team
// id at +0 and the team dict at +0xC.
class TeamsInfoEntry
{
public:
	short m_next;
	short m_previous;
	short m_reserved;
	short m_free;
	int m_generation;
	Dict m_dict;						// +0x0C
};

class TeamsInfoRec
{
public:
	TeamsInfoRec();
	~TeamsInfoRec();
	void swap(TeamsInfoRec *other);		// 0x0032B651
	__forceinline int getNumTeams() const { return m_count; }
	int addTeam(const Dict *dict);		// 0x0032DA4E
	void rva0032C2C4();					// 0x0032C2C4, WB discards overridden teams
	void removeTeam(int id);			// 0x0032C26D, WB removeTeam
	int getFirstTeamID() const { return m_teams[0].m_next; }
	int getNextTeamID(int id) const { return m_teams[id].m_next; }
	Dict *getTeamInfo(int id) { return &m_teams[id].m_dict; }

private:
	char m_index[0x0C];
	_STL::vector<TeamsInfoEntry> m_teams;	// +0x0C
	short m_count;						// +0x18, signed test at 0x0032E48C
	char m_rest[0x1C - 0x1A];
};

class LibraryMapCache;

// The case-insensitive set of library map names linkLibraryMaps has visited;
// its _M_find 0x0002C751 and insert 0x0002CA26 are rowed in WWLib.
struct BfmeStringNoCaseLess { bool operator()(const AsciiString &a, const AsciiString &b) const; };
typedef _STL::set<AsciiString, BfmeStringNoCaseLess> AsciiStringNoCaseSet;

// BFME 2's SidesList has two bases (SidesList_sidesInfo.cpp), so its member
// pointers are the 8-byte multiple-inheritance form; this view flattens them.
#pragma pointers_to_members(full_generality, multiple_inheritance)
class SidesList
{
public:
	SidesList();						// 0x0032EE24
	virtual ~SidesList();				// 0x0032EC63

	bool parseSidesDataChunk(DataChunkInput &file, DataChunkInfo *info);
	bool parseBuildListDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);
	void writeSidesDataChunk(DataChunkOutput &chunkWriter);
	void addToFactionBuildListMap(NameKeyType faction, const BfmePod128 &entry, int listType);	// 0x0032CDFE
	int addSide(const Dict *dict);		// 0x0032D076
	SidesInfo *getSideInfo(int side);	// 0x002035BA
	void swap(SidesList *other);		// 0x0032B690
	void rva0032E02B();					// 0x0032E02B, WB validateSides
	void rva0032ED61();					// 0x0032ED61, castle template map clear
	void parseCastleTemplateMaps();		// 0x0032F84F
	bool parseCastleTemplateDataChunk(DataChunkInput &file, DataChunkInfo *info);
	bool parseLibraryMapListsChunk(DataChunkInput &file, DataChunkInfo *info);
	void writeCastleTemplateDataChunk(DataChunkOutput &out, MapObject *pMapObjs, const AsciiString &mapName, Rva002E3A8DHolder *paths);
	void rva0032E6F4(int key, const BfmePod128 &entry);	// 0x0032E6F4, castle build entry add
	void rva0032ED75(int key, const _STL::vector<BfmeE8> &path);	// 0x0032ED75, castle path add
	void rva0032C88F(int index);		// 0x0032C88F, WB 0xa86610
	void rva0032A4D7(DataChunkOutput &chunkWriter);	// 0x0032A4D7, Teams chunk writer
	bool rva0032D038(DataChunkInput &file, DataChunkInfo *info);
	bool rva0032D04A(DataChunkInput &file, DataChunkInfo *info);
	void rva0032D554();
	bool rva0032F0AA(DataChunkInput &file, void *info);	// 0x0032F0AA, the "Teams" callback
	void discardOverriddenScriptsAndTeams();
	void addMusicScriptReference();
	void rva0032FC70(int sideIndex, LibraryMapCache *cache);
	void rva0032E474(SidesInfo *side, ScriptList *scripts, TeamsInfoRec *teams);
	void linkLibraryMaps(int sideIndex, LibraryMapCache *cache, const _STL::vector<AsciiString> &libraryMaps,
		AsciiStringNoCaseSet &visited, ScriptList *scripts, TeamsInfoRec *teams);

private:
	// getSideInfo expanded in place, as linkLibraryMaps has it for a library
	// map's second side (cmp [sides+0x3C],1 / lea [sides+0xA0]).
	SidesInfo *getSideInfoInline(int side) { return side >= 0 && side < m_numSides ? (SidesInfo *)m_sides + side : 0; }

	char m_bases[0x20 - 4];
	_STL::list<AsciiString> m_castleTemplateMaps;	// +0x20
	char m_castleTemplates[0x3C - 0x24];
	int m_numSides;						// +0x3C
	char m_sides[0xF44 - 0x40];
	TeamsInfoRec m_teamrec;				// +0xF44
	char m_secondTeamRec[0x1C]; // distinct adjacent TeamsInfoRec at +0xF60
	bool m_cleared;						// +0xF7C
	char m_factionBuildLists[0x11B0 - 0xF7D];
};

// SidesList::parseSidesDataChunk, retail 0x0032F13C (820 bytes): the sides,
// their build lists and (before version 5) the teams and player scripts are
// read into a scratch SidesList that is then swapped in. Identity (target):
// WorldBuilder's debug twin wb 0xa82370 (SidesList.cpp:729) makes the same
// calls; retail's ret 8 drops BFME 1's userData. The scratch list's ctor and
// dtor are 0x0032EE24 and 0x0032EC63, its +0xF44 TeamsInfoRec takes the
// teams, and a build count over 9999 reads as none.


// The castle build-list and path maps' clear (this +0x24 and +0x30).
class Rva0032ED61 { public: void rva0032ED61(); };

// The SidesList chunk binding (BfmeDataChunkParserBinding.cpp): its callback
// is an 8-byte member pointer, its base destructor the inline one above.
#pragma pointers_to_members(full_generality, multiple_inheritance)
typedef bool (SidesList::*BfmeSidesListChunkCallback)(DataChunkInput &, DataChunkInfo *);

class BfmeParserBindingVE : public BfmeParserBindingBaseVE
{
public:
	BfmeParserBindingVE(SidesList *owner, BfmeSidesListChunkCallback callback,
		DataChunkInput *input, const AsciiString &label, const AsciiString &parentLabel);	// 0x000AD73D

	virtual void bfmeSlot0();
	virtual void bfmeSlot1();

private:
	SidesList *m_owner;
	BfmeSidesListChunkCallback m_callback;
};

void SidesList::parseCastleTemplateMaps()
{
	((Rva0032ED61 *)this)->rva0032ED61();
	for (_STL::list<AsciiString>::iterator it = m_castleTemplateMaps.begin(); it != m_castleTemplateMaps.end(); ++it) {
		AsciiString mapName = *it;
		if (mapName.isEmpty())
			return;
		AsciiString path("Bases\\");
		path.concat(mapName);
		path.concat("\\");
		path.concat(mapName);
		path.concat(".bse");
		AsciiString fileName(path);
		Rva00240000 fileStrm;
		bool fileFound = fileStrm.rva00308050(fileName);
		if (fileFound) {
			DataChunkInput file(&fileStrm);
			BfmeParserBindingVE parser(this, &SidesList::parseCastleTemplateDataChunk, &file, "CastleTemplates", AsciiString::TheEmptyString);
			bool ok = file.parse(0);
			switch (ok) {
			case false:
				throw ERROR_CORRUPT_FILE_FORMAT;
			case true:
				break;
			}
			((Rva003079ED *)&fileStrm)->rva003079ED();
		}
	}
}
