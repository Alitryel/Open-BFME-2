// cl: /I. /ICode/Libraries/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist
// GameLogic::DoXfer (GameLogicSnapshot receiver), retail 0x0024797E, 2195 B.
// The frame layout depends on BFME 2's rts::hash<AsciiString>: hashing the key by
// const reference through _STL::hash<const char *> on str() makes the out-of-line
// buildable-map ++ (0x411084, via _M_skip_to_next 0x3F7925 and _M_bkt_num_key
// 0x223149) a non-throwing call, so the hash iterator does not conflict with the
// object-load guard and shares its stack colour as in retail. Zero Hour's by-value
// key (copy and releaseBuffer) or an opaque declaration leaves ++ may-throw.
// stlport
//
// GameLogic::DoXfer, retail 0x0024797E (2195 B, RET 4; WB 0x00D097E0, GameLogic.cpp 7168..7472).
// The receiver is the Snapshot sub-object at GameLogic+0x0C (the body subtracts 0x0C
// to reach the logic for its out-of-line calls). Structure follows the WB debug body and
// Zero Hour's GameLogic::xfer; BFME 2's save format adds the skirmish game info and
// preferences block, the buildable overrides, the control bar overrides and the
// Snapshot-valued sub-systems. Members keep offset names (receiver-relative offsets
// are the Snapshot view's, GameLogic offset = receiver offset + 0x0C).
#include "ascii_string.h"
#include "unicode_string.h"
#include <set>
#include <map>
#include <hash_map>

class Xfer;
class Object;
struct Rva00243B52DestroyEntry;
#include "reference/shims/moduledata/Common/Snapshot.h"

struct XferVersionInfo
{
	XferVersionInfo(unsigned char a, unsigned char b) : m_a(a), m_b(b) {}
	unsigned char m_a, m_b;
};

#include "Lib/Coord3DBase.h"
// Suppress this TU's non-retail copy of ?begin@?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@QBEPBQAXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void * const * vector<void *,allocator<void *> >::begin() const; }

