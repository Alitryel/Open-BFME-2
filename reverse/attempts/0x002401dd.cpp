// ?rva002401DD@GameLogic@@QAEXPAVBfmeThingEC@@IH@Z
// partial score=0.833 date=2026-10-17
// ?rva002401DD@GameLogic@@QAEXPAVBfmeThingEC@@IH@Z
// partial score=0.8299 date=2026-10-14
// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// stlport
//
// ?init@GameLogic@@UAEXXZ @0x00243EE7 957B (Ghidra FUN_00643ee7, ret at
// 0x002442A3; next body 0x002442A4).
// Target evidence: the setName literals name every subsystem it creates and
// the global each is stored in: ThePartitionManager (0x009FE748, ctor
// 0x006253F0), TheShroudManager (0x009FE74C, ctor 0x007398D0) and
// TheCollisionManager (0x009FE754, ctor 0x00758250), each new'd at 0x14 bytes,
// then TheTerrainLogic (0x009FEC50, own virtual 0x38, SubsystemInterface at
// +4), TheLargeGroupAudio (0x009FE1A8, new 0x40 with ctor 0x0020DD59) and
// TheBuffLogic (0x009FF190, own virtual 0x40, base at +4); TheGhostObjectManager
// (0x009FF188) comes from own virtual 0x3C. setName is the out-of-line
// SubsystemInterface member 0x0006F3CC taking an AsciiString by value.
// Donor: BFME 1 game/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
// (GameLogic::init, same subsystem order, region zero, partition 7, sides
// list pair and the trailing field resets). BFME 2 differs from the donor
// with three owned members new'd at +0x170/+0x174/+0x178 between the region
// setup and the ghost manager, an out-of-line player-leave reset
// (0x0023D17D through TheGameLogic) and moved field offsets. Field names
// stay offset names: only the donor knows their meaning.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base
// wrapper (_List_iterator_base::operator!=, retail's copy is 0x006CFE40).
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
#include <map>
#include <set>
#include <string>
#include <vector>
#include <math.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "reference/shims/moduledata/Common/Snapshot.h"
#include "Code/Libraries/Source/profile/profile.h"

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
#include <cstddef>
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}


// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}

// STLport's __copy_trivial is a memmove wrapper the shipped header defined
// inline; retail calls it out of line at 0x000179B0 but the compiler still saw
// it could not throw: the vector copy at 0x002CFAB9 has no EH frame, and
// populateRandomSideAndColor frees its copied vector through the _M_start it
// already holds in a register (the copy never spills `this`).
namespace _STL { void *__copy_trivial(const void *__first, const void *__last, void *__result) throw(); }

typedef _STL::list<int, _STL::allocator<int> > IntList;

// ZH GameLogic.h ObjectTOCEntry: a thing template name and the 16-bit id
// save games store in its place. Retail list node: name at +8, id at +0xC
// (read by xferObjectTOC below). The allocator is a placeholder class: the
// list's out-of-line members fold onto addresses other lists already name.
struct ObjectTOCEntry
{
	AsciiString name;
	unsigned short id;
};
template <class T> class Rva00245F79Allocator : public _STL::allocator<T>
{
};
typedef _STL::list<ObjectTOCEntry, Rva00245F79Allocator<ObjectTOCEntry> > ObjectTOCList;

namespace _STL
{
template<> void _List_base<ObjectTOCEntry, Rva00245F79Allocator<ObjectTOCEntry> >::clear();
}

#include "Code/Libraries/Include/Lib/Region3D.h"

void setFPMode(void);

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface(void);
	virtual void init(void) = 0;
	virtual void s02(void); virtual void s03(void); virtual void s04(void);
	virtual void s05(void); virtual void s06(void); virtual void s07(void);
	virtual void s08(void);
	virtual void reset(void);                                            // +0x24
	virtual void update(void);                                           // +0x28
	void setName(AsciiString name);

private:
	int m_04;
	AsciiString m_name;
};

class PartitionManager : public SubsystemInterface
{
public:
	virtual void update(void);                                           // +0x28
	void setRegion(const Region3D *extent, float cellSize);
	void rva00625310(int value);
	void rva00625300(const Region3D *extent);
	void revealMapForPlayerPermanently(int playerIndex);

private:
	int m_impl[2];
};

