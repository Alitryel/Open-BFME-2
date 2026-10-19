// cl: /O1 /arch:SSE /G7 /GX /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
// CastleBehaviorModuleData construction and field parser.
class INI;
class MultiIniFieldParse;
#include <vector>
#include <map>
#include "ascii_string.h"

class Rva002618A2
{
public:
    Rva002618A2 *rva002618FA(int, int, int, int, int, int);
protected:
    unsigned m_words[7];
};
class Rva00045411BitSet : public Rva002618A2
{
public:
    Rva00045411BitSet() {}
    Rva00045411BitSet(int, int);
    Rva00045411BitSet(const Rva00045411BitSet &);
    __declspec(noinline) Rva00045411BitSet(int a, int b, int c, int d, int e, int f);
};
class BfmeFixedStorage0004543D : public Rva00045411BitSet
{
public:
    BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &);
    __declspec(noinline) BfmeFixedStorage0004543D(int a, int b);
};
extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;
class Rva003623E5Member
{
public:
    Rva003623E5Member();
    ~Rva003623E5Member();
    void rva00362192(Rva00045411BitSet, BfmeFixedStorage0004543D);
    void initFromStorages(BfmeFixedStorage0004543D, BfmeFixedStorage0004543D);
private:
    int m_handle;
};
struct RvaPair0039973B { AsciiString m_key; int m_value; ~RvaPair0039973B(); };
struct Rva00395D77 { unsigned char m_bytes[12]; ~Rva00395D77(); };
struct FXBoneInfo { AsciiString m_boneName; const void *m_particleSystemTemplate; };
class Rva0039597C;
class Rva00399800 { public: Rva0039597C *rva003997CD(Rva0039597C *, Rva0039597C *); };
namespace _STL {
template <> vector<FXBoneInfo>::iterator vector<FXBoneInfo>::erase(iterator, iterator);
template <> inline void vector<RvaPair0039973B>::clear()
{
    ((vector<FXBoneInfo> *)this)->erase((FXBoneInfo *)this->_M_start, (FXBoneInfo *)this->_M_finish);
}
template <> inline void vector<Rva00395D77>::clear()
{
    ((Rva00399800 *)this)->rva003997CD((Rva0039597C *)this->_M_start, (Rva0039597C *)this->_M_finish);
}
}
struct BfmeStringRecord004071F7 { AsciiString m_templateName; unsigned m_count1, m_count2; };
class Rva00397C94 { public: void rva00398257(); };
#include "Common/Snapshot.h"
extern const void *const BfmeCastleBehaviorModuleDataVtable[];
class __declspec(novtable) Rva0039A027Base : public Snapshot
{
public:
    __forceinline Rva0039A027Base() : m_f08(0.0f), m_n0c(0)
    { *(const void *const **)this = BfmeCastleBehaviorModuleDataVtable; }
    virtual ~Rva0039A027Base() {}
private:
    unsigned m_unknown04;
    float m_f08;
    unsigned m_n0c;
};
class __declspec(novtable) CastleBehaviorModuleData : public Rva0039A027Base
{
public:
    CastleBehaviorModuleData();
    static void buildFieldParse(MultiIniFieldParse &parse);
    static void rva0039981E(INI *, void *, void *, const void *);
    virtual ~CastleBehaviorModuleData();
private:
    AsciiString m_str10, m_str14;
    float m_f18, m_f1c, m_f20, m_f24, m_f28, m_f2c;
    Rva003623E5Member m_filter30, m_filter34;
    int m_n38;
    bool m_b3c, m_b3d, m_b3e;
    int m_n40, m_n44, m_n48, m_n4c;
    _STL::vector<RvaPair0039973B> m_vec50;
    _STL::vector<Rva00395D77> m_vec5c;
    _STL::map<int, BfmeStringRecord004071F7> m_map68;
    bool m_b74, m_b75;
};
// Native factory 0x0024AA99 is registered as CastleBehavior and calls this body.
CastleBehaviorModuleData::CastleBehaviorModuleData()
{
    ((Rva00397C94 *)&m_map68)->rva00398257();
    ((StringBase<char> *)&m_str10)->set("");
    m_vec50.clear();
    m_vec5c.clear();
    ((StringBase<char> *)&m_str14)->set("");
    m_f18 = 1.0f;
    m_f1c = 2.0f;
    m_f20 = 2.0f;
    m_f24 = 5.0f;
    m_f28 = 100.0f;
    m_f2c = 0.0f;
    m_b74 = false;
    m_filter30.rva00362192(Rva00045411BitSet(0,7,0x3c,0x68,0x99,0x73), BfmeFixedStorage0004543D(0,0x88));
    m_filter34.initFromStorages(g_defaultStorage009FEFA4, g_defaultStorage009FEFA4);
    m_n38 = 0x12;
    m_n48 = 0;
    m_n44 = 0;
    m_n40 = 0xa;
    m_b3c = false;
    m_b3d = false;
    m_n4c = -1;
    m_b3e = false;
    m_b75 = true;
}

