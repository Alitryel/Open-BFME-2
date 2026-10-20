// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0TeamFactory@@QAE@XZ, retail 0x003A25B1, 109 bytes.
//
// Evidence from the retail body: the rowed SubsystemInterface ctor 0x001B4E63
// (twelve-byte base), the inlined trivial Snapshot ctor's vptr store at +0xC
// (0x00BBB554, canonical Snapshot header), the two TeamFactory vtables
// 0x0081AE2C / 0x0081AE1C, the rowed pod-map ctor 0x0024613C at +0xB0, zeroes
// at +0xBC and +0xC0, and memset(this+0x10, 0, 0xA0) for the forty-pointer
// m_dummyTeams array. Layout: SubsystemInterface(0xC) + Snapshot(4) +
// m_dummyTeams[40] (0xA0) + map (0xC) + two ints = 0xC4, the size the
// GameEngineInit view gives TeamFactory. TeamFactoryDtor.cpp (rowed at
// 0x003A383A) stores the same two vtables and destroys the +0xB0 member, and
// TeamFactoryClear.cpp names the +0x10 array and the +0xB0 map, so the member
// roles come from the rowed family rather than from this TU's guess.

#define __PLACEMENT_VEC_NEW_INLINE
#include <map>
#include <string.h>

// Native C1AE1C slot 2 is the TeamFactory name getter at 3A261E.
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
// Suppress this TU's non-retail copy of ??1?$_Rb_tree@HU?$pair@$$CBHUBfmePod8@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod8@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod8;
namespace _STL { template <> _Rb_tree<int,pair<int const ,BfmePod8>,_Select1st<pair<int const ,BfmePod8> >,less<int>,allocator<pair<int const ,BfmePod8> > >::~_Rb_tree(); }

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void postProcessLoad();
	virtual bool vslot04(int);
	virtual bool vslot05();
	virtual int vslot06();
	virtual void vslot07(int);
	virtual void vslot08();
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	char m_pad04[8];
};

struct BfmePod8
{
	int words[2];
};

typedef std::pair<const int, BfmePod8> TeamMapValue;
typedef std::_Rb_tree<int, TeamMapValue, std::_Select1st<TeamMapValue>, std::less<int>, std::allocator<TeamMapValue> > TeamMapTree;
// Use the shared destructor already selected for the POD-map family.
template <> TeamMapTree::~_Rb_tree();

class TeamPrototype;

class TeamFactory : public SubsystemInterface, public Snapshot
{
public:
	TeamFactory();
	virtual ~TeamFactory();
	// Native primary table slots, shared with TeamFactoryDtor.cpp.
	virtual void init();
	virtual void reset();
	virtual void update();

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);

private:
	TeamPrototype *m_dummyTeams[40]; // +0x10
	std::map<int, BfmePod8> m_prototypes; // +0xB0
	int m_uniqueTeamPrototypeID; // +0xBC
	int m_uniqueTeamID; // +0xC0
};

TeamFactory::TeamFactory()
	: m_uniqueTeamPrototypeID(0), m_uniqueTeamID(0)
{
	memset(m_dummyTeams, 0, sizeof(m_dummyTeams));
}
