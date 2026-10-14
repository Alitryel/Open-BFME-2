// ?update@VictoryConditions@@UAEXXZ
// partial score=0.72 date=2026-10-14
// ?update@VictoryConditions@@UAEXXZ
// partial score=0.62 date=2026-10-14
// cl: /O1 /EHsc /MD /Ireference/shims/bfme2_ascii
// VictoryConditions.cpp -- VictoryConditions members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function (vtable pairing); retail supplies the bytes. The body is Zero
// Hour's (GameLogic/ScriptEngine/VictoryConditions.cpp) with BFME2's observer
// branch, which also requires a positive count at +0x88, and a range check on
// the local slot.
//
// Layout (target evidence): m_players[20] at +0x18, m_localSlotNum at +0x68,
// m_singleAllianceRemaining at +0x85, m_isObserver at +0x86, an int at +0x88.
// hasBeenDefeated is vtable slot 15 (+0x3C).

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

class PlayerTemplate;
class Team;
enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };
class ParticleSystem { public: bool isSaveable() const; };	// 0x002AA223 (rowed under this name)
class Player {
public:
 Bool isLocalPlayer() const;
 Relationship getRelationship(const Team *that) const;
 Relationship getRelationship(const Player *that) const;
 Bool isSkirmishAIPlayer();
 Team *getDefaultTeam() const { return defaultTeam; }
 const AsciiString &getDisplayName() const { return m_display38 ? *(const AsciiString *)((const char *)m_display38 + 8) : AsciiString::TheEmptyString; }
 char prefix[0x34]; const PlayerTemplate *playerTemplate;
 void *m_display38;				// +0x38
 char pad3C[0x50 - 0x3C]; unsigned m_playerNameKey;	// +0x50
 int m_playerIndex;				// +0x54
 char pad58[0x2EC - 0x58]; Team *defaultTeam; // +0x2EC
 char pad2F0[0x3AC - 0x2F0]; unsigned m_id;	// +0x3AC
 char pad3B0[0x4AC - 0x3B0]; unsigned m_484;	// +0x4AC
};
class Rva0023D229 {public:void rva0023D24C(Int slot);void Set(Int slot);};
class GameLogic;
extern GameLogic *TheGameLogic;
class PlayerList {public:char prefix[0x10];Player *m_local;Player *neutralPlayer;};
extern PlayerList *ThePlayerList;
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator {public:NameKeyType nameToKey(const char *);NameKeyType nameToKey(const AsciiString &);};
extern NameKeyGenerator *TheNameKeyGenerator;
class PlayerTemplateStore {public:const PlayerTemplate *findPlayerTemplate(NameKeyType)const;};
extern PlayerTemplateStore *ThePlayerTemplateStore;


enum { MAX_PLAYER_COUNT = 20 };

class VictoryConditions
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void update(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual Bool hasAchievedVictory(Player *player);	// +0x38
	virtual Bool hasBeenDefeated(Player *player);		// +0x3C
	virtual Bool hasSinglePlayerBeenDefeated(Player *player);	// +0x40
 virtual void slot17();virtual void slot18();
	virtual Bool isLocalAlliedDefeat();			// +0x4C
 virtual void slot20();virtual void slot21();virtual void slot22();
 virtual void showEndGame(const AsciiString &apt, bool flag, const AsciiString &gui, const AsciiString &empty);	// +0x5C
 virtual void slot24();virtual void slot25();
 virtual Bool rva00420017(Player *player);
 virtual void slot27();virtual void slot28();virtual void slot29();virtual void slot30();
 virtual void updateEndGame();				// +0x7C


private:
	unsigned char m_pad04[0x18 - 4];
	Player *m_players[MAX_PLAYER_COUNT];		// +0x18
	Int m_localSlotNum;				// +0x68
	unsigned m_endFrame;				// +0x6C
	Bool m_isDefeated[MAX_PLAYER_COUNT];		// +0x70
	Bool m_singleAllianceRemaining;			// +0x85
	Bool m_isObserver;				// +0x86
	Int m_field88;					// +0x88
 Int m_cachedPlayerCount; // +0x8C
};

// Zero Hour's file-static areAllies, retail 0x0041FE35 (46 bytes): kept out
// of line, cl 7.1 passes its two players in EDI and ESI.
#pragma auto_inline(off)
static Bool areAllies(const Player *p1, const Player *p2)
{
	if (p1 != p2 &&
		p1->getRelationship(p2->getDefaultTeam()) == ALLIES &&
		p2->getRelationship(p1->getDefaultTeam()) == ALLIES)
		return true;
	return false;
}
#pragma auto_inline(on)

// A player that may win: present and not flagged by 0x002AA223.
static __forceinline Bool isEligiblePlayer(Player *player)
{
	return player && !((const ParticleSystem *)player)->isSaveable();
}

