// ?DoXfer@ScriptEngine@@UAEXPAVXfer@@@Z
// partial score=0.86 date=2026-10-17
// ?DoXfer@ScriptEngine@@UAEXPAVXfer@@@Z
// partial score=0.75 date=2026-10-14
// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata /O1 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_STLP_NO_EXCEPTIONS /arch:SSE /G7 /DBFME_SNAPSHOT_CAPITALIZED_SLOTS
// stlport
//
// ScriptEngine::DoXfer, retail 0x0020A859 (6131 B): the script engine's save
// game block, version 5. Retail evidence: the Snapshot thunk of the
// ScriptEngine vtable, WorldBuilder's ScriptEngine.cpp lines 4309..4923 (its
// four DEBUG_CRASH texts name m_sequentialScripts, MAX_ATTACK_PRIORITIES,
// m_namedObjects, m_namedReveals and m_allObjectTypeLists) and the rowed
// helpers it calls. Zero Hour's ScriptEngine::xfer supplies the section order
// and the member names; BFME 2 turned the counters and flags into keyed maps
// and added the living-world maps, the per-player special power lists and the
// version 2/3 maps after the object type lists.
//
// Bank state (explain_mismatch, 2026-10-14): 15 structural and 504 raw
// instruction diffs out of 2027. Remaining walls:
// - loop entry: retail enters the old-version CRC loops 1, 3 and 4 by
//   jmp-to-test, while loops 2, 5 and the per-player loops use the guard
//   (cmp edi,eax / je). Loops 1 and 2 have the same source. This build guards
//   all of them. Tried without effect: const_iterator, postfix ++, reversed
//   compare, while form, iterator declared outside or at the block top,
//   (*it), and dropping the local _List_iterator operator!=.
// - frame slots: retail order is counters, flags, sequentialScriptCount; req
//   sits at -0x64, shared with the byte-flag name; version is at -0x34; the
//   byte-flag value is in the dead xfer argument slot [ebp+0xb]. Renaming
//   locals or moving their declarations does not change this layout.
// - unresolved ICF STL callees: list dtor 0x2FECBC, list clear 0x23DAA5,
//   the eh-vector element dtor 0x207F08 and the _List_base ctor 0x35C9A6
//   need names or fold-proof pins.
#include "ascii_string.h"
#include <map>
#include <list>
#include <vector>
#include "Common/Snapshot.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/GameEngine/Source/Common/BfmeSpecialPowerTimer8.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"

class GameLogic;
extern GameLogic *TheGameLogic;

namespace _STL {
template<class T,class L,class R>
static inline bool operator!=(const _Rb_tree_iterator<T,L>& a,const _Rb_tree_iterator<T,R>& b) {
 return a._M_node!=b._M_node;
}
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a, const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef short Short;
typedef float Real;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool IsLoading();
	virtual Bool IsStoring();
	virtual Bool IsCRC();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void xferUser(void *data, UnsignedInt size);
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *snapshot);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(AsciiString *value);
	virtual void xferReal(Real *value);
	virtual void slot29();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
	virtual void xferUnsignedShort(UnsignedShort *value);
	virtual void xferShort(Short *value);
	virtual void xferUnsignedByte(UnsignedByte *value);
	virtual void slot35();
	virtual void xferBool(Bool *value);
};

// Native constructor 0x0060C36E and throw type CFFD18 identify the real class.
class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &);
	~XferException();
	char *text;
	int tag;
};

struct ScriptCounter
{
	int m_value;
	bool m_isCountdownTimer;
	bool m_isMillisecondTimer;
	ScriptCounter() : m_value(0), m_isCountdownTimer(false), m_isMillisecondTimer(false) {}
};

typedef _STL::pair<AsciiString,AsciiString> ScriptKey;
struct TeamLess0019B850 : _STL::less<ScriptKey> {};
typedef _STL::map<ScriptKey,ScriptCounter> ScriptCounterMap;
typedef _STL::map<ScriptKey,bool> ScriptFlagMap;
typedef _STL::map<ScriptKey,int,TeamLess0019B850> ScriptDefaultIntMap;
typedef _STL::map<ScriptKey,AsciiString> ScriptStringMap;
typedef _STL::map<AsciiString,unsigned char> ScriptByteMap;