class Xfer
{
public:
	virtual void slot00();
	virtual bool isLoading();
	virtual bool isStoring();
	virtual bool isCRC();
	virtual bool isLightCRC();
	virtual void beginBlock(const char *name);
	virtual void endBlock();
	virtual void skipBlock(const char *name);
	virtual void slot20();
	virtual void slot24();
	virtual void xferVersion(XferVersionInfo *version);
	virtual void slot2C();
	virtual void xferSnapshot(Snapshot *snapshot);
	virtual void slot34(); virtual void slot38(); virtual void slot3C(); virtual void slot40();
	virtual void slot44(); virtual void slot48(); virtual void slot4C(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual Xfer &xferCoord3D(Coord3DBase *value);
	virtual void slot64();
	virtual Xfer &xferUnicodeString(UnicodeString *value);
	virtual Xfer &xferAsciiString(AsciiString *value);
	virtual Xfer &slot70();
	virtual Xfer &slot74();
	virtual Xfer &xferUnsignedInt(unsigned int *value);
	virtual Xfer &xferInt(int *value);
	virtual Xfer &xferUnsignedShort(unsigned short *value);
	virtual Xfer &slot84();
	virtual Xfer &slot88();
	virtual Xfer &slot8C();
	virtual Xfer &xferBool(bool *value);
};


// BFME 2's native lookup at 0x00049DC5 uses the ObjectID enum and a map
// receiver at +0xB4. The provider's existing accessed prefix is shared here;
// complete GameLogic and map extents remain unreconstructed. Pointer-only
// callers do not construct these views or depend on their sizeof.
// Reference-backed consumers may already have the same ObjectID enum.
#ifndef _GAME_TYPE_H_
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
#endif

class Xfer;
class GameMessage;
class BfmeThingEC;
class Object;
class Drawable;
class Rva00439E0C;
class AsciiString;
class CommandButton;
class WindowLayout;
class Rva0023E928;
class UnicodeString;
class TerrainResourceManager;

// class-gate: allow ObjectIdNode carried with the private GameLogic view below (same layout as the shared view)
struct ObjectIdNode
{
	char pad[8];
	Object *object;
};

// class-gate: allow ObjectIdMap carried with the private GameLogic view below (same layout as the shared view)
class ObjectIdMap
{
public:
	ObjectIdNode *find(const ObjectID &id);
};

// The network code reads the command timestamp at +0x38 and Zero Hour's
// frame counter at +0x40 (ConnectionManager::update 0x004D342A, among others).
// StealthUpdate::disguiseAsObject (0x00373DF0) reads the manager at +0x178
// whose call 0x00439E0C takes the disguised object. The spell store's show
// (finishShowPurchaseScience 0x0043CB48) reads the end flag at +0x6D and
// the game mode at +0x110.
// InGameUI::addFloatingText (0x002A0D19) gates on the byte at +0x9A, Zero
// Hour's getDrawIconUI.
// The object list head is at +0xAC: getFirstObject (0x0023CAD2) returns it and
// prepareLogicForObjectLoad (0x00242C86) walks it inline.
// ScoreKeeper::addObjectLost (0x0039CF73) tests the scoring byte at +0x98
// first, as Zero Hour's isScoringEnabled does.
// GameClient::update (0x0023BEE8) reads the byte at +0x125, next to the pause
// byte isGamePaused (0x0023CD97) returns from +0x124, and skips the drawable,
// terrain and display updates while it is set.
struct PlayerLeaveStatus;
struct ObjectTOCEntry;
// class-gate: allow GameLogic shared view lacks getObjectCount (0x0023CFCE), xferObjectTOC and
// findTOCEntryByName that this body calls; adding them to the shared header moves other units' slots
class GameLogic
{
	char pad[0x38];
	unsigned int m_timestamp;
	char pad3C[0x40 - 0x3C];
	unsigned int m_frame;
	char pad44[0x6D - 0x44];

public:
	bool m_6d; // +0x6D

private:
	char pad6E[0x98 - 0x6E];
	bool m_isScoringEnabled; // +0x98
	char pad99[0x9A - 0x99];
	bool m_drawIconUI; // +0x9A
	char pad9B[0xAC - 0x9B];
	Object *m_firstObject; // +0xAC, the head getFirstObject returns
	char padB0[0xB4 - 0xB0];
	ObjectIdMap m_map;
	char padB5[0x110 - 0xB5];

public:
	int m_110; // +0x110

