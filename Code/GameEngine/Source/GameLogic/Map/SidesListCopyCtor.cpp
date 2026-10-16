// ??0SidesList@@QAE@ABV0@@Z, retail 0x0032EF3E (364 B), EH EXACT.
// BFME2 SidesList copy constructor, byte-verified against retail. The class
// model follows the canonical SidesList view in SidesListCtor.cpp (base order
// SubsystemInterface, Snapshot, Rva00330757Member) and the BFME2 offsets retail
// proves: notifier subobject +0x10, list/maps +0x20/+0x24/+0x30, counts and
// SidesInfo arrays +0x3C/+0x40/+0x7C0/+0x7C4, TeamsInfoRec +0xF44/+0xF60,
// cleared byte +0xF7C and the 20 28-byte FactionBuildLists records at +0xF80.
// The array copies call the rowed std::copy providers (SidesInfo 0x32E8F9,
// SidesList::FactionBuildLists 0x32DD66) and the map constructors the rowed
// STLport instantiations at 0x413727.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
//
// Target-side copy layout for SidesList. The donor SidesList.h establishes the
// SubsystemInterface/Snapshot bases; retail 0x0032EF3E then proves the BFME2
// offsets: notifier subobject +0x10, list/maps +0x20/+0x24/+0x30, counts and
// SidesInfo arrays +0x3C/+0x40/+0x7C0/+0x7C4, TeamsInfoRec +0xF44/+0xF60,
// cleared byte +0xF7C, and the 20 28-byte records at +0xF80. The latter's
// two vector assignments call the rowed 128-byte vector operator= at 0x32C0E3.
// The donor class identity is supported by the base, matching SidesList method
// call sites, the two target vtables and the target member offsets. Extra-field
// semantics beyond the vector control blocks remain address-derived.

#include <algorithm>
#include <vector>
#include "Common/Snapshot.h"
#include <map>
#include <list>
#include "ascii_string.h"
struct BfmePod128 { ~BfmePod128(); int a[32]; };
struct BfmeE8 { int a[2]; };
typedef _STL::map<int, _STL::vector<BfmePod128> > MapType0032EF3E;
typedef _STL::map<int, _STL::vector<_STL::vector<BfmeE8> > > MapType0032EF3E_B;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw();
	SubsystemInterface(const SubsystemInterface &that);

private:
	bool m_flag;
	char m_pad05[3];
	char m_name[4];
};

class Rva00330757Member
{
public:
	__declspec(nothrow) Rva00330757Member();
	~Rva00330757Member();

private:
	char m_body[0x10];
};

class SidesListNotifier : public Rva00330757Member
{
public:
	__forceinline SidesListNotifier() : Rva00330757Member() {}
	__forceinline SidesListNotifier(const SidesListNotifier &) : Rva00330757Member() {}
};

typedef MapType0032EF3E Rva0032D3D3Map;
typedef MapType0032EF3E_B Rva0032EAA1Map;

class SidesInfo
{
public:
	SidesInfo();
	SidesInfo(const SidesInfo &that);
	~SidesInfo();
	SidesInfo &operator=(const SidesInfo &that);

private:
	char m_body[0x60];
};

class TeamsInfoRec
{
public:
	TeamsInfoRec();
	TeamsInfoRec(const TeamsInfoRec &that);
	~TeamsInfoRec();
	void clear();

private:
	char m_body[0x1C];
};

struct Rva0032C0E3Element
{
	char m_body[0x80];
};

class Rva0032C19D
{
public:
	Rva0032C19D();
	~Rva0032C19D();
	Rva0032C19D &operator=(const Rva0032C19D &that);

private:
	int m_value;
	std::vector<Rva0032C0E3Element> m_first;
	std::vector<Rva0032C0E3Element> m_second;
};

class SidesList : public SubsystemInterface, public Snapshot, public SidesListNotifier
{
public:
	struct FactionBuildLists
	{
		int m_value;
		_STL::vector<Rva0032C0E3Element> m_first;
		_STL::vector<Rva0032C0E3Element> m_second;
	};
public:
	SidesList(const SidesList &that);
	virtual ~SidesList();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void draw();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	_STL::list<AsciiString> m_list;				// +0x20
	Rva0032D3D3Map m_map1;					// +0x24
	Rva0032EAA1Map m_map2;					// +0x30
	int m_numSides;							// +0x3C
	SidesInfo m_sides[20];					// +0x40
	int m_numSkirmishSides;					// +0x7C0
	SidesInfo m_skirmishSides[20];			// +0x7C4
	TeamsInfoRec m_teamrec;				// +0xF44
	TeamsInfoRec m_skirmishTeamrec;		// +0xF60
	bool m_cleared;							// +0xF7C
	char m_pad[3];
	FactionBuildLists m_extra[20];				// +0xF80
};

SidesList::SidesList(const SidesList &that)
	: SubsystemInterface(that),
	  SidesListNotifier(that),
	  m_list(),
	  m_map1(),
	  m_map2(),
	  m_numSides(that.m_numSides),
	  m_numSkirmishSides(that.m_numSkirmishSides),
	  m_teamrec(that.m_teamrec),
	  m_skirmishTeamrec(that.m_skirmishTeamrec),
	  m_cleared(that.m_cleared)
{
	std::copy(const_cast<SidesInfo *>(that.m_sides), const_cast<SidesInfo *>(that.m_sides) + that.m_numSides, m_sides);
	std::copy(const_cast<SidesInfo *>(that.m_skirmishSides), const_cast<SidesInfo *>(that.m_skirmishSides) + that.m_numSkirmishSides, m_skirmishSides);
	std::copy(const_cast<FactionBuildLists *>(that.m_extra), const_cast<FactionBuildLists *>(that.m_extra) + 20, m_extra);
}