struct NoCaseTreeValue4
{
	unsigned int m_value;
	NoCaseTreeValue4() : m_value(0) {}
};
typedef _STL::list<_STL::pair<const AsciiString,NoCaseTreeValue4> > ListAsciiStringValue;
typedef _STL::list<BfmeSpecialPowerTimer8> ListSpecialPowerTimer;
typedef _STL::list<AsciiString> ListAsciiString;
typedef _STL::list<int> ListInt;
typedef _STL::list<_STL::pair<AsciiString,Coord3D> > ListAsciiStringCoord3D;

struct BfmeFloat4Record00469C61
{
	unsigned int m_frame;
	Coord3D m_position;
};
typedef _STL::list<BfmeFloat4Record00469C61> ListToppleRecord;

struct BfmeStringRecord00204A30
{
	unsigned long word0;
	AsciiString text0;
	float word1;
	AsciiString text1;
	int word2;
	~BfmeStringRecord00204A30();
};

class Object
{
	char m_pad[0x74];
public:
	ObjectID m_id;
	ObjectID getID() const { return m_id; }
};

struct Rva0020A227Element
{
	AsciiString key;
	Object *obj;
	Rva0020A227Element() : obj(0) {}
};

// Retail 0x0020479E (Rva0020479ECtor.cpp): stores only, so loading needs no
// unwind state around the allocation.
struct SequentialScriptQuad
{
	int m_count0;
	int m_index0;
	int m_count1;
	int m_index1;
	SequentialScriptQuad() : m_count0(0), m_index0(-1), m_count1(0), m_index1(-1) {}
};

class SequentialScript : public Snapshot
{
public:
	SequentialScript() : m_04(0), m_08(0), m_0c(0), m_10(0), m_24(0), m_28(0) {}
protected:
	virtual void LoadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void DoXfer(Xfer *xfer);
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	SequentialScriptQuad m_14;
	unsigned char m_24;
	int m_28;
};

class ObjectTypes : public Snapshot
{
public:
	ObjectTypes();
protected:
	virtual void LoadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void DoXfer(Xfer *xfer);
	char m_data[0x10];
};

class AttackPriorityInfo : public Snapshot
{
protected:
	virtual void LoadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void DoXfer(Xfer *xfer);
	char m_data[0xC];
};

class Rva00203D4EA;
void Rva00203D4EChain(Rva00203D4EA *xfer, void *key);
void XferLivingWorldArmyID(Xfer *xfer, int *id);
void XferLivingWorldPlayerID(Xfer *xfer, int *id);
void XferObjectID(Xfer *xfer, ObjectID *id);
void XferGameDifficulty(Xfer *xfer, int *difficulty);
unsigned long CRC_String(const char *text);
unsigned long Rva003ECA13Get(const AsciiString &text);
Xfer *xferListInt(Xfer *xfer, ListInt *list);
Xfer *Rva00206923XferList(Xfer *xfer, ListSpecialPowerTimer *list);
Xfer *xferList2069F0(Xfer *xfer, ListToppleRecord *list);
Xfer *Rva0020700FXfer(Xfer *xfer, ListAsciiString *list);
Xfer *Rva002070F7Xfer(Xfer *xfer, ListSpecialPowerTimer *lists);
Xfer *Rva00207F91XferList(Xfer *xfer, ListAsciiStringValue *list);
Xfer *Rva00208081Xfer(Xfer *xfer, void *lists);
Xfer *Rva002080DAXferList(Xfer *xfer, ListAsciiStringCoord3D *list);
Xfer *Rva00209A09Xfer(Xfer *xfer, ListAsciiStringValue *lists);

class Rva00206593 { public: void rva00206EC7(); };
class Rva002065C8 { public: void rva00206EF0(); };
class Rva002065FD { public: void rva00206F19(); };
class Rva00206632 { public: void rva00206F42(); };
class Rva00206667 { public: void rva00206F6B(); };
class Rva0020669C { public: void rva00206F94(); };
class Rva002066D1 { public: void rva00206FBD(); };
class Rva00206706 { public: void rva00206FE6(); };

enum { MAX_ATTACK_PRIORITIES = 256, MAX_PLAYER_COUNT = 20 };

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
protected:
	bool m_dumpUpdate;
	int m_curUpdateTime;
};