	// Native AIUnitBuilder598052 and listener239457 compare this word.
	int m_114; // +0x114; precise mode meaning remains unresolved

private:
	char pad118[0x125 - 0x118];
	bool m_flag125;
	char pad126[0x170 - 0x126];
	// Native handleBuildPlacements (0x002A21E1) enumerates resource claimants
	// through this manager; WorldBuilder's corresponding field is at +0x174.
	TerrainResourceManager *m_resourceManager;
	char pad174[0x178 - 0x174];
	Rva00439E0C *m_manager178;
	char pad17C[0x1B8 - 0x17C];
	// Window cleanup 0x00376D49 owns this layout and clears the pending byte.
	// BFME1's closeWindows supplies its purpose; offsets are native BFME2.
	WindowLayout *m_background; // +0x1B8
	bool m_backgroundPending; // +0x1BC

public:
	void logicMessageDispatcher(GameMessage *, void *); // Native 0x00377613
	void rva0023F8DA(); // Verified native 0x0023F8DA game-over details
	void rva0023DA49(); // Verified native 0x0023DA49 battle-complete wrapper
	void rva0023DA4E(); // Verified native 0x0023DA4E battle-complete gate
	void selectObject(Object *, bool, unsigned int, bool); // Verified native 0x0023C924
	void ProcessCRC(unsigned int, int, unsigned int, GameMessage *, bool, BfmeThingEC *); // Verified native 0x00241529
	void rva0023D080(int); // Verified native 0x0023D080, forwards to the void ArmySummarySystem::CallArmyToEngageInBattleByID
	void CallPlayerGiveMoney(int, int, int); // Verified native 0x0023D793
	bool rva00085124();	// 0x00085124; verified mode 4-or-7 predicate
	bool isInMultiplayerGame();	// 0x00042235
	bool rva0042219();	// 0x00042219, mode gate rejecting 9, 4 and 7
	bool rva001DCD1C();	// 0x001DCD1C, mode 8 or mode 9 with +0x114 != 3
	void rva0023CD9E(bool paused, int pauseMode, bool affectMouse);	// 0x0023CD9E
	Object *findObjectByID(ObjectID id);
	void rva0023CFE4(Xfer *xfer); // 0x0023CFE4, Version1 plus native snapshot at +0x184
	void rva0023D033(); // 0x0023D033, native +0x184 cleanup forwarder
	const AsciiString *rva0023D05F(int value);	// 0x0023D05F, +0x184 army name by id
	const AsciiString *rva0023D06A(int value);	// 0x0023D06A, +0x184 army banner name by id
	int rva0023D08B(int value);	// 0x0023D08B, existing +0x184 forwarder
	void rva0023D0C2(Object *obj, int handle);	// 0x0023D0C2
	void TransitionFromLivingWorldTacticalBattle(); // 0x0023D0CD; timeline continue callback
	Object *getFirstObject();	// 0x0023CAD2
	int rva0023CAD9();	// 0x0023CAD9, next ObjectID for Object::Object 0x00298EA9
	void registerObject(Object *obj);	// 0x00242AE9, called by Object::Object 0x00298EA9
	void destroyObject(Object *obj);	// 0x00242C09
	void sendObjectDestroyed(Object *obj);	// 0x0023CD67, called by Object::~Object 0x00299CE4
	void rva0023CF8B();	// 0x0023CF8B, called by AptLoadScreen::init 0x0043A5F6
	void deselectObject(Object *obj, unsigned int playerMask, bool affectClient);	// 0x0023C9F8
	void bindObjectAndDrawable(Object *obj, Drawable *draw);	// 0x0023CD4A
	void rva00376E92(bool first, bool second);	// 0x00376E92
	void rva00376D49();	// 0x00376D49, window cleanup, donor closeWindows
	void rva00248558(bool fromSave);	// 0x00248558, verified new-game/load pass
	unsigned char isGamePaused();	// 0x0023CD97
	void deleteLoadScreen();	// 0x002423E3
	void processDestroyList();	// 0x002413DF
	unsigned int getObjectCount();
	void xferObjectTOC(Xfer*);
	ObjectTOCEntry*findTOCEntryByName(AsciiString);
	void prepareLogicForObjectLoad();	// 0x00242C86
	void processProgressComplete(int playerID);	// 0x0023D76E
	void CreateWOTRMPPlayers(); // 0x0023E99A; verified provider, campaign caller 0x0052C45E
	void setControlBarOverride(const AsciiString &commandSetName, int slot, const CommandButton *commandButton);	// 0x0024792F
	void ProcessSaveGameCommand(Rva0023E928 *msg, bool frozen);	// 0x00240866, multiplayer save request handler
	void rva0023D30F(int a, int b, UnicodeString *name);	// 0x0023D30F, thiscall spelling of the stdcall Rva0023D30FCall
	bool isScoringEnabled() const { return m_isScoringEnabled; }
	bool getFlag125() const { return m_flag125; }
	unsigned int getTimestamp() const { return m_timestamp; }
	unsigned int getFrame() const { return m_frame; }
	bool getDrawIconUI() const { return m_drawIconUI; }
	Rva00439E0C *getManager178() const { return m_manager178; }
	TerrainResourceManager *getTerrainResourceManager() const { return m_resourceManager; }
	PlayerLeaveStatus *getPlayerLeaveStatus(int playerIndex); // 0x0023D1E3, verified eight-slot status accessor
};
void XferObjectID(Xfer *xfer, ObjectID *id);
void XferBuildableStatus(Xfer *xfer, int *value);
void XferGameDifficulty(Xfer *xfer, int *value);

struct ObjectTOCEntry;
class CommandButton;
class Team;
class ThingTemplate
{
public:
	void GetAssetList(int assets, int mode);
};

struct Rva001408C0Target;
typedef _STL::set<Rva001408C0Target *, _STL::less<Rva001408C0Target *>,
	_STL::allocator<Rva001408C0Target *> > Rva001408C0Set;

class AssetList
{
public:
	AssetList() : m_treeLayoutPad(0), m_changed(true) {}

private:
	Rva001408C0Set m_prototypes;
	unsigned int m_treeLayoutPad;
	bool m_changed;
};

struct AssetLoadMode
{
	bool m_alternate;
	AssetLoadMode() : m_alternate(false) {}
};

void bfmeMergeReceiverKeys(int value);

struct CreateMask
{
	CreateMask() { memset(m_bits, 0, sizeof(m_bits)); }
	unsigned int m_bits[4];
};

class ThingFactory
{
public:
	Object *rva002D0A23(const ThingTemplate *tt, Team *team, const CreateMask &mask, ObjectID id);
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

class Player { public: char m_pad00[0x2ec]; Team *m_defaultTeam; };
class PlayerList { public: char m_pad00[0x18]; Player *m_neutralPlayer; };
extern PlayerList *ThePlayerList;

class ControlBar { public: const CommandButton *findCommandButton(const AsciiString &name); };
extern ControlBar *TheControlBar;

class GameInfo
{
public:
	GameInfo();
	virtual ~GameInfo();
	virtual void slot04();
	virtual void slot08();
	virtual void xfer(Xfer *xfer);
	virtual void slot10(); virtual void slot14(); virtual void slot18();
	virtual void slot1C(); virtual void slot20(); virtual void slot24();
	virtual void reset();
	void init();
	void endGame();
	void clearSlotList();
	char m_pad04[0x10 - 4];
	bool m_inGame;
	char m_rest[0xDC - 0x11];
};
class SkirmishGameInfo : public GameInfo
{
public:
	SkirmishGameInfo();
	virtual ~SkirmishGameInfo();
	char m_rest2[0xE3C - 0xDC];
};
extern GameInfo *TheSkirmishGameInfo;
extern GameInfo *TheGameInfo;

class SkirmishPreferences
{
public:
	SkirmishPreferences(int tag);
	virtual ~SkirmishPreferences();
	virtual bool write();
	UnicodeString Rva0043B9F5();
	void setCurrentUserName(const UnicodeString &name);

private:
	char m_pad04[0x20 - 4];
};

class LinearCampaignManager;
class CaveSystem;
class LargeGroupAudio;
class DelayedExperienceLevelGrantSystem;
extern LinearCampaignManager *TheLinearCampaignManager;
extern CaveSystem *TheCaveSystem;
extern LargeGroupAudio *TheLargeGroupAudio;
extern DelayedExperienceLevelGrantSystem *TheDelayedExperienceLevelGrantSystem;

// Pointer conversion to a Snapshot sub-object at +off, null-guarded as a base conversion is.
static __forceinline Snapshot *snapshotAt(void *p, int off) { return p ? (Snapshot *)((char *)p + off) : 0; }

class GameLogic;
extern GameLogic *TheGameLogic;
class Rva000421FD
{
public:
	void rva000421FD(void);
};
struct LogicFPView { char opaque[0x1B4]; int depth; };
class Rva0004224C
{
public:
	Rva0004224C(void)
	{
		if (TheGameLogic)
			((Rva000421FD *)TheGameLogic)->rva000421FD();
	}
	~Rva0004224C(void) { if (TheGameLogic) --((LogicFPView *)TheGameLogic)->depth; }
};

struct Rva0023E887Source { int m_00; const char *m_text; };
class Rva0023E887
{
public:
	Rva0023E887(const Rva0023E887Source &source);
private:
	int m_00;
	AsciiString m_text;
};

struct TreeKey00242F5E { int m_id; AsciiString m_name; };
struct TreeOpaqueMapped242F5E { unsigned int m_bits; };
bool operator<(const TreeKey00242F5E &a, const TreeKey00242F5E &b);
typedef _STL::map<TreeKey00242F5E, TreeOpaqueMapped242F5E, _STL::less<TreeKey00242F5E>, _STL::allocator<_STL::pair<const TreeKey00242F5E, TreeOpaqueMapped242F5E> > > ControlBarOverrideMap;

enum BuildableStatus { BUILDABLE_STATUS_UNKNOWN = 0 };
namespace rts
{
	template <class T> struct hash { size_t operator()(const T &value) const; };
	template <class T> struct equal_to { bool operator()(const T &left, const T &right) const; };
}
typedef _STL::pair<const AsciiString, BuildableStatus> BuildableStatusPair;
// The buildable map's hasher is the AsciiString hash at retail 0x00055041 (30 B): the
// key by reference, hashed through _STL::hash<const char *> on str(). Its body is visible
// so the out-of-line ++ chain (0x411084 -> 0x3F7925 -> 0x223149 -> 0x55041) is nothrow.
// Same functor and pinned name as Rva00212858Resize.cpp; the ledger's rts::hash<AsciiString>
// at 0x0002BF8C is a different (lowercasing) body.
struct Rva00055041AsciiHash
{
	unsigned int operator()(const AsciiString &ast) const
	{
		_STL::hash<const char *> tmp;
		return tmp((const char *) ast.str());
	}
};
typedef _STL::hash_map<AsciiString, BuildableStatus, Rva00055041AsciiHash,
	rts::equal_to<AsciiString>, _STL::allocator<BuildableStatusPair> > BuildableMap;


class Rva0023E7B4 { public: void *rva0023E7B4(unsigned short key); };

struct ObjectView
{
	char m_pad00[4];
	ThingTemplate *m_template;
	char m_pad08[0x38 - 8];
	Coord3DBase m_position;
	char m_pad44[0x74 - 0x44];
	ObjectID m_id;
	char m_pad78[0x8C - 0x78];
	ObjectView *m_next;
};


class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

// StringBase<wchar_t>::compare is called out of line, bound to the string_base.cpp row.
template<> __declspec(nothrow) int StringBase<wchar_t>::compare(const StringBase<wchar_t>&str)const;

static __forceinline bool differs(const UnicodeString &a, const UnicodeString &b) { return a.compare(b) != 0; }

// The Snapshot sub-object of GameLogic (receiver of DoXfer); offsets are receiver-relative.
class GameLogicSnapshot
{
public:
	void DoXfer(Xfer *xfer);

private:
	char m_pad00[4];
	BuildableMap m_buildableOverrides;                   // +0x04 (GameLogic +0x10)
	ControlBarOverrideMap m_controlBarOverrides;         // +0x18
	char m_pad2C[0x2c - 0x18 - sizeof(ControlBarOverrideMap)];
	unsigned int m_timestamp;                            // +0x2C
	char m_pad30[0x34 - 0x30];
	unsigned int m_frame;                                // +0x34
	char m_pad38[0x88 - 0x38];
	int m_88;
	bool m_scoring;                                      // +0x8C
	bool m_8d, m_8e, m_8f;
	char m_pad90[0x93 - 0x90];
	bool m_93;
	int m_94;
	int m_98;
	char m_pad9C[0xA0 - 0x9C];
	ObjectView *m_objList;                               // +0xA0
	char m_padA4[0x104 - 0xA4];
	int m_mode;                                          // +0x104
	int m_second;                                        // +0x108
	int m_10c;
	bool m_110;
	char m_pad111[0x158 - 0x111];
	_STL::vector<Rva00243B52DestroyEntry *> m_158;
	Snapshot *m_164;
	Snapshot *m_168;
	Snapshot *m_16c;
	int m_170;
	unsigned int m_174;
};

void GameLogicSnapshot::DoXfer(Xfer *xfer)
{
	XferVersionInfo version(1, 8);
	xfer->xferVersion(&version);

	int mode = m_mode;
	xfer->xferInt(&mode);
	m_mode = mode;
	int second = m_second;
	xfer->xferInt(&second);
	int curMode = m_mode;
	m_second = second;

	if (curMode == 2 || second == 0) {
		if (xfer->isLoading()) {
			if (!TheSkirmishGameInfo) {
				TheSkirmishGameInfo = new SkirmishGameInfo;
			} else if (TheSkirmishGameInfo->m_inGame) {
				TheSkirmishGameInfo->endGame();
			}
			TheGameInfo = TheSkirmishGameInfo;
			TheSkirmishGameInfo->init();
			TheSkirmishGameInfo->clearSlotList();
			TheSkirmishGameInfo->reset();
		}
		TheSkirmishGameInfo->xfer(xfer);
	}

	if (version.m_b >= 4 && m_mode == 2) {
		SkirmishPreferences prefs(0);
		UnicodeString name = prefs.Rva0043B9F5();
		xfer->xferUnicodeString(&name);
		bool changed = xfer->isLoading() && differs(prefs.Rva0043B9F5(), name);
		if (changed) {
			prefs.setCurrentUserName(name);
			prefs.write();
		}
	}

	if (xfer->isCRC())
		xfer->xferUnsignedInt(&m_timestamp);
	xfer->xferUnsignedInt(&m_frame);
	xfer->xferInt(&m_170);
	xfer->xferBool(&m_110);

	if (xfer->isLightCRC()) {
		for (ObjectView *obj = m_objList; obj; obj = obj->m_next) {
			Coord3DBase pos;
			pos.x = obj->m_position.x;
			pos.y = obj->m_position.y;
			pos.z = obj->m_position.z;
			xfer->xferCoord3D(&pos);
		}
		return;
	}

	Rva0004224C guard;
	GameLogic *logic = (GameLogic *)((char *)this - 0x0C);
	logic->xferObjectTOC(xfer);
	if (xfer->isLoading())
		logic->prepareLogicForObjectLoad();
	unsigned int objectCount = logic->getObjectCount();
	xfer->xferUnsignedInt(&objectCount);

	ObjectID id;
	Team *defaultTeam;
	if (xfer->isStoring()) {
		for (ObjectView *obj = m_objList; obj; obj = obj->m_next) {
			ObjectTOCEntry *entry = logic->findTOCEntryByName(*(AsciiString *)((char *)obj->m_template + 0x64));
			if (entry == 0)
				throw XferException(5, 0);
			xfer->xferUnsignedShort((unsigned short *)((char *)entry + 4));
			id = obj->m_id;
			XferObjectID(xfer, &id);
			xfer->beginBlock("Object");
			xfer->xferSnapshot((Snapshot *)((char *)obj + 0x60));
			xfer->endBlock();
		}
	} else {
		defaultTeam = ThePlayerList->m_neutralPlayer->m_defaultTeam;
		for (unsigned int i = 0; i < objectCount; ++i) {
			unsigned short tocID;
			xfer->xferUnsignedShort(&tocID);
			AsciiString *entryName = (AsciiString *)((Rva0023E7B4 *)logic)->rva0023E7B4(tocID);
			if (entryName == 0)
				throw XferException(5, 0);
			XferObjectID(xfer, &id);
			const ThingTemplate *tt = TheThingFactory->findTemplate(*entryName);
			if (tt == 0) {
				xfer->skipBlock("Object");
				continue;
			}
			AssetLoadMode mode;
			AssetList assets;
			((ThingTemplate *)tt)->GetAssetList((int)&assets, (int)&mode);
			bfmeMergeReceiverKeys((int)&assets);
			Object *obj = TheThingFactory->rva002D0A23(tt, defaultTeam, CreateMask(), id);
			xfer->beginBlock("Object");
			xfer->xferSnapshot(snapshotAt(obj, 0x60));
			xfer->endBlock();
		}
	}

	if (version.m_b < 7)
		xfer->xferSnapshot((Snapshot *)TheLinearCampaignManager);
	xfer->xferSnapshot(snapshotAt(TheCaveSystem, 0x0C));
	xfer->xferSnapshot(m_164);
	xfer->xferSnapshot(m_168);
	xfer->xferSnapshot(m_16c);
	xfer->xferSnapshot(snapshotAt(TheLargeGroupAudio, 0x0C));
	xfer->xferBool(&m_scoring);
	xfer->xferInt(&m_10c);

	if (xfer->isStoring()) {
		for (BuildableMap::const_iterator it = m_buildableOverrides.begin(); it != m_buildableOverrides.end(); ++it) {
			AsciiString name = it->first;
			int status = it->second;
			xfer->xferAsciiString(&name);
			XferBuildableStatus(xfer, &status);
		}
		AsciiString empty;
		xfer->xferAsciiString(&empty);
	} else {
		if (!m_buildableOverrides.empty())
			throw XferException(5, 0);
		for (;;) {
			AsciiString name;
			xfer->xferAsciiString(&name);
			if (name.isEmpty())
				break;
			int status;
			XferBuildableStatus(xfer, &status);
			m_buildableOverrides[name] = (BuildableStatus)status;
		}
	}

	xfer->xferBool(&m_8d);
	xfer->xferBool(&m_8e);
	xfer->xferBool(&m_8f);
	xfer->xferInt(&m_94);
	if (version.m_b >= 3)
		XferGameDifficulty(xfer, &m_98);
	xfer->xferUnsignedInt(&m_174);

	if (xfer->isStoring()) {
		for (ControlBarOverrideMap::iterator it = m_controlBarOverrides.begin(); it != m_controlBarOverrides.end(); ++it) {
			AsciiString value = it->second.m_bits ? *(AsciiString *)(it->second.m_bits + 0x10) : AsciiString::TheEmptyString;
			int slot = it->first.m_id;
			AsciiString key = it->first.m_name;
			xfer->xferInt(&slot).xferAsciiString(&key).xferAsciiString(&value);
		}
		int end = -1;
		xfer->xferInt(&end);
	} else {
		if (!m_controlBarOverrides.empty())
			throw XferException(5, 0);
		for (;;) {
			if (version.m_b >= 5) {
				int slot;
				xfer->xferInt(&slot);
				if (slot < 0)
					break;
				AsciiString key;
				AsciiString value;
				xfer->xferAsciiString(&key).xferAsciiString(&value);
				const CommandButton *button = 0;
				if (!value.isEmpty())
					button = TheControlBar->findCommandButton(value);
				m_controlBarOverrides[(const TreeKey00242F5E &)_STL::make_pair(slot, key)].m_bits = (unsigned int)button;
			} else {
				AsciiString name;
				xfer->xferAsciiString(&name);
				if (name.isEmpty())
					break;
				AsciiString value;
				xfer->xferAsciiString(&value);
				const CommandButton *button = 0;
				if (!value.isEmpty())
					button = TheControlBar->findCommandButton(value);
				const char *rest = name.str() + 1;
				Rva0023E887Source source;
				source.m_00 = name.str()[0] - '0';
				source.m_text = rest;
				Rva0023E887 key(source);
				m_controlBarOverrides[(const TreeKey00242F5E &)key].m_bits = (unsigned int)button;
			}
		}
	}

	xfer->xferInt(&m_88);
	if (version.m_b >= 2)
		xfer->xferBool(&m_93);
	if (version.m_b >= 8)
		xfer->xferSnapshot(snapshotAt(TheDelayedExperienceLevelGrantSystem, 0x0C));
	m_158.clear();
}

// The shared GameLogic view leaves +0x24 unmodelled; the override map lives there.
struct GameLogicControlBarOverrides
{
	unsigned char m_pad00[0x24];
	ControlBarOverrideMap m_controlBarOverrides;	// +0x24
};

void GameLogic::setControlBarOverride(const AsciiString &commandSetName, int slot, const CommandButton *commandButton)
{
	((GameLogicControlBarOverrides *)this)->m_controlBarOverrides[(const TreeKey00242F5E &)_STL::make_pair(slot, commandSetName)].m_bits = (unsigned int)commandButton;
}