class Rva006253F0 : public PartitionManager
{
public:
	Rva006253F0(void);
	virtual void init(void);
};

class Open2Store8F75D0 : public PartitionManager
{
public:
	Open2Store8F75D0(void);
	virtual void init(void);
};

class Rva00739720
{
public:
	void rva00739720(int value);
};

class CollisionManager : public SubsystemInterface
{
public:
	CollisionManager(void);
	virtual void init(void);

private:
	int m_impl[2];
};

class Rva00758210
{
public:
	void rva00758210(void);
};

class Rva006C0810
{
public:
	void rva006C0810(const Region3D *extent, float cellSize);
};

class Object;
class ThingTemplate;
class Matrix3D;

class Rva00240000;

class Object;
enum PathfindLayerEnum { LAYER_GROUND = 1 };

class TerrainLogic : public Snapshot, public SubsystemInterface
{
public:
	virtual bool loadMap(const AsciiString &filename, Rva00240000 *stream, bool query,
		bool newGame);                                                   // +0x10
	virtual void newMap(bool loadingSaveGame);                           // +0x14
	virtual float getGroundHeight(float x, float y, Coord3D *normal = 0) const;
	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer,
	                            Coord3D *normal = 0, bool clip = true) const;
	virtual void getExtent(Region3D *extent) const;                      // +0x20
	virtual void bridgeSlot09();
	virtual void bridgeSlot0A();
	virtual void bridgeSlot0B();
	virtual void bridgeSlot0C();
	virtual void bridgeSlot0D();
	virtual void bridgeSlot0E();
	virtual void bridgeSlot0F();
	virtual void bridgeSlot10();
	virtual void bridgeSlot11();
	virtual void bridgeSlot12();
	virtual void bridgeSlot13();
	virtual void bridgeSlot14();
	virtual void bridgeSlot15();
	virtual void bridgeSlot16();
	virtual void bridgeSlot17();
	virtual void bridgeSlot18();
	virtual void bridgeSlot19();
	virtual void bridgeSlot1A();
	virtual void bridgeSlot1B();
	virtual void bridgeSlot1C();
	virtual void bridgeSlot1D();
	virtual void bridgeSlot1E();
	virtual void bridgeSlot1F();
	virtual void bridgeSlot20();
	virtual void bridgeSlot21();
	virtual void bridgeSlot22();
	virtual void bridgeSlot23();
	virtual void bridgeSlot24();
	virtual void bridgeSlot25();
	virtual void bridgeSlot26();
	virtual void bridgeSlot27();
	virtual void bridgeSlot28();
	virtual void bridgeSlot29();
	virtual void bridgeSlot2A();
	virtual void bridgeSlot2B();
	virtual void bridgeSlot2C();
	virtual void bridgeSlot2D();
	virtual void bridgeSlot2E();
	virtual void addLandmarkBridgeToLogic(Object *bridgeObj); // +0xBC; donor name
	void rva002817F2(const AsciiString &filename);
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
	void rva0027D3D9(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
	void rva00283642(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
	void rva00280176(const ThingTemplate *tt, const Coord3D *pos, const Matrix3D *mtx, float scale);
};

class BuffLogic : public Snapshot, public SubsystemInterface
{
};

class GhostObjectManager
{
public:
	virtual ~GhostObjectManager(void);
	virtual void g01(void); virtual void g02(void); virtual void g03(void);
	virtual void reset(void);                                            // +0x10
	virtual void setLocalPlayerIndex(int playerIndex);                   // +0x14
};

class Pathfinder
{
public:
	void rva002E8DAA(void);
	void rva002F0F07(void);
	void AddObjectToPathfindMap(Object *obj);
};

// loadAllObjects reads the three tree names at +0xDC..E4 and scale at +0xE8.
// The field offsets are retail facts; the tree meanings follow the donor.
class AIData
{
	char m_pad00[0xd8];
public:
	bool m_d8;
	AsciiString m_treeName[3];
	float m_treeScale;
	bool m_ec;
};

class AI : public SubsystemInterface
{
public:
	Pathfinder *pathfinder(void) { return m_pathfinder; }
	const AIData *getAiData(void) const { return m_aiData; }

private:
	int m_0c;
	Pathfinder *m_pathfinder;                                            // +0x10
	char m_pad14[0x18 - 0x14];
	AIData *m_aiData;
};

class AssetList;
struct AssetLoadMode;

// 0x00203BB1 is rowed as a free function but runs on TheScriptEngine; the
// member-pointer union loads ecx for it (BFME 1 GameLogic::update precedent).
void Rva00203BB1ForceAppContinue(void);

class ScriptEngine : public SubsystemInterface
{
public:
	void rva00205358(AssetList *assets, AssetLoadMode *mode);
	void rva00207C02(void);
	void rva002047CF(void);
	void forceAppContinue(void)
	{
		union
		{
			void (*entry)(void);
			void (ScriptEngine::*method)(void);
		} fn;
		fn.entry = &Rva00203BB1ForceAppContinue;
		(this->*fn.method)();
	}
};

class Rva00203B08
{
public:
	bool rva00203AE5(void);
};

class Overridable
{
public:
	Overridable *deleteOverrides(void);
};

struct Rva00200BD9Holder;

class StatsCollector;

class Rva0048BA39StatsCollector
{
public:
	~Rva0048BA39StatsCollector(void);
};

class Rva000427195
{
public:
	void rva003A2A41(void);
};

class Rva00240CAB
{
public:
	void rva0024191A(void);
};

class Rva004DFC20
{
public:
	void clear(void);
};

class Rva0053F1ECSub
{
public:
	void note(int buckets);
};

class Rva0023E7D9
{
public:
	void rva0023E7D9(void);
	void rva0023F88C(bool loadingSaveGame);
};

class Rva0035A1D8
{
public:
	void rva0035A1D8(void);
};

class DOTManager
{
public:
	void rva0043B725(void);
	void update(void);
};

class Rva00439920
{
public:
	void rva00439920(void);
};

class LargeGroupAudio : public SubsystemInterface
{
public:
	LargeGroupAudio(void);
	virtual void init(void);

private:
	int m_body[13];
};

class Rva0035A2DC
{
public:
	void rva0035A2DC(Region3D *extent, float cellSize);
};

class Rva00359E13
{
public:
	Rva00359E13(void);
	void rva0035AA3E(void);

private:
	int m_body[17];
};

class Rva0043B660
{
public:
	Rva0043B660(void);
	void rva000B3FD0(void);

private:
	int m_body[4];
};

class Rva0043821C
{
public:
	void rva0043821C(void);
};

class Rva00243177
{
public:
	Rva00243177(void);
	void rva00439965(void);

private:
	int m_body[6];
};

class Dict;

// One 16-byte record of the indexed team list at SidesList+0xF44: +0 links
// the live list (record 0 heads it), +6 is the per-key chain link that
// TeamsInfoRec::removeTeam (0x0032C26D) repairs.
struct TeamsInfoNode
{
	short m_previous;
	short m_next;
	short m_chainNext;
	short m_chainPrevious;
	int m_entry;
	int m_extra;
};

class TeamsInfoRec
{
public:
	void removeTeam(int index);
	TeamsInfoNode *getNode(int index) { return &m_nodes[index]; }
	int addTeam(const Dict *d);

private:
	_STL::map<_STL::pair<AsciiString,AsciiString>,int> m_tree;
	_STL::vector<TeamsInfoNode> m_nodes;
	short m_count;short m_freeHead;
};

class Dict
{
public:
	Dict(int numPairs = 0);
	~Dict() { releaseData(); }
	bool getBool(int key, bool *exists = 0) const;
	float getReal(int key, bool *exists = 0) const;
	AsciiString getAsciiString(int key, bool *exists = 0) const;
	void setInt(int key, int value);
	void setBool(int key, bool value);
	void setAsciiString(int key, const AsciiString &value);
	void setUnicodeString(int key, const UnicodeString &value);
	void clear(void);

private:
	void releaseData(void);

	void *m_data;
};

class SidesInfo
{
public:
	Dict *getDict(void) { return &m_dict; }

	void *m_pBuildList;
	Dict m_dict;                                                         // +0x04
	char m_pad08[0x60 - 8];
};

class SidesList
{
public:
	void rva0032D554(void);
	void rva0032F84F(void);
	void discardOverriddenScriptsAndTeams(void);
	void rva0032FF91(void);
	void addMusicScriptReference(void);
	TeamsInfoRec *getTeamInfo(void) { return &m_teams; }
	int addSide(const Dict *d);
	SidesInfo *findSideInfo(AsciiString name, int *index = 0);
	void addTeam(const Dict *d) { m_teams.addTeam(d); }
	void rva0032E02B(void);
	int getNumSides(void) const { return m_numSides; }
	// The header body the compiler sees but does not inline (retail calls the
	// 0x002035BA copy): knowing it stores nothing, SetUpCampaignPlayers keeps
	// TheSidesList in esi across the call. The copy emitted here is
	// byte-identical to retail's.
	__declspec(noinline) SidesInfo *getSideInfo(int side)
	{
		if (side >= 0 && side < m_numSides)
			return &m_sides[side];
		return 0;
	}

	char m_pad000[0x3c];
	int m_numSides;                                                      // +0x3C
	SidesInfo m_sides[(0xf44 - 0x40) / 0x60];                            // +0x40
	char m_padSides[(0xf44 - 0x40) % 0x60];
	TeamsInfoRec m_teams;                                                // +0xF44
	char m_padF60[0xf7c - 0xf60];
	bool m_f7c;
};

class GlobalData
{
public:
	char m_pad000[0xc];
	AsciiString m_mapName;
	char m_pad010[0x26 - 0x10];
	bool m_26;
	char m_pad027[0xd4 - 0x27];
	float m_d4;
	float m_d8;
	char m_pad0DC[0x9c1 - 0xdc];
	bool m_9c1;
	char m_pad9C2[0xaf5 - 0x9c2];
	bool m_af5;
	char m_padAF6[0xbd0 - 0xaf6];
	int m_bd0;
	char m_padBD4[0xc18 - 0xbd4];
	unsigned int m_c18;
	char m_padC1C[0xc30 - 0xc1c];
	int m_c30;
	char m_padC34[0xd45 - 0xc34];
	bool m_d45;
	char m_padD46[0xd48 - 0xd46];
	int m_d48;
	char m_padD4C[0xddc - 0xd4c];
	bool m_ddc;
	char m_padDDD[0xe94 - 0xddd];
	int m_e94;
	char m_padE98[0x1110 - 0xe98];
	bool m_1110;
	char m_pad1111[0x123d - 0x1111];
	bool m_123d;
};

class GameInfo;
class LoadScreen;
class Object;
class MapObject;

// One record per object the map loader created: the object and the map
// object it came from (8 bytes; push_back 0x00539A2E).
struct Rva0024622FEntry
{
	Object *obj;
	MapObject *mapObj;
};

class GameMessage;
class BfmeThingEC;
struct Rva00241529Record;
struct PlayerLeaveStatus;
class PlayerTemplate;

enum KindOfType
{
	KINDOF_INVALID = -1
};

class UpdateModule;
typedef _STL::vector<UpdateModule *> UpdateModuleList;

// The object embedded at GameLogic+0x184 (0x2C bytes); its member 0x0040CA98
// never reads this.
class Rva0040CA98
{
public:
	void rva0040CA98(void);

private:
	char m_body[0x2c];
};

enum ObjectID
{
	INVALID_ID = 0
};

// Retail folds this record's vector growth onto the no-EH STLport provider.
// Keep that provider's algorithm visible without emitting an EH-enabled copy.
namespace _STL {
template<> inline void vector<Rva0024622FEntry>::_M_insert_overflow(
    pointer position, const Rva0024622FEntry &value, const __false_type &,
    size_type fillLength, bool atEnd)
{
    const size_type oldSize = size();
    const size_type length = oldSize + (max)(oldSize, fillLength);
    pointer start = this->_M_end_of_storage.allocate(length);
    pointer finish = start;
    finish = __uninitialized_copy(this->_M_start, position, start, __false_type());
    if (fillLength == 1) {
        _Construct(finish, value);
        ++finish;
    } else
        finish = __uninitialized_fill_n(finish, fillLength, value, __false_type());
    if (!atEnd)
        finish = __uninitialized_copy(position, this->_M_finish, finish, __false_type());
    _M_clear();
    _M_set(start, finish, start + length);
}
}

class GameLogic : public SubsystemInterface
{
public:
	virtual void init(void);
	virtual void v11(void); virtual void v12(void);
	virtual void update(int phase);                                      // +0x34
	virtual TerrainLogic *createTerrainLogic(void);                      // +0x38
	virtual GhostObjectManager *createGhostObjectManager(void);          // +0x3C
	virtual BuffLogic *createBuffLogic(void);                            // +0x40

	virtual void reset(void);

	void rva00240E18(bool loadingSaveGame);
	void rva0023D17D(void);
	void destroyAllObjectsImmediate(void);
	void rva00376D49(void);
	void rva00246422(bool dontCreate);
	void rva00248558(bool loadingSaveGame);
	void startNewGame_Init(bool loadingSaveGame);
	void rva002469A5(bool loadingSaveGame, int *progress);
	void startNewGame_PlaceMPBuildings(bool loadingSaveGame, int *progress);
	void rva00248278(bool loadingSaveGame);
	void rva0023F52C(bool loadingSaveGame);
	void rva0024004D(bool loadingSaveGame);
	void loadMapINI(AsciiString mapName);
	void rva0023E628(AsciiString mapName);
	void CreateMPPlayers(bool isSkirmish, int progress);
	void CreateWOTRMPPlayers();
	void SetUpCampaignPlayers(void);
	void rva0023E0C7(void);
	void lastHeardFrom(int playerIndex);
	bool rva001DCD1C(void);
	void rva0024622F(bool loadingSaveGame);
	void setWidth(float width) { m_width = width; }
	void setHeight(float height) { m_height = height; }
	bool rva0023C8DA(unsigned char loadingSaveGame);
	Object *findObjectByID(ObjectID id);
	void loadAllObjects(_STL::vector<Rva0024622FEntry> *created, const KindOfType *excludeKind,
		const KindOfType *requireKind, bool dontCreate);
	void startNewGame_OpenLoadScreen(bool loadingSaveGame, GameInfo *game);
	bool isInMultiplayerGame(void);
	bool rva00085124(void);
	void formatPlayerStartWaypointName(AsciiString *name);
	void ProcessCRC(unsigned int crc, int player, unsigned int frame, GameMessage *message,
		bool forced, BfmeThingEC *stream);
	void rva0023F8DA(void);
	const AsciiString &rva0023FB58(int index);
	PlayerLeaveStatus *getPlayerLeaveStatus(int playerIndex);
	void rva002401DD(BfmeThingEC *stream, unsigned int frame, int player);
	bool rva002259F3(void);
	bool rva0042219(void);
	void processCommandList(void);
	void processDestroyList(void);
	void logicMessageDispatcher(GameMessage *msg, void *userData);
	unsigned int getCRC(int mode);
	void rva00240EBC(void);

	Object *getFirstObject(void) const { return m_objList; }
	ObjectTOCEntry *findTOCEntryByName(AsciiString name);
	void addTOCEntry(AsciiString name, unsigned short id);
	void xferObjectTOC(Xfer *xfer);

private:
	LoadScreen *getLoadScreen(bool saveGame);

public:

	char m_pad00C[0x10 - 0x0c];
	char m_10[0x24 - 0x10];
	char m_24[0x30 - 0x24];
	float m_width;
	float m_height;
	unsigned int m_38;
	char m_pad03C[0x40 - 0x3c];
	unsigned int m_40;
	unsigned int getFrame(void) const { return m_40; }
	bool m_44;
	char m_pad045[0x48 - 0x45];
	Rva00241529Record *m_48;
	IntList::iterator m_4c;
	IntList m_50;
	AsciiString m_54;
	_STL::vector<AsciiString> m_58;
	AsciiString m_64;
	AsciiString m_68;
	bool m_6c;
	bool m_6d;
	char m_pad06E[0x70 - 0x6e];
	bool m_70;
	bool m_71;
	bool m_72;
	char m_pad073[0x94 - 0x73];
	int m_94;
	bool m_98;
	bool m_99;
	bool m_9a;
	bool m_9b;
	bool m_9c;
	bool m_9d;
	bool m_9e;
	bool m_9f;
	int m_a0;
	int m_a4;
	bool m_a8;
	char m_pad0A9[0xac - 0xa9];
	Object *m_objList;
	char m_pad0B0[0xb4 - 0xb0];
	char m_b4[0xc8 - 0xb4];
	UpdateModuleList m_updates[4];                                       // +0xC8
	UpdateModuleList m_sleeping;                                         // +0xF8
	UpdateModule *m_104;
	char m_pad108[0x10c - 0x108];
	int m_10c;
	int m_110;
	int m_114;
	int m_118;
	bool m_11c;
	bool m_11d;
	char m_pad11E[0x120 - 0x11e];
	LoadScreen *m_120;
	bool m_124;
	bool m_125;
	bool m_126;
	bool m_127;
	bool m_128[8];
	int m_130[8];
	bool m_150;
	char m_pad151[0x154 - 0x151];
	Object *m_154;
	Object *m_158;
	Object *m_15c;
	Object *m_160;
	_STL::vector<void *> m_164;
	Rva00359E13 *m_170;
	Rva0043B660 *m_174;
	Rva00243177 *m_178;
	int m_17c;
	int m_180;
	Rva0040CA98 m_184;
	int m_1b0;
	int m_1b4;
	int m_1b8;
	bool m_1bc;
	char m_pad1BD[0x1c0 - 0x1bd];
	ObjectTOCList m_objectTOC;
	char m_pad1C4[0x2a4 - 0x1c4];
	int m_2a4;
};

extern PartitionManager *ThePartitionManager;
extern PartitionManager *TheShroudManager;
class BfmeTaintManager;
extern BfmeTaintManager *TheTaintManager;
extern CollisionManager *TheCollisionManager;
extern GlobalData *TheWritableGlobalData;
extern GhostObjectManager *TheGhostObjectManager;
extern TerrainLogic *TheTerrainLogic;
LargeGroupAudio *TheLargeGroupAudio = 0;
BuffLogic *TheBuffLogic = 0;
extern SidesList *TheSidesList;
extern GameLogic *TheGameLogic;
extern AI *TheAI;
extern ScriptEngine *TheScriptEngine;
extern StatsCollector *g_00E032F8;
extern Rva00200BD9Holder *g_rva00200BD9Holder;

// 0x0004224C (rowed as a this-returning member) is the out-of-line
// constructor of a scope guard: when TheGameLogic exists it sets the FP mode
// on the first nesting level and counts TheGameLogic+0x1B4 up. The matching
// count-down (0x00042212) is expanded at scope exit. Both are defined in the
// class: 0x00248558 keeps the guard in its parameter slot, which MSVC 7.1
// does only for an empty class whose constructor and destructor it can see.
class Rva000421FD
{
public:
	void rva000421FD(void);
};

class Rva0004224C
{
public:
	Rva0004224C(void)
	{
		if (TheGameLogic)
			((Rva000421FD *)TheGameLogic)->rva000421FD();
	}
	~Rva0004224C(void)
	{
		if (TheGameLogic)
			TheGameLogic->m_1b4--;
	}
};


class Team;

// The +0x08 member of Player: 0x003805BB takes a point value and a flag
// (Player::addSkillPointsForKill passes true), 0x002E6A93 stores its +0x18.
// 0x003805BB is rowed as Rva00380200::rva003805BB (Rva00380200Getter.cpp).
class Rva00380200 { public: bool rva003805BB(float value, bool flag); };

class Rva003805BB
{
public:
	void rva002E6A93(int value);

	char m_pad00[0x14];
	int m_14;
	int m_18;
};

enum PlayerType
{
	PLAYER_HUMAN
};

class Player
{
public:
	Team *getDefaultTeam(void) const { return m_defaultTeam; }
	PlayerType getPlayerType(void) const { return m_playerType; }
	int getPlayerIndex(void) const { return m_playerIndex; }
	int iterateObjects(int (*func)(Object *obj, void *userData), void *userData) const;

	char m_pad00[0x8];
	Rva003805BB m_skillPoints;
	char m_pad24[0x34 - 0x24];
	PlayerTemplate *m_34;
	char m_pad38[0x4c - 0x38];
	AsciiString m_4c;
	char m_pad50[0x54 - 0x50];
	int m_playerIndex;                                                   // +0x54
	char m_pad58[0x5c - 0x58];
	PlayerType m_playerType;
	char m_pad60[0x2ec - 0x60];
	Team *m_defaultTeam;
	char m_pad2F0[0x3bc - 0x2f0];
	int m_3bc;
	char m_pad3C0[0x4ac - 0x3c0];
	int m_4ac;
};

enum NameKeyType
{
	NAMEKEY_INVALID
};

class PlayerList : public SubsystemInterface
{
public:
	virtual void p0b(void); virtual void p0c(void);
	virtual void p0d(void); virtual void p0e(void);
	virtual void newMap(void);                                           // +0x3C

	Player *getNeutralPlayer(void) const { return m_neutralPlayer; }
	Player *getLocalPlayer(void) const { return m_local; }
	Player *getNthPlayer(int index);
	Player *findPlayerWithNameKey(NameKeyType key);
	void setLocalPlayer(Player *player);
	Team *validateTeam(AsciiString owner, MapObject *mapObj);

private:
	char m_pad0C[0x10 - 0x0c];
	Player *m_local;
	char m_pad14[0x18 - 0x14];
	Player *m_neutralPlayer;
};

enum RecorderModeType
{
	RECORDERMODETYPE_RECORD,
	RECORDERMODETYPE_PLAYBACK,
	RECORDERMODETYPE_NONE
};

class File;

class RecorderClass : public SubsystemInterface
{
public:
	bool isMultiplayer(void);
	RecorderModeType getMode(void);
	void logCRCMismatch(void);
	void rva0037BE15(File *output, unsigned int frame);
	void initControls(void);

	char m_pad00C[0xe68 - 0xc];
	int m_e68;
	int m_e6c;
};

class GameTextInterface
{
public:
	virtual void g00(void) = 0;
	virtual void g01(void) = 0;
	virtual void g02(void) = 0;
	virtual void g03(void) = 0;
	virtual void g04(void) = 0;
	virtual void g05(void) = 0;
	virtual void g06(void) = 0;
	virtual void g07(void) = 0;
	virtual void g08(void) = 0;
	virtual void g09(void) = 0;
	virtual void g10(void) = 0;
	virtual void g11(void) = 0;
	virtual void g12(void) = 0;
	virtual void g13(void) = 0;
	virtual void g14(void) = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0; // +0x3C
	virtual void g16(void) = 0;
	virtual void g17(void) = 0;
	virtual void g18(void) = 0;
	virtual void initMapStringFile(const AsciiString &filename) = 0;  // +0x4C
};
extern PlayerList *ThePlayerList;
extern RecorderClass *TheRecorder;
extern GameTextInterface *TheGameText;
extern int g_value12A6F38;
extern bool ignoreCRCMismatches;

class File
{
public:
	virtual void f00(void);
	virtual bool open(const char *filename, int access);
	virtual void close(void);                                            // +0x08
	virtual int read(void *buffer, int bytes);
	virtual int write(const void *buffer, int bytes);                    // +0x10
};

class ScriptActions
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
	virtual void s0c(); virtual void s0d(); virtual void s0e();
	virtual void closeWindows(bool suppressNewWindows);                  // +0x3C
};
extern ScriptActions *TheScriptActions;