// VictoryConditions::hasAchievedVictory, retail 0x0041FEEB (131 bytes),
// vtable slot 14: Zero Hour's body, which BFME2 also refuses for the player
// flagged by 0x002AA223, gates on a positive +0x88 count and reports the
// winning slot to TheGameLogic (0x0023D24C). Retail saves EBX/EDI only after
// the early return: the opening test is an inlined helper and the rest its
// else scope (a plain early return saves them at entry).
Bool VictoryConditions::hasAchievedVictory(Player *player)
{
	if (!isEligiblePlayer(player))
		return false;
	else
	{
		if (m_singleAllianceRemaining && m_field88 > 0)
		{
			for (Int i=0; i<MAX_PLAYER_COUNT; ++i)
			{
				if (m_players[i] && !hasSinglePlayerBeenDefeated(m_players[i]) && (player == m_players[i] || areAllies(m_players[i], player)))
				{
					((Rva0023D229 *)TheGameLogic)->rva0023D24C(i);
					return true;
				}
			}
		}

		return false;
	}
}

// VictoryConditions::hasBeenDefeated, retail 0x0041FF6E (63 bytes), vtable slot 15.
Bool VictoryConditions::hasBeenDefeated(Player *player)
{
	if (!isEligiblePlayer(player))
		return false;

	if (m_singleAllianceRemaining && m_field88 > 0 && !hasAchievedVictory(player))
		return true;

	return false;
}

// VictoryConditions::isLocalAlliedDefeat, retail 0x004200CB.
Bool VictoryConditions::isLocalAlliedDefeat()
{
	if (m_isObserver)
	{
		if (m_field88 > 0)
			return m_singleAllianceRemaining;
		return false;
	}
	if (m_localSlotNum < 0 || m_localSlotNum >= sizeof(m_players) / sizeof(m_players[0]))
		return false;
	return hasBeenDefeated(m_players[m_localSlotNum]);
}

// Native420017..42008F RET4; WB11156D0 VictoryConditions.cpp cache-one flow.
// Same eligibility test as GeneralsMD cachePlayerPtrs; target extracts it into
// a bool helper and uses the member counter+8C. Original helper name unknown.
Bool VictoryConditions::rva00420017(Player *player)
{
 const PlayerTemplate *civilian = ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey("FactionCivilian"));
 if (player && player != ThePlayerList->neutralPlayer && player->playerTemplate && player->playerTemplate != civilian && !((const ParticleSystem *)player)->isSaveable()) {
  m_players[m_cachedPlayerCount] = player;
  if (m_players[m_cachedPlayerCount]->isLocalPlayer()) m_localSlotNum=m_cachedPlayerCount;
  ++m_cachedPlayerCount;
  return true;
 }
 return false;
}

// ============================================================================
// VictoryConditions::update, retail 0x00420388 (1100 B), vtable slot 5 (+0x14).
// Zero Hour's update with BFME2's observer gate, the LivingWorld / skirmish-AI
// forfeit block and BFME2 field offsets. The delay is GlobalData::m_110C times
// BfmeLogicFramesPerSecond (retail VA 0x00DBA4E4); the player walk is 20 slots.
// Every callee is a ledger row named by the WorldBuilder debug body.
// ============================================================================

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Rva00420388GlobalData { char pad[0x110C]; float m_110C; };
extern int BfmeLogicFramesPerSecond;

class RecorderClass { public: Bool isMultiplayer(); };
extern RecorderClass *TheRecorder;

class Rva0023C6A4 { public: Bool rva00200084(); };
class Rva0023C666 { public: int rva0023C666(); };
class Rva00210C66CmpBoolField { public: Bool get() const; };

class PlayerTemplate {
public:
	char pad[0x1BC];
	Bool m_1bc;
};

// GameLogic view for this body only; the canonical lookup header describes the
// same native class but not these frame/mode fields.
class GameLogic {
public:
	char pad40[0x40];
	unsigned m_frame;			// +0x40
	char pad44[0x98 - 0x44];
	Bool m_98;				// +0x98
	char pad99[0x110 - 0x99];
	int m_110;				// +0x110
	int m_114;				// +0x114
	Bool isInMultiplayerGame();
};

class GameSlot {
public:
	Bool isAI() const;
	char pad34[0x34];
	AsciiString m_name;			// +0x34
	char pad3C[0x44 - 0x3C];
	unsigned m_frame;			// +0x44
};

class GameInfo {
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual Bool unidentifiedSlot12();	// +0x50
	GameSlot *getSlot(Int slot);
};
extern GameInfo *g_00E02EEC;

class InGameUI {
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual void message(AsciiString text, ...);	// +0x3C
	virtual void s16(); virtual void s17();
	virtual void message2(AsciiString text, const AsciiString &arg);	// +0x48
};
extern InGameUI *TheInGameUI;

struct Coord3D;
enum EvaEventID { EVA_EVENT_0 = 0 };
class Eva { public: Bool reportEvaEvent(EvaEventID event, const Coord3D *position, const Coord3D *secondPosition); };
extern Eva *TheEva;

extern int g_00DFE4CC;

class PartitionManager { public: void revealMapForPlayerPermanently(Int playerIndex); };
extern PartitionManager *TheShroudManager;

class Rva002E2903Player { public: char pad[0x3C4]; Bool m_3c4; };
class Rva002AB5C7Player { public: void rva002AB44A(); };
struct Rva0059E647World;
extern Rva0059E647World *g_rva0059E647World;
class Rva002BA8F1Logic { public: Rva002E2903Player *find(Int id, unsigned *flag); };

