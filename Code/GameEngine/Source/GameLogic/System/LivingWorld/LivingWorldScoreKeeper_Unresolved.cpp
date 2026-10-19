// cl: /O1 /G7 /arch:SSE /EHs /DNDEBUG /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// Split from LivingWorldScoreKeeper.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// stlport
// LivingWorldScoreKeeper: complete 0xFC-byte Snapshot with eight observer
// interfaces. WB10EF240 establishes the class and observer names; retail
// constructor4EEADE, destructor4EED02, primary tableC62AC4 and all eight
// secondary tables establish the offsets and callback ownership independently.
// Base Phase/RTS tablesC62A20 contain two RET8 callbacks, not deleting dtors.
// Base widths in interface order: 8,16,12,8,16,16,8,16 bytes. Final tables:
// C62ABC/C62AAC/C62AA0/C62A98/C62A88/C62A78/C62A70/C62A60.
// eventN_M names describe the proven interface and slot only; the original
// callback names remain unknown. Each override reproduces its existing retail
// body, including the compiler's secondary-this adjustment. Default slots are
// real empty methods with the target RET4/8/12 ABI. /EHs preserves the native
// destructor's four inline storage-free transitions.
// The twelve-byte map storage invokes the existing int/pointer constructor
// at33C432 and unsigned/pointer tree teardown at357C6A. Both are independently
// proven retail providers; no extra template pin is introduced. Collector/xfer
// use the established template-key/integer-count view. The storage view does
// not assert the original template spelling. Vector roles are localized too.
// Scratch raw objects, table-slot proof and EH checks: build/astra-high-d/.
// Keep vector growth's unsigned comparison local. Its standalone template
// copy differs from retail; all uses in this unit are already inlined.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}
#include <vector>
#include <map>
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

extern "C" __declspec(dllimport) long __cdecl time(long *);

class Rva004E06FBPtrChase32Field; class LivingWorldBattle; struct Rva004EF2ABArg; class LivingWorldLogic; class CountInputPrefix;
class LivingWorldPhaseObserver {public: ~LivingWorldPhaseObserver(){} virtual void event0_0(int,int){} virtual void event0_1(int,int){} };
class LivingWorldBuildingObserver {public: ~LivingWorldBuildingObserver(){} virtual void event1_0(Rva004E06FBPtrChase32Field*){} virtual void event1_1(int){} virtual void event1_2(int){} virtual void event1_3(const Rva004E06FBPtrChase32Field*,int){} };
class LivingWorldAutoResolveEventObserver {public: ~LivingWorldAutoResolveEventObserver(){} virtual void event2_0(int,int,int){} virtual void event2_1(int,int,int){} virtual void event2_2(int,LivingWorldBattle*,void*){} };
class LivingWorldRTSEventObserver {public: ~LivingWorldRTSEventObserver(){} virtual void event3_0(int,int){} virtual void event3_1(int,LivingWorldBattle*){} };
class LivingWorldRegionObserver {public: ~LivingWorldRegionObserver(){} virtual void event4_0(int,int,int){} virtual void event4_1(int,int,int){} virtual void event4_2(int,int){} virtual void event4_3(int,int){} };
class LivingWorldPlayerObserver {public: ~LivingWorldPlayerObserver(){} virtual void event5_0(Rva004EF2ABArg*){} virtual void event5_1(int,int,int){} virtual void event5_2(int,int,int){} virtual void event5_3(int){} };
#include "../../../../Include/Common/LivingWorldLogicObserver.h"
class LivingWorldBuildingNuggetSpawnArmyObserver {public: ~LivingWorldBuildingNuggetSpawnArmyObserver(){} virtual void event7_0(int){} virtual void event7_1(int,int){} virtual void event7_2(int,int){} virtual void event7_3(CountInputPrefix*,void*){} };

struct Rva002BA8F1Listener;
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *); };
class Rva002B7250;
extern Rva002B7250 g_00E04424, g_registryAtE02E88, g_00E044F0;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class LivingWorldPlayer;

struct Rva004EE501 : public _STL::_Vector_base<int, _STL::allocator<int> >
{
	__forceinline Rva004EE501() : _STL::_Vector_base<int, _STL::allocator<int> >(_STL::allocator<int>()) {}
	~Rva004EE501();
};