// 0x002036B4, a 12-byte member of the object in TheScriptEngine's slot.
class Rva002036B4GlobalCopier
{
public:
	void apply(void);
};

void Rva00437E84(int type, const UnicodeString &title, const UnicodeString &text);
File *createMemoryReadFile(char *buffer, int size);
void rva0060DFB5(File *input, File *output);

extern "C" __declspec(dllimport) int __stdcall GetComputerNameA(char *buffer, unsigned long *size);

// 0x00A03204: tag the report as an intentionally faked desync.
extern bool g_fakeDesync;
// 0x00A02D89: also write the raw CRC stream next to the text report.
extern bool TheBinaryDeepCRC;

class BfmeThingEC
{
public:
	virtual void e00(void);
	int bfmeTakeEC(int *size);

	AsciiString m_04;
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access, int bufferSize);
	bool doesFileExist(const char *filename) const;
};
extern FileSystem *TheFileSystem;

void GameLogic::rva002401DD(BfmeThingEC *stream, unsigned int frame, int player)
{
	m_71 = true;
	if (ignoreCRCMismatches && g_value12A6F38 != m_40)
		return;
	if (!m_1bc)
	{
		m_1bc = true;
		TheRecorder->logCRCMismatch();
		TheScriptActions->closeWindows(true);
		if (!TheRecorder || TheRecorder->getMode() != RECORDERMODETYPE_PLAYBACK || g_value12A6F38 == m_40)
			Rva00437E84(4, TheGameText->fetch("GUI:DesyncTitle"), TheGameText->fetch("GUI:DesyncText"));
		m_1b8 = 0;
		if (!TheRecorder || TheRecorder->getMode() != RECORDERMODETYPE_PLAYBACK || g_value12A6F38 == m_40)
			((Rva002036B4GlobalCopier *)TheScriptEngine)->apply();
	}
	if (!stream)
		return;
	const char *map;
	const char *slash = TheWritableGlobalData->m_mapName.reverseFind('\\');
	if (slash)
		map = slash + 1;
	else
		_ReadWriteBarrier();
	_ReadWriteBarrier();
		map = "";
	if (0) throw 1;

	if (!stream)
		return;

	AsciiString playerName(ThePlayerList->getLocalPlayer()->m_4c);
	if (playerName.isEmpty())
	{
		char computerName[260] = { 0 };
		struct { unsigned long v; unsigned char pad[4]; } sizePad;
		sizePad.v = 256;
		{
			GetComputerNameA(computerName, (unsigned long *)&sizePad.v);
			playerName = computerName;
		}
	}

	AsciiString frameName;
	AsciiString filename;
	if ((1 ? stream->m_04.str() : stream->m_04.str()))
		frameName.format("Frame%s", stream->m_04.str());
	else
		frameName.format("Frame%d", frame);

	if (frame > 0)
		filename.format("DESYNC-%s-%s-%s.txt", frameName.str(), map, playerName.str());
	else
		filename.format("DESYNC-%s-%s.txt", map, playerName.str());

	File *output = TheFileSystem->openFile(filename.str(), 0x2a, 0);
	if (output)
	{
		int size;
		char *buffer = (char *)stream->bfmeTakeEC(&size);
		File *input = createMemoryReadFile(buffer, size);
		if (input)
		{
			AsciiString text;
			if (frame > 0)
			{
				if (g_fakeDesync)
					text.format("*** Frame #%d -- THIS IS A FAKE DESYNC THAT WAS TRIGGERED INTENTIONALLY BY THIS PLAYER! IGNORE!\n\n", frame);
				else if (g_value12A6F38 == m_40)
					text.format("*** Frame #%d -- THIS IS A FORCED DESYNC TRIGGERED ON FRAME %d USING COMMANDLINE -forceDesyncOnFrame %d! IGNORE!!!!\n\n", frame, m_40);
				else
					text.format("Frame #%d\n\n", frame);
				output->write(text.str(), text.getLength());
			}
			text = m_54;
			output->write(text.str(), text.getLength());
			for (unsigned int i = 0; i < m_58.size(); ++i)
			{
				text = rva0023FB58(i);
				output->write(text.str(), text.getLength());
			}
			text = m_64;
			output->write(text.str(), text.getLength());
			text = m_68;
			output->write(text.str(), text.getLength());
			text.format("\n");
			output->write(text.str(), text.getLength());
			text.format("\n--------------------------------------------------------\nREPLAY FILE\n---------------------------------------------------------\n");
			output->write(text.str(), text.getLength());
			TheRecorder->rva0037BE15(output, frame);
			text.format("---------------------------------------------------------\n\n");
			output->write(text.str(), text.getLength());
			rva0060DFB5(input, output);
			input->close();
			output->close();
			if (TheBinaryDeepCRC)
			{
				if (frame > 0)
					filename.format("BIN_DESYNC-%s-%s-%s.bin", frameName.str(), map, playerName.str());
				else
					filename.format("BIN_DESYNC-%s-%s.bin", map, playerName.str());
				output = TheFileSystem->openFile(filename.str(), 0x4a, 0);
				if (!output)
					return;
				output->write(buffer, size);
				output->close();
			}
			free(buffer);
		}
	}
}