void VictoryConditions::update()
{
	unsigned frame = TheGameLogic->m_frame;
	_ReadWriteBarrier();
	updateEndGame();
	unsigned delay = (int)(TheWritableGlobalData
		? ((Rva00420388GlobalData *)TheWritableGlobalData)->m_110C * (float)BfmeLogicFramesPerSecond
		: 25.0f);
	if (!TheRecorder->isMultiplayer())
		return;
	if (m_localSlotNum == -1 && !m_isObserver)
		return;
	if (frame < delay)
		return;

	if (!m_singleAllianceRemaining)
	{
		Player *first = 0;
		volatile Bool onlyOneAlliance = true;
		for (Int i = 0; i < MAX_PLAYER_COUNT; i++)
		{
			Player *p = m_players[i];
			if (p && !hasSinglePlayerBeenDefeated(p))
			{
				if (first)
				{
					if (!areAllies(first, p))
					{
						onlyOneAlliance = false;
						break;
					}
				}
				else
					first = p;
			}
		}
		if (onlyOneAlliance)
		{
			m_singleAllianceRemaining = true;
			m_endFrame = frame;
			if (!((GameInfo *)g_00E02EEC)->unidentifiedSlot12())
				TheGameLogic->m_98 = false;
		}
	}

	for (Int i = 0; i < MAX_PLAYER_COUNT; i++)
	{
		Player *p = m_players[i];
		if (!p)
			continue;
		if (m_isDefeated[i])
			continue;
		if (!hasSinglePlayerBeenDefeated(p))
			continue;
		m_isDefeated[i] = true;
		((Rva0023D229 *)TheGameLogic)->Set(i);
		p->m_484 = frame;
		if (frame > 1)
		{
			TheShroudManager->revealMapForPlayerPermanently(p->m_playerIndex);
			if (((Rva0023C6A4 *)TheGameLogic)->rva00200084() && p->isLocalPlayer())
			{
				TheInGameUI->message(AsciiString("GUI:YouHaveBeenDefeated"));
			}
			else if (!((Rva0023C666 *)TheGameLogic)->rva0023C666() && TheGameLogic->m_114 != 0)
			{
				TheInGameUI->message2(AsciiString("GUI:PlayerHasBeenDefeated"), p->getDisplayName());
			}

			if ((TheGameLogic->isInMultiplayerGame() || TheGameLogic->m_110 != 2) &&
				ThePlayerList && TheEva && p->getDefaultTeam())
			{
				Player *local = ThePlayerList->m_local;
				if (local->getRelationship(p->getDefaultTeam()) == ALLIES)
				{
					if (local != p)
					{
						TheEva->reportEvaEvent((EvaEventID)6, 0, 0);
					}
					else if (g_00DFE4CC)
					{
						Player *local2 = ThePlayerList->m_local;
						if (local2)
						{
							AsciiString gui("Gui_DefeatScreen");
							AsciiString apt("APT:EndDefeat");
							showEndGame(apt,
								local2->playerTemplate ? ((PlayerTemplate *)local2->playerTemplate)->m_1bc : false,
								gui, AsciiString::TheEmptyString);
						}
					}
				}
				else
				{
					TheEva->reportEvaEvent((EvaEventID)7, 0, 0);
				}
			}

			if (((Rva00210C66CmpBoolField *)TheGameLogic)->get() && !p->isSkirmishAIPlayer())
			{
				Bool anyAlive = false;
				Bool anyOther = false;
				for (Int j = 0; j < MAX_PLAYER_COUNT; j++)
				{
					if (j == i)
						continue;
					Player *q = m_players[j];
					if (!q)
						continue;
					if (q->isSkirmishAIPlayer())
						continue;
					Rva002E2903Player * volatile r = ((Rva002BA8F1Logic *)g_rva0059E647World)->find(q->m_id, 0);
					if (q->getRelationship(p) != ENEMIES && r->m_3c4 == false)
						anyOther = true;
					if (!m_isDefeated[j])
						anyAlive = true;
				}
				if (anyOther && !anyAlive)
				{
					for (Int j = 0; j < MAX_PLAYER_COUNT; j++)
					{

						if (!(m_players[j]))
							continue;
						if (!(m_players[j])->isSkirmishAIPlayer())
							continue;
						if ((j ? m_isDefeated[j] : m_isDefeated[j]))
							continue;
						((Rva002AB5C7Player *)(m_players[j]))->rva002AB44A();
					}
				}
			}
		}

		for (Int j = 0; j < 8; j++)
		{
			AsciiString name;
			NameKeyType key = (NameKeyType)p->m_playerNameKey;
			if (key == TheNameKeyGenerator->nameToKey(name) && g_00E02EEC)
			{
				GameSlot *slot = ((GameInfo *)g_00E02EEC)->getSlot(j);
				if (slot && slot->isAI())
				{
					name = slot->m_name;
					slot->m_frame = frame;
				}
			}
		}
		((Rva002AB5C7Player *)p)->rva002AB44A();
	}
}
