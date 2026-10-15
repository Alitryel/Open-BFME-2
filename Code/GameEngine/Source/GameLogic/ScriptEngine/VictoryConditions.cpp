// cl: /O1 /EHsc /MD /arch:SSE
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

typedef bool Bool;
typedef int Int;

class PlayerTemplate;
class Team;
enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };
class ParticleSystem { public: bool isSaveable() const; };	// 0x002AA223 (rowed under this name)
extern "C" void *__cdecl memset(void *dst, int value, unsigned int size);

// The 28-byte by-value kind filter retail copies through the rowed copy
// constructor 0x0004543D; a one-bit filter is built in place (memset, then
// the bit's byte).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
	__forceinline explicit BfmeFixedStorage0004543D(Int bit)
	{
		memset(w, 0, sizeof(w));
		((unsigned char *)w)[bit / 8] |= 1 << (bit % 8);
	}
	unsigned int w[7];
};
template <int N> class BitFlags;
extern BitFlags<116> KINDOFMASK_NONE;
class BfmeTab1026;
class Rva002AA22AByteField { public: unsigned char get() const; };	// 0x002AA22A

class Player {
public:
 Bool isLocalPlayer() const;
 Bool rva002AB295(BfmeFixedStorage0004543D mask, Bool flag) const;
 Bool rva002AB2D9(BfmeTab1026 *tab, Bool flag) const;
 Bool rva002AB341(BfmeFixedStorage0004543D mask, BfmeFixedStorage0004543D exclude) const;
 Bool rva002AB390(BfmeTab1026 *tab) const;
 Bool hasAnyObjects(Bool flag) const;
 Relationship getRelationship(const Team *that) const;
 Team *getDefaultTeam() const { return defaultTeam; }
 char prefix[0x34]; const PlayerTemplate *playerTemplate;
 char pad38[0x2EC - 0x38]; Team *defaultTeam; // +0x2EC
};
class Rva0023D229 {public:void rva0023D24C(Int slot);};
class GameLogic;
extern GameLogic *TheGameLogic;
// Fields testDefeat reads: TheGameLogic +0x110 (game mode, 9 refuses any
// defeat) and +0x114 (3 skips the selection lock); TheWritableGlobalData
// +0xEBC/+0xEC0 (the two template tables the structure conditions test).
struct VictoryGameLogicView { char m_pad[0x110]; Int m_mode; Int m_network; };
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct VictoryGlobalDataView { char m_pad[0xEBC]; unsigned int m_buildingTable; unsigned int m_unitTable; };
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

// ?isSelectionLocked@BfmeSelectionState@@QBE_NXZ, rowed 0x0004253A (20 bytes,
// InGameUI_isSelectionLocked.cpp): a visible noinline copy of the same body,
// so cl knows the call leaves TheGameLogic alone and keeps it in ESI across it.
class BfmeSelectionState
{
public:
	__declspec(noinline) bool isSelectionLocked() const { return m_first != 0 && m_second != 0; }
private:
	unsigned char m_pad[0xB4];
	unsigned char m_first;
	unsigned char m_second;
};
class PlayerList {public:char prefix[0x18];Player *neutralPlayer;};
extern PlayerList *ThePlayerList;
enum NameKeyType { NAMEKEY_INVALID=0 };
class NameKeyGenerator {public:NameKeyType nameToKey(const char *);};
extern NameKeyGenerator *TheNameKeyGenerator;
class PlayerTemplateStore {public:const PlayerTemplate *findPlayerTemplate(NameKeyType)const;};
extern PlayerTemplateStore *ThePlayerTemplateStore;


enum { MAX_PLAYER_COUNT = 20 };

class VictoryConditions
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual Bool hasAchievedVictory(Player *player);	// +0x38
	virtual Bool hasBeenDefeated(Player *player);		// +0x3C
	virtual Bool hasSinglePlayerBeenDefeated(Player *player);	// +0x40
 virtual void slot17();virtual void slot18();
	virtual Bool isLocalAlliedDefeat();			// +0x4C
 virtual void slot20();virtual void slot21();virtual void slot22();
 virtual void slot23();virtual void slot24();virtual void slot25();
 virtual Bool rva00420017(Player *player);
 virtual void slot27(); virtual void slot28();
	virtual Bool slot29();					// +0x74 (rowed byte getter +0x90)

	Bool testDefeat(Player *player);			// 0x004207D4


private:
	unsigned char m_pad04[0x0C - 4];
	Int m_victoryCondition;				// +0x0C (testDefeat's switch)
	unsigned char m_pad10[0x18 - 0x10];
	Player *m_players[MAX_PLAYER_COUNT];		// +0x18
	Int m_localSlotNum;				// +0x68
	unsigned char m_pad6C[0x85 - 0x6c];
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

// VictoryConditions::testDefeat, retail 0x004207D4 (312 bytes), named by its
// own assert string in WB 0x01115160 (same flow, BFME2's offsets): a player
// flagged by 0x002AA22A is defeated; a selection lock outside game type 3, or
// game mode 9, defeats nobody; otherwise the +0x0C condition picks the test:
// 0 no object of kind 177 (0x002AB295), 1 no objects at all, 2 neither a
// building of the +0xEBC table nor an object of kind 14 (0x002AB341 against
// KINDOFMASK_NONE), 3 neither a +0xEBC building nor a +0xEC0 unit. WB keeps
// the value 3 test (0x002AB390) before value 2's in the source, which gives
// retail's shared negate tail in value 2's block.
Bool VictoryConditions::testDefeat(Player *player)
{
	if (((const Rva002AA22AByteField *)player)->get())
		return true;
	if (((VictoryGameLogicView *)TheGameLogic)->m_network != 3 && TheLivingWorldLogic
		&& ((BfmeSelectionState *)TheLivingWorldLogic)->isSelectionLocked())
		return false;
	if (((VictoryGameLogicView *)TheGameLogic)->m_mode == 9)
		return false;

	switch (m_victoryCondition)
	{
	case 0:
	{
		BfmeFixedStorage0004543D mask(177);
		if (!player->rva002AB295(mask, false))
			return true;
		break;
	}
	case 1:
		if (!player->hasAnyObjects(false))
			return true;
		break;
	case 3:
		if (player->rva002AB2D9((BfmeTab1026 *)&((VictoryGlobalDataView *)TheWritableGlobalData)->m_buildingTable, false))
			return false;
		return player->rva002AB390((BfmeTab1026 *)&((VictoryGlobalDataView *)TheWritableGlobalData)->m_unitTable) ? false : true;
	case 2:
	{
		if (player->rva002AB2D9((BfmeTab1026 *)&((VictoryGlobalDataView *)TheWritableGlobalData)->m_buildingTable, false))
			return false;
		BfmeFixedStorage0004543D mask(14);
		return player->rva002AB341(mask, *(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE) ? false : true;
	}
	}
	return false;
}

// VictoryConditions::hasSinglePlayerBeenDefeated, retail 0x0042090C (65 bytes),
// vtable slot 16 (+0x40, after hasAchievedVictory and hasBeenDefeated as in
// Zero Hour's VictoryConditionsInterface). WB 0x011154F0 has the same flow:
// refuse a missing or 0x002AA223-flagged player, answer true when the slot 29
// byte is set, else ask testDefeat (0x004207D4, named by its own WB assert
// string) and count each defeat in +0x88.
Bool VictoryConditions::hasSinglePlayerBeenDefeated(Player *player)
{
	if (!isEligiblePlayer(player))
		return false;
	if (slot29())
		return true;
	Bool defeated = testDefeat(player);
	if (defeated)
		++m_field88;
	return defeated;
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