class ScriptEngine : public SubsystemInterface, public Snapshot
{
public:
	typedef _STL::vector<SequentialScript *> VecSequentialScriptPtr;
	typedef _STL::vector<Rva0020A227Element> VecNamedRequests;
	typedef _STL::vector<BfmeStringRecord00204A30> VecNamedReveal;
	typedef _STL::vector<ObjectTypes *> AllObjectTypes;
	virtual void LoadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void DoXfer(Xfer *xfer);
protected:

	VecSequentialScriptPtr m_sequentialScripts;          // 0x10
	char m_pad1C[0x190A0 - 0x1C];
	ScriptCounterMap m_counters;                          // 0x190A0
	ScriptFlagMap m_flags;                                // 0x190AC
	ScriptDefaultIntMap m_objectIDs;                      // 0x190B8
	ScriptDefaultIntMap m_values;                         // 0x190C4
	ScriptByteMap m_byteFlags;                            // 0x190D0
	ScriptDefaultIntMap m_players;                        // 0x190DC
	ScriptDefaultIntMap m_armies;                         // 0x190E8
	ScriptStringMap m_strings;                            // 0x190F4
	AttackPriorityInfo m_attackPriorityInfo[MAX_ATTACK_PRIORITIES]; // 0x19100
	Int m_numAttackInfo;                                  // 0x1A100
	Int m_endGameTimer;                                   // 0x1A104
	Int m_closeWindowTimer;                               // 0x1A108
	AsciiString m_currentTrackName;                       // 0x1A10C
	char m_pad1A110[0x1A120 - 0x1A110];
	VecNamedRequests m_namedObjects;                      // 0x1A120
	Bool m_firstUpdate;                                   // 0x1A12C
	char m_pad1A12D[0x1A138 - 0x1A12D];
	Int m_fade;                                           // 0x1A138
	char m_pad1A13C[4];
	Real m_minFade;                                       // 0x1A140
	Real m_maxFade;                                       // 0x1A144
	Real m_curFadeValue;                                  // 0x1A148
	Int m_curFadeFrame;                                   // 0x1A14C
	Int m_fadeFramesIncrease;                             // 0x1A150
	Int m_fadeFramesHold;                                 // 0x1A154
	Int m_fadeFramesDecrease;                             // 0x1A158
	UnsignedInt m_unknown1A15C;                           // 0x1A15C
	UnsignedInt m_unknown1A160;                           // 0x1A160
	char m_pad1A164[0x1A254 - 0x1A164];
	ListInt m_completedVideo;                             // 0x1A254
	ListSpecialPowerTimer m_testingSpeech;                // 0x1A258
	ListSpecialPowerTimer m_testingAudio;                 // 0x1A25C
	ListInt m_uiInteractions;                             // 0x1A260
	ListInt m_list1A264;                                  // 0x1A264
	ListSpecialPowerTimer m_triggeredSpecialPowers[MAX_PLAYER_COUNT]; // 0x1A268
	ListSpecialPowerTimer m_midwaySpecialPowers[MAX_PLAYER_COUNT];    // 0x1A2B8
	ListSpecialPowerTimer m_finishedSpecialPowers[MAX_PLAYER_COUNT];  // 0x1A308
	ListSpecialPowerTimer m_completedUpgrades[MAX_PLAYER_COUNT];      // 0x1A358
	char m_acquiredSciences[0xF0];                        // 0x1A3A8
	ListToppleRecord m_toppleDirections;                  // 0x1A498
	VecNamedReveal m_namedReveals;                        // 0x1A49C
	Real m_breezeDirection;                               // 0x1A4A8
	Real m_breezeDirectionX;                              // 0x1A4AC
	Real m_breezeDirectionY;                              // 0x1A4B0
	Real m_breezeIntensity;                               // 0x1A4B4
	Real m_breezeLean;                                    // 0x1A4B8
	Real m_breezeRandomness;                              // 0x1A4BC
	Short m_breezePeriod;                                 // 0x1A4C0
	Short m_breezeVersion;                                // 0x1A4C2
	Int m_gameDifficulty;                                 // 0x1A4C4
	AllObjectTypes m_allObjectTypeLists;                  // 0x1A4C8
	Bool m_bool1A4D4;                                     // 0x1A4D4
	Bool m_objectsShouldReceiveDifficultyBonus;           // 0x1A4D5
	Bool m_ChooseVictimAlwaysUsesNormal;                  // 0x1A4D6
	Bool m_freezeByScript;                                // 0x1A4D7
};

