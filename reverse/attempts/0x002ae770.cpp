// ?update@Player@@QAEXXZ
// partial score=0.99 date=2026-10-15
// cl: /G7 /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?update@Player@@QAEXXZ, retail 0x002AE770 (351 bytes, RET0).
// Identity: existing pin (PlayerList's per-player update REL32 at
// 0x002A7AC0); WB C12FA0 is the same body by call graph. ZH Player.cpp
// Player::update supplies the shape: AI update, generic scripts of every
// owned team, local-player retaliation-mode message once a logic second.
// BFME2 deltas established from retail bytes:
//  - before the team walk, the +2BC name->int timer map is walked; each
//    nonzero entry is decremented and, on reaching zero, the +294 float
//    map entry for that name is reset from the +2A8 one (production-speed
//    bonus expiry; the writer is rowed PlayerProductionSpeed 0x002AE8CF);
//  - the team-prototype list (+0x32C) is walked through a local copy
//    (copy ctor 0x002AE577, nothrow base dtor 0x002ABB44);
//  - the energy sabotage and academy-stats updates are gone;
//  - LOGICFRAMES_PER_SECOND is the variable BfmeLogicFramesPerSecond;
//  - the tail calls rowed Player 0x002AD1FD and ScoreKeeper::updateFrame
//    on the +0x3BC score keeper.
// Field names for +2BC/+2A8/+294/+33E are donor inference; the map views
// keep their rowed address-derived owners.
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class AsciiString;
class TeamPrototype;

// Retail calls the team list's base destructor (0x002ABB44) with no EH
// state transition before it (see AIPlayerTeamBuild.cpp).
namespace _STL {
template <> inline _List_base<TeamPrototype *, allocator<TeamPrototype *> >::~_List_base() throw()
{
	clear();
	_M_node.deallocate(_M_node._M_data, 1);
}
}
typedef _STL::list<TeamPrototype *> PlayerTeamList;

template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc) {}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};
class Snapshot
{
public:
	virtual void crc();
};

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
	void updateGenericScripts();
};

class TeamPrototype
{
public:
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const
	{
		return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
	}
private:
	unsigned char m_pad[0x334];
	Team *m_dlinkhead_TeamInstanceList; // +0x334
};

// Rowed name-map helpers (AsciiStringTableSubscripts.cpp, MilesAudio views).
class Rva000411084
{
public:
	void *next();
	void *current, *owner;
};
class Rva000427195
{
public:
	void *first(Rva000411084 *);
};
class Rva001FDE3F
{
public:
	float &rva001FDE3F(const AsciiString &key);
};
struct NameTimerNode
{
	void *m_next;
	unsigned char m_key[4]; // AsciiString
	Int m_value;
};

class AIPlayerView
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void update();
};

class GameMessage
{
public:
	enum Type { MSG_ENABLE_RETALIATION_MODE = 0x462 };
	void appendIntegerArgument(Int arg);
	void appendBooleanArgument(Bool arg);
};
class MessageStream
{
public:
#define V(n) virtual void slot##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17)
#undef V
	virtual GameMessage *appendMessage(GameMessage::Type);
};
extern MessageStream *TheMessageStream;

class ScoreKeeper
{
public:
	void updateFrame(Int frame);
};

class Player;
class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
private:
	unsigned char m_pad[0x10];
	Player *m_local; // +0x10
};
extern PlayerList *ThePlayerList;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	unsigned char m_pad[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct GlobalDataView
{
	unsigned char m_pad[0x11BC];
	Bool m_clientRetaliationModeEnabled; // +0x11BC
};
#define TheGlobalData ((const GlobalDataView *)TheWritableGlobalData)

extern Int BfmeLogicFramesPerSecond;

class Player
{
public:
	void update();
	void rva002AD1FD();
	Int getPlayerIndex() const { return m_playerIndex; }
	Bool isLogicalRetaliationModeEnabled() const { return m_logicalRetaliationModeEnabled; }
private:
	unsigned char m_pad0[0x54];
	Int m_playerIndex; // +0x54
	unsigned char m_pad58[0x294 - 0x58];
	Rva001FDE3F m_productionSpeedBonus; // +0x294
	unsigned char m_pad295[0x2A8 - 0x295];
	Rva001FDE3F m_startingProductionSpeedBonus; // +0x2A8
	unsigned char m_pad2A9[0x2BC - 0x2A9];
	Rva000427195 m_productionSpeedTimers; // +0x2BC
	unsigned char m_pad2BD[0x2DC - 0x2BD];
	AIPlayerView *m_ai; // +0x2DC
	unsigned char m_pad2E0[0x32C - 0x2E0];
	PlayerTeamList m_playerTeamPrototypes; // +0x32C
	unsigned char m_pad330[0x33E - 0x330];
	Bool m_logicalRetaliationModeEnabled; // +0x33E
	unsigned char m_pad33F[0x3BC - 0x33F];
	ScoreKeeper m_scoreKeeper; // +0x3BC
};

void Player::update()
{
	if (m_ai)
		m_ai->update();

	{
		Rva000411084 it;
		for (m_productionSpeedTimers.first(&it); it.current; it.next())
		{
			NameTimerNode *node = (NameTimerNode *)it.current;
			if (((NameTimerNode *)it.current)->m_value != 0)
			{
				((NameTimerNode *)it.current)->m_value--;
				// Residue: retail re-reads the count at [eax+8] without reloading
				// it.current; this path reloads it (one extra mov).
				if (((NameTimerNode *)it.current)->m_value == 0)
			{
				const AsciiString &name = *(const AsciiString *)node->m_key;
				m_productionSpeedBonus.rva001FDE3F(name) = m_startingProductionSpeedBonus.rva001FDE3F(name);
				}
			}
		}
	}

	// Allow the teams this player owns to update themselves.
	PlayerTeamList teams(m_playerTeamPrototypes);
	PlayerTeamList::iterator end = teams.end();
	for (PlayerTeamList::iterator pit = teams.begin(); pit != end; ++pit)
	{
		for (DLINK_ITERATOR<Team> iter = (*pit)->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			team->updateGenericScripts();
		}
	}

	if (ThePlayerList->getLocalPlayer() == this)
	{
		UnsignedInt now = TheGameLogic->getFrame();
		if (now % BfmeLogicFramesPerSecond == 0)
		{
			if (TheGlobalData->m_clientRetaliationModeEnabled != isLogicalRetaliationModeEnabled())
			{
				GameMessage *msg = TheMessageStream->appendMessage(GameMessage::MSG_ENABLE_RETALIATION_MODE);
				if (msg)
				{
					msg->appendIntegerArgument(getPlayerIndex());
					msg->appendBooleanArgument(TheGlobalData->m_clientRetaliationModeEnabled);
				}
			}
		}
	}

	rva002AD1FD();
	m_scoreKeeper.updateFrame(TheGameLogic->getFrame());
}