typedef char Rva0039A027BaseSize[(sizeof(Rva0039A027Base) == 0x10) ? 1 : -1];
typedef char Rva0039A027StringSize[(sizeof(AsciiString) == 4) ? 1 : -1];
typedef char Rva0039A027FilterSize[(sizeof(Rva003623E5Member) == 4) ? 1 : -1];
typedef char Rva0039A027MaskSize[(sizeof(Rva00045411BitSet) == 28 && sizeof(BfmeFixedStorage0004543D) == 28) ? 1 : -1];
typedef char Rva0039A027PairSize[(sizeof(RvaPair0039973B) == 8) ? 1 : -1];
typedef char Rva0039A027RecordSize[(sizeof(BfmeStringRecord004071F7) == 12) ? 1 : -1];
typedef char Rva0039A027VectorSize[(sizeof(_STL::vector<RvaPair0039973B>) == 12 && sizeof(_STL::vector<Rva00395D77>) == 12) ? 1 : -1];
typedef char Rva0039A027MapSize[(sizeof(_STL::map<int, BfmeStringRecord004071F7>) == 12) ? 1 : -1];
typedef char Rva0039A027DataSize[(sizeof(CastleBehaviorModuleData) == 0x78) ? 1 : -1];

extern "C" void *memset(void *, int, unsigned);
Rva00045411BitSet::Rva00045411BitSet(int unused, int b1, int b2, int b3, int b4, int b5)
{
    (void)unused;
    memset(this, 0, 0x1c);
    m_words[(unsigned)b1 >> 5] |= (1u << (b1 & 31));
    m_words[(unsigned)b2 >> 5] |= (1u << (b2 & 31));
    m_words[(unsigned)b3 >> 5] |= (1u << (b3 & 31));
    m_words[(unsigned)b4 >> 5] |= (1u << (b4 & 31));
    m_words[(unsigned)b5 >> 5] |= (1u << (b5 & 31));
}
BfmeFixedStorage0004543D::BfmeFixedStorage0004543D(int unused, int bit)
{
    (void)unused;
    memset(this, 0, 0x1c);
    m_words[(unsigned)bit >> 5] |= (1u << (bit & 31));
}

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class INI
{
public:
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0039A4FC_ParseNameCountList(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0039A565_ParseNameNameReal(INI *ini, void *instance, void *store, const void *userData);
};

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);
void Rva001DEE74Parse(INI *ini, void *instance, void *store, const void *userData);

// The shared two-field table at VA 0x00BF00A0 (RepairHealthPercentPerSecond,
// BuildVariation), owned by GapBodiesGE17.cpp with the FoundationAIUpdate
// data factory that also registers it.
extern const FieldParse s_Rva002534B1FieldParse[];


// Retail VA 0x00C1ABA0 (RVA 0x0081ABA0, .rdata): 23 fields and the zero
// sentinel; tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeCastleBehaviorFields[] = {
	{ "CastleToUnpackForFaction", &CastleBehaviorModuleData::rva0039981E, 0, 0x68 },
	{ "FilterValidOwnedEntries", &iniParseObjectFilter, 0, 0x30 },
	{ "FilterCrew", &iniParseObjectFilter, 0, 0x34 },
	{ "FactionDecal", &INI::Rva0039A565_ParseNameNameReal, 0, 0x5C },
	{ "PreBuiltList", &INI::Rva0039A4FC_ParseNameCountList, 0, 0x50 },
	{ "PreBuiltPlyr", &INI::parseAsciiString, 0, 0x10 },
	{ "DecalName", &INI::parseAsciiString, 0, 0x14 },
	{ "DecalSize", &INI::parseReal, 0, 0x18 },
	{ "FadeTime", &INI::parseReal, 0, 0x1C },
	{ "UnpackDelayTime", &INI::parseReal, 0, 0x20 },
	{ "BuildTime", &INI::parseReal, 0, 0x24 },
	{ "ScanDistance", &INI::parseReal, 0, 0x28 },
	{ "MaxCastleRadius", &INI::parseReal, 0, 0x2C },
	{ "CrewPrepareTime", &INI::parseDurationUnsignedInt, 0, 0x38 },
	{ "InstantUnpack", &INI::parseBool, 0, 0x3C },
	{ "KeepDeathKillsEverything", &INI::parseBool, 0, 0x3D },
	{ "CrewReleaseFX", &INI::parseFXList, 0, 0x48 },
	{ "CrewPrepareFX", &INI::parseFXList, 0, 0x44 },
	{ "CrewPrepareInterval", &INI::parseDurationUnsignedInt, 0, 0x40 },
	{ "DisableStructureRotation", &INI::parseBool, 0, 0x74 },
	{ "EvaEnemyCastleSightedEvent", &Rva001DEE74Parse, 0, 0x4C },
	{ "Summoned", &INI::parseBool, 0, 0x3E },
	{ "TransferFoundationHealthToCastleUponUnpack", &INI::parseBool, 0, 0x75 },
	{ 0, 0, 0, 0 }
};

// ?buildFieldParse@CastleBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0039ABC5
// retail 0x0039ABC5, 33 bytes. Double-table parse proc (tables 0x00BF00A0
// and 0x00C1ABA0) through the rowed MultiIniFieldParse::add at 0x2BC6E.
// Row supersedes the parse pin.
void CastleBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(s_Rva002534B1FieldParse, 0);
	parse.add(BfmeCastleBehaviorFields, 0);
}