void ScriptEngine::DoXfer(Xfer *xfer)
{
	Int i;

	if (xfer->IsCRC())
		return;

	struct { XferVersion v; unsigned char pad[14]; } versionBuf;
	XferVersion& version = versionBuf.v;
	version.m_version = 1;
	version.m_currentVersion = 5;
	xfer->xferVersion(&version);
	xfer->xferBool(&m_freezeByScript);
	xfer->xferAsciiString(&m_currentTrackName);

	// sequential scripts
	UnsignedShort sequentialScriptCount = m_sequentialScripts.size();
	xfer->xferUnsignedShort(&sequentialScriptCount);
	SequentialScript *sequentialScript;
	if (xfer->IsStoring())
	{
		VecSequentialScriptPtr::iterator it;
		for (it = m_sequentialScripts.begin(); it != m_sequentialScripts.end(); ++it)
		{
			sequentialScript = *it;
			xfer->xferSnapshot(sequentialScript);
		}
	}
	else
	{
		if (m_sequentialScripts.size() != 0)
			throw XferException(5, 0);
		for (UnsignedShort i = 0; i < sequentialScriptCount; ++i)
		{
			sequentialScript = new SequentialScript;
			m_sequentialScripts.push_back(sequentialScript);
			xfer->xferSnapshot(sequentialScript);
		}
	}

	// counters
	UnsignedShort countersSize = m_counters.size();
	xfer->xferUnsignedShort(&countersSize);
	if (xfer->IsStoring())
	{
		ScriptCounterMap::iterator end = m_counters.end();
		for (ScriptCounterMap::iterator it = m_counters.begin(); it != end; ++it)
		{
			xfer->xferAsciiString(&const_cast<ScriptKey &>(it->first).first);
			xfer->xferAsciiString(&const_cast<ScriptKey &>(it->first).second);
			xfer->xferInt(&it->second.m_value);
			xfer->xferBool(&it->second.m_isCountdownTimer);
		}
	}
	else
	{
		((Rva00206593 *)&m_counters)->rva00206EC7();
		i = 0;
		while (i < countersSize)
		{
			ScriptKey key;
			xfer->xferAsciiString(&key.first);
			xfer->xferAsciiString(&key.second);
			ScriptCounter counter;
			xfer->xferInt(&counter.m_value);
			xfer->xferBool(&counter.m_isCountdownTimer);
			m_counters.insert(_STL::make_pair(key, counter));
		}
	}

	// flags
	UnsignedShort flagsSize = m_flags.size();
	xfer->xferUnsignedShort(&flagsSize);
	if (xfer->IsStoring())
	{
		ScriptFlagMap::iterator end = m_flags.end();
		for (ScriptFlagMap::iterator it = m_flags.begin(); it != end; ++it)
		{
			xfer->xferAsciiString(&const_cast<ScriptKey &>(it->first).first);
			xfer->xferAsciiString(&const_cast<ScriptKey &>(it->first).second);
			xfer->xferBool(&it->second);
		}
	}
	else
	{
		((Rva002065C8 *)&m_flags)->rva00206EF0();
		for (i = 0; i < flagsSize; ++i)
		{
			ScriptKey key;
			xfer->xferAsciiString(&key.first);
			xfer->xferAsciiString(&key.second);
			bool value = false;
			xfer->xferBool(&value);
			m_flags.insert(_STL::make_pair(key, value));
		}
	}

	// living world players, armies and strings
	if (version.m_currentVersion >= 4)
	{
		Int count;
		if (xfer->IsLoading())
		{
			xfer->xferInt(&count);
			while (count > 0)
			{
				ScriptKey key;
				Rva00203D4EChain((Rva00203D4EA *)xfer, &key);
				UnsignedInt army;
				XferLivingWorldArmyID(xfer, (int *)&army);
				m_armies.insert(ScriptDefaultIntMap::value_type(key, army));
				--count;
			}
			xfer->xferInt(&count);
			while (count > 0)
			{
				ScriptKey key;
				Rva00203D4EChain((Rva00203D4EA *)xfer, &key);
				AsciiString value;
				xfer->xferAsciiString(&value);
				m_strings.insert(ScriptStringMap::value_type(key, AsciiString(value)));
				--count;
			}
			xfer->xferInt(&count);
			while (count > 0)
			{
				ScriptKey key;
				Rva00203D4EChain((Rva00203D4EA *)xfer, &key);
				UnsignedInt player;
				XferLivingWorldPlayerID(xfer, (int *)&player);
				m_players.insert(ScriptDefaultIntMap::value_type(key, player));
				--count;
			}
		}
		else
		{
			count = m_armies.size();
			xfer->xferInt(&count);
			ScriptDefaultIntMap::iterator it = m_armies.begin();
			ScriptDefaultIntMap::iterator end = m_armies.end();
			while (it != end)
			{
				ScriptKey key(it->first);
				Rva00203D4EChain((Rva00203D4EA *)xfer, &key);
				Int army = it->second;
				XferLivingWorldArmyID(xfer, &army);
				++it;
			}
			count = m_strings.size();
			xfer->xferInt(&count);
			ScriptStringMap::iterator sit = m_strings.begin();
			ScriptStringMap::iterator send = m_strings.end();
			while (sit != send)
			{
				ScriptKey key(sit->first);
				Rva00203D4EChain((Rva00203D4EA *)xfer, &key);
				AsciiString value(sit->second);
				xfer->xferAsciiString(&value);
				++sit;
			}
			count = m_players.size();
			xfer->xferInt(&count);
			ScriptDefaultIntMap::iterator pit = m_players.begin();
			ScriptDefaultIntMap::iterator pend = m_players.end();
			while ((1 ? (pit != pend) : (pit != pend)))
			{
				ScriptKey key(pit->first);
				Rva00203D4EChain((Rva00203D4EA *)xfer, &key);
				Int player = pit->second;
				XferLivingWorldPlayerID(xfer, &player);
				++it;
			}
		}
	}
	else if (xfer->IsLoading())
	{
		((Rva002066D1 *)&m_armies)->rva00206FBD();
		((Rva0020669C *)&m_players)->rva00206F94();
		((Rva00206706 *)&m_strings)->rva00206FE6();
	}

	// attack priority info
	UnsignedShort attackPriorityInfoSize = m_numAttackInfo;
	xfer->xferUnsignedShort(&attackPriorityInfoSize);
	if (attackPriorityInfoSize > MAX_ATTACK_PRIORITIES)
		throw XferException(5, 0);
	for (i = 0; i < attackPriorityInfoSize; ++i)
		xfer->xferSnapshot(&m_attackPriorityInfo[i]);
	xfer->xferInt(&m_numAttackInfo);
	xfer->xferInt(&m_endGameTimer);
	xfer->xferInt(&m_closeWindowTimer);

	// named objects
	AsciiString namedObjectName;
	Object *obj;
	ObjectID objectID;
	UnsignedShort namedObjectsCount = m_namedObjects.size();
	xfer->xferUnsignedShort(&namedObjectsCount);
	if (xfer->IsStoring())
	{
		VecNamedRequests::iterator it;
		for (it = m_namedObjects.begin(); it != m_namedObjects.end(); ++it)
		{
			namedObjectName = it->key;
			xfer->xferAsciiString(&namedObjectName);
			obj = it->obj;
			objectID = obj ? obj->getID() : INVALID_OBJECT_ID;
			XferObjectID(xfer, &objectID);
		}
	}
	else
	{
		Rva0020A227Element req;
		m_namedObjects.clear();
		for (UnsignedShort i = 0; i < namedObjectsCount; ++i)
		{
			xfer->xferAsciiString(&namedObjectName);
			XferObjectID(xfer, &objectID);
			obj = TheGameLogic->findObjectByID(objectID);
			if (obj == 0 && objectID != INVALID_OBJECT_ID)
				throw XferException(5, 0);
			req.key = namedObjectName;
			req.obj = obj;
			m_namedObjects.push_back(req);
		}
	}

	// fade
	xfer->xferBool(&m_firstUpdate);
	xfer->xferUser(&m_fade, sizeof(m_fade));
	xfer->xferReal(&m_minFade);
	xfer->xferReal(&m_maxFade);
	xfer->xferReal(&m_curFadeValue);
	xfer->xferInt(&m_curFadeFrame);
	xfer->xferInt(&m_fadeFramesIncrease);
	xfer->xferInt(&m_fadeFramesHold);
	xfer->xferInt(&m_fadeFramesDecrease);

	// lists saved by name before version 5, by CRC since
	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiString names;
		Rva0020700FXfer(xfer, &names);
		m_completedVideo.clear();
		for (ListAsciiString::iterator it = names.begin(); it != names.end(); ++it)
			m_completedVideo.push_back(CRC_String(it->str()));
	}
	else
		xferListInt(xfer, &m_completedVideo);

	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiString names;
		Rva0020700FXfer(xfer, &names);
		m_uiInteractions.clear();
		for (ListAsciiString::iterator it = names.begin(); it != names.end(); ++it)
			m_uiInteractions.push_back(CRC_String(it->str()));
	}
	else
		xferListInt(xfer, &m_uiInteractions);

	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiStringValue names;
		Rva00207F91XferList(xfer, &names);
		m_testingSpeech.clear();
		BfmeSpecialPowerTimer8 timer;
		timer.m_templateID = 0;
		timer.m_readyFrame = 0;
		for (ListAsciiStringValue::iterator it = names.begin(); it != names.end(); ++it)
		{
			timer.m_templateID = CRC_String(it->first.str());
			timer.m_readyFrame = it->second.m_value;
			m_testingSpeech.push_back(timer);
		}
	}
	else
		Rva00206923XferList(xfer, &m_testingSpeech);

	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiStringValue names;
		Rva00207F91XferList(xfer, &names);
		m_testingAudio.clear();
		BfmeSpecialPowerTimer8 timer;
		timer.m_templateID = 0;
		timer.m_readyFrame = 0;
		for (ListAsciiStringValue::iterator it = names.begin(); it != names.end(); ++it)
		{
			timer.m_templateID = CRC_String(it->first.str());
			timer.m_readyFrame = it->second.m_value;
			m_testingAudio.push_back(timer);
		}
	}
	else
		Rva00206923XferList(xfer, &m_testingAudio);

	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiString names;
		Rva0020700FXfer(xfer, &names);
		m_list1A264.clear();
		for (ListAsciiString::iterator it = names.begin(); it != names.end(); ++it)
			m_list1A264.push_back(CRC_String(it->str()));
	}
	else
		xferListInt(xfer, &m_list1A264);

	// per-player special power lists
	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiStringValue names[MAX_PLAYER_COUNT];
		Rva00209A09Xfer(xfer, names);
		BfmeSpecialPowerTimer8 timer;
		timer.m_templateID = 0;
		timer.m_readyFrame = 0;
		for (i = 0; i < MAX_PLAYER_COUNT; ++i)
		{
			ListSpecialPowerTimer *list = &m_triggeredSpecialPowers[i];
			list->clear();
			ListAsciiStringValue *old = &names[i];
			for (ListAsciiStringValue::iterator it = old->begin(); it != old->end(); ++it)
			{
				timer.m_templateID = CRC_String(it->first.str());
				timer.m_readyFrame = it->second.m_value;
				list->push_back(timer);
			}
		}
	}
	else
		Rva002070F7Xfer(xfer, m_triggeredSpecialPowers);

	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiStringValue names[MAX_PLAYER_COUNT];
		Rva00209A09Xfer(xfer, names);
		BfmeSpecialPowerTimer8 timer;
		timer.m_templateID = 0;
		timer.m_readyFrame = 0;
		for (i = 0; i < MAX_PLAYER_COUNT; ++i)
		{
			ListSpecialPowerTimer *list = &m_midwaySpecialPowers[i];
			list->clear();
			ListAsciiStringValue *old = &names[i];
			for (ListAsciiStringValue::iterator it = old->begin(); it != old->end(); ++it)
			{
				timer.m_templateID = CRC_String(it->first.str());
				timer.m_readyFrame = it->second.m_value;
				list->push_back(timer);
			}
		}
	}
	else
		Rva002070F7Xfer(xfer, m_midwaySpecialPowers);

	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiStringValue names[MAX_PLAYER_COUNT];
		Rva00209A09Xfer(xfer, names);
		BfmeSpecialPowerTimer8 timer;
		timer.m_templateID = 0;
		timer.m_readyFrame = 0;
		for (i = 0; i < MAX_PLAYER_COUNT; ++i)
		{
			ListSpecialPowerTimer *list = &m_finishedSpecialPowers[i];
			list->clear();
			ListAsciiStringValue *old = &names[i];
			for (ListAsciiStringValue::iterator it = old->begin(); it != old->end(); ++it)
			{
				timer.m_templateID = CRC_String(it->first.str());
				timer.m_readyFrame = it->second.m_value;
				list->push_back(timer);
			}
		}
	}
	else
		Rva002070F7Xfer(xfer, m_finishedSpecialPowers);

	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiStringValue names[MAX_PLAYER_COUNT];
		Rva00209A09Xfer(xfer, names);
		BfmeSpecialPowerTimer8 timer;
		timer.m_templateID = 0;
		timer.m_readyFrame = 0;
		for (i = 0; i < MAX_PLAYER_COUNT; ++i)
		{
			ListSpecialPowerTimer *list = &m_completedUpgrades[i];
			list->clear();
			ListAsciiStringValue *old = &names[i];
			for (ListAsciiStringValue::iterator it = old->begin(); it != old->end(); ++it)
			{
				timer.m_templateID = CRC_String(it->first.str());
				timer.m_readyFrame = it->second.m_value;
				list->push_back(timer);
			}
		}
	}
	else
		Rva002070F7Xfer(xfer, m_completedUpgrades);

	Rva00208081Xfer(xfer, m_acquiredSciences);

	// topple directions
	if (xfer->IsLoading() && version.m_currentVersion < 5)
	{
		ListAsciiStringCoord3D names;
		Rva002080DAXferList(xfer, &names);
		m_toppleDirections.clear();
		BfmeFloat4Record00469C61 topple;
		topple.m_frame = 0;
		for (ListAsciiStringCoord3D::iterator it = names.begin(); it != names.end(); ++it)
		{
			topple.m_frame = CRC_String(it->first.str());
			topple.m_position = it->second;
			m_toppleDirections.push_back(topple);
		}
	}
	else
		xferList2069F0(xfer, &m_toppleDirections);

	// breeze
	xfer->xferReal(&m_breezeDirection);
	xfer->xferReal(&m_breezeDirectionX);
	xfer->xferReal(&m_breezeDirectionY);
	xfer->xferReal(&m_breezeIntensity);
	xfer->xferReal(&m_breezeLean);
	xfer->xferReal(&m_breezeRandomness);
	xfer->xferShort(&m_breezePeriod);
	xfer->xferShort(&m_breezeVersion);
	XferGameDifficulty(xfer, &m_gameDifficulty);
	xfer->xferBool(&m_bool1A4D4);

	// named reveals
	UnsignedShort namedRevealCount = m_namedReveals.size();
	xfer->xferUnsignedShort(&namedRevealCount);
	xfer->xferUnsignedInt(&m_unknown1A15C);
	xfer->xferUnsignedInt(&m_unknown1A160);
	if (xfer->IsStoring())
	{
		VecNamedReveal::iterator it;
		for (it = m_namedReveals.begin(); it != m_namedReveals.end(); ++it)
		{
			xfer->xferUnsignedInt((UnsignedInt *)&it->word0);
			xfer->xferAsciiString(&it->text0);
			xfer->xferReal(&it->word1);
			xfer->xferAsciiString(&it->text1);
		}
	}
	else
	{
		if (m_namedReveals.empty() == false)
			throw XferException(5, 0);
		BfmeStringRecord00204A30 reveal;
		for (UnsignedShort i = 0; i < namedRevealCount; ++i)
		{
			if (version.m_currentVersion >= 5)
				xfer->xferUnsignedInt((UnsignedInt *)&reveal.word0);
			else
			{
				AsciiString name;
				xfer->xferAsciiString(&name);
				reveal.word0 = Rva003ECA13Get(name);
			}
			xfer->xferAsciiString(&reveal.text0);
			xfer->xferReal(&reveal.word1);
			xfer->xferAsciiString(&reveal.text1);
			m_namedReveals.push_back(reveal);
		}
	}

	// object type lists
	UnsignedShort allObjectTypesCount = m_allObjectTypeLists.size();
	xfer->xferUnsignedShort(&allObjectTypesCount);
	if (xfer->IsStoring())
	{
		AllObjectTypes::iterator it;
		ObjectTypes *objectTypes;
		for (it = m_allObjectTypeLists.begin(); it != m_allObjectTypeLists.end(); ++it)
		{
			objectTypes = *it;
			xfer->xferSnapshot(objectTypes);
		}
	}
	else
	{
		if (m_allObjectTypeLists.empty() == false)
			throw XferException(5, 0);
		ObjectTypes *objectTypes;
		for (UnsignedShort i = 0; i < allObjectTypesCount; ++i)
		{
			objectTypes = new ObjectTypes;
			xfer->xferSnapshot(objectTypes);
			m_allObjectTypeLists.push_back(objectTypes);
		}
	}

	xfer->xferBool(&m_objectsShouldReceiveDifficultyBonus);
	xfer->xferBool(&m_ChooseVictimAlwaysUsesNormal);

	if (xfer->IsLoading())
	{
		if (m_fade == 0)
		{
			m_fade = 4;
			m_curFadeFrame = 0;
			m_minFade = 1.0f;
			m_maxFade = 0.0f;
			m_fadeFramesIncrease = 0;
			m_fadeFramesHold = 0;
			m_fadeFramesDecrease = 0;
			m_curFadeValue = 0.0f;
		}
	}

	// keyed object IDs and values
	if (version.m_currentVersion >= 2)
	{
		if (xfer->IsLoading())
		{
			((Rva002065FD *)&m_objectIDs)->rva00206F19();
			UnsignedInt count = 0;
			xfer->xferUnsignedInt(&count);
			for (UnsignedInt i = 0; i < count; ++i)
			{
				AsciiString first;
				AsciiString second;
				xfer->xferAsciiString(&first);
				xfer->xferAsciiString(&second);
				ObjectID id;
				XferObjectID(xfer, &id);
				ScriptKey key(first, second);
				_STL::pair<ScriptDefaultIntMap::iterator, bool> result = m_objectIDs.insert(_STL::make_pair(key, 0));
				result.first->second = id;
			}
			((Rva00206632 *)&m_values)->rva00206F42();
			count = 0;
			xfer->xferUnsignedInt(&count);
			for (UnsignedInt j = 0; j < count; ++j)
			{
				AsciiString first;
				AsciiString second;
				xfer->xferAsciiString(&first);
				xfer->xferAsciiString(&second);
				UnsignedInt value;
				xfer->xferUnsignedInt(&value);
				ScriptKey key(first, second);
				_STL::pair<ScriptDefaultIntMap::iterator, bool> result = m_values.insert(_STL::make_pair(key, 0));
				result.first->second = value;
			}
		}
		else if (xfer->IsStoring())
		{
			UnsignedInt count = m_objectIDs.size();
			xfer->xferUnsignedInt(&count);
			for (ScriptDefaultIntMap::iterator it = m_objectIDs.begin(); it != m_objectIDs.end(); ++it)
			{
				ScriptKey key(it->first);
				ObjectID id = (ObjectID)it->second;
				xfer->xferAsciiString(&key.first);
				xfer->xferAsciiString(&key.second);
				XferObjectID(xfer, &id);
			}
			count = m_values.size();
			xfer->xferUnsignedInt(&count);
			for (ScriptDefaultIntMap::iterator vit = m_values.begin(); vit != m_values.end(); ++vit)
			{
				ScriptKey key(vit->first);
				UnsignedInt value = vit->second;
				xfer->xferAsciiString(&key.first);
				xfer->xferAsciiString(&key.second);
				xfer->xferUnsignedInt(&value);
			}
		}
	}

	// keyed byte flags
	if (version.m_currentVersion >= 3)
	{
		if (xfer->IsStoring())
		{
			UnsignedInt count = m_byteFlags.size();
			xfer->xferUnsignedInt(&count);
			for (ScriptByteMap::iterator it = m_byteFlags.begin(); it != m_byteFlags.end(); ++it)
			{
				AsciiString name(it->first);
				unsigned char value = it->second;
				xfer->xferAsciiString(&name);
				xfer->xferBool((Bool *)&value);
			}
		}
		else if (xfer->IsLoading())
		{
			((Rva00206667 *)&m_byteFlags)->rva00206F6B();
			UnsignedInt count = 0;
			xfer->xferUnsignedInt(&count);
			while (count > 0)
			{
				AsciiString name;
				unsigned char value = 0;
				xfer->xferAsciiString(&name);
				xfer->xferBool((Bool *)&value);
				m_byteFlags.insert(_STL::make_pair(name, value));
				--count;
			}
		}
	}
}