typedef _STL::map<int,void*> ScoreMapCtor;
typedef _STL::pair<const unsigned,void*> ScoreMapPair;
typedef _STL::_Rb_tree<unsigned,ScoreMapPair,_STL::_Select1st<ScoreMapPair>,_STL::less<unsigned>,_STL::allocator<ScoreMapPair> > ScoreMapDtor;
namespace _STL {template<> map<int,void*>::map();}
struct ScoreMapStorage {
 __forceinline ScoreMapStorage(){((ScoreMapCtor*)this)->ScoreMapCtor::map();}
 __forceinline ~ScoreMapStorage(){((ScoreMapDtor*)this)->ScoreMapDtor::~ScoreMapDtor();}
 char bytes[12];
};
class LivingWorldScoreKeeper : public Snapshot,
	public LivingWorldPhaseObserver,
	public LivingWorldBuildingObserver,
	public LivingWorldAutoResolveEventObserver,
	public LivingWorldRTSEventObserver,
	public LivingWorldRegionObserver,
	public LivingWorldPlayerObserver,
	public LivingWorldLogicObserver,
	public LivingWorldBuildingNuggetSpawnArmyObserver
{
public:
	LivingWorldScoreKeeper(int playerIndex, LivingWorldPlayer *player);
	virtual ~LivingWorldScoreKeeper();
 virtual void event0_1(int,int);
virtual void event1_0(Rva004E06FBPtrChase32Field*);virtual void event1_3(const Rva004E06FBPtrChase32Field*,int);
virtual void event2_2(int,LivingWorldBattle*,void*);virtual void event3_0(int,int);virtual void event3_1(int,LivingWorldBattle*);
virtual void event4_0(int,int,int);virtual void event5_0(Rva004EF2ABArg*);virtual void event6_1(LivingWorldLogic*);virtual void event7_3(CountInputPrefix*,void*);
protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
private:
	LivingWorldPlayer *m_player;		// +0x24
	Rva004EE501 m_28;
	_STL::vector<int> m_34, m_40, m_4C;
	_STL::vector<bool> m_58;
	int m_6C;
	long m_startTime;			// +0x70
	int m_74, m_78, m_7C;
	int m_80[5];
	int m_94, m_98;
	ScoreMapStorage m_9C;
	int m_A8, m_AC, m_B0;
	ScoreMapStorage m_B4, m_C0, m_CC;
	int m_D8, m_DC, m_E0, m_E4, m_E8, m_EC, m_F0;
	int m_playerIndex;			// +0xF4
	bool m_F8;
};

typedef char ScoreKeeperSize[sizeof(LivingWorldScoreKeeper)==0xFC?1:-1];

#define LW_OBSERVERS(offset) ((Rva005A0B4CList *)((char *)TheLivingWorldLogic + (offset)))

LivingWorldScoreKeeper::LivingWorldScoreKeeper(int playerIndex, LivingWorldPlayer *player) :
	m_player(player), m_6C(0), m_startTime(time(0)), m_74(0), m_78(-1), m_7C(-1),
	m_94(0), m_98(0), m_A8(0), m_AC(0), m_B0(0),
	m_D8(0), m_DC(0), m_E0(0), m_E4(0), m_E8(0), m_EC(0), m_F0(0),
	m_playerIndex(playerIndex), m_F8(false)
{
	for (int i = 0; i < 5; ++i)
		m_80[i] = 0;
	LW_OBSERVERS(0x1C)->append((Rva002BA8F1Listener *)(LivingWorldPhaseObserver *)this);
	LW_OBSERVERS(0x2C)->append((Rva002BA8F1Listener *)(LivingWorldAutoResolveEventObserver *)this);
	LW_OBSERVERS(0x3C)->append((Rva002BA8F1Listener *)(LivingWorldRTSEventObserver *)this);
	LW_OBSERVERS(0x4C)->append((Rva002BA8F1Listener *)(LivingWorldLogicObserver *)this);
	((Rva005A0B4CList *)&g_00E04424)->append((Rva002BA8F1Listener *)(LivingWorldBuildingObserver *)this);
	((Rva005A0B4CList *)&g_registryAtE02E88)->append((Rva002BA8F1Listener *)(LivingWorldRegionObserver *)this);
	((Rva005A0B4CList *)&g_00E044F0)->append((Rva002BA8F1Listener *)(LivingWorldBuildingNuggetSpawnArmyObserver *)this);
	((Rva005A0B4CList *)m_player)->append((Rva002BA8F1Listener *)(LivingWorldPlayerObserver *)this);
}

class Rva004EF2FAPrimary { public:void collectEndOfTurnStats(int); };

class Rva004EE5D2 {public:void rva004EE78A();void rva004EE5D2();};
LivingWorldScoreKeeper::~LivingWorldScoreKeeper(){((Rva004EE5D2*)this)->rva004EE78A();}
