// ?rva003E8E23@ScriptConditions@@IAE_NPAVParameter@@000@Z
// partial score=0.9567 date=2026-10-19
// ?rva003E8E23@ScriptConditions@@IAE_NPAVParameter@@000@Z
// partial score=0.873 date=2026-10-17
// ?rva003E8E23@ScriptConditions@@IAE_NPAVParameter@@000@Z
// partial score=0.9586 date=2026-10-15
// ?rva003E8E23@ScriptConditions@@IAE_NPAVParameter@@000@Z
// partial score=0.8316 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /Ireference/shims/moduledata /DNDEBUG /MD /EHsc
//
// BFME2 player-wide team walk conditions. The count conditions resolve a player from a
// player Parameter (rowed ScriptEngine::rva00357B82 mask plus
// PlayerList::getPlayerFromMask 0x002A7B91), then walks that player's +0x32C
// team-prototype list, every prototype's +0x334 team instance list (member
// pointer 0x009C4AF5) and every team's member list (rowed
// iterate_TeamMemberList 0x00263864 and advance 0x00263526), counting the
// members that pass the condition's test.
//
// ?rva003E85E0@ScriptConditions@@IAE_NPAVParameter@@00@Z @ 0x003E85E0 195B
// Target evidence: evaluateCondition's jump table (0x007EC5C0, index minus 5)
// sends condition 176 here; initConditionTemplates names template 176
// ANY_HERO_REACHED_RANK. Counts members whose template has KindOf bit 90
// (template byte +0x113 bit 2) and whose Object+0x264 record holds a +0x24
// rank at least the third Parameter's int, and returns count >= the second
// Parameter's int. The +0x264/+0x24 rank matches the rowed
// evaluateNamedUnitRankLevel (0x003E92DF). BFME2-only condition with no donor
// method name, so the method keeps an address name; reading bit 90 as the
// hero KindOf is an inference from the template name.
//
// ?rva003E8AA9@ScriptConditions@@IAE_NPAVParameter@@@Z @ 0x003E8AA9 158B
// Target evidence: jump-table index 176 sends condition 181 here; the
// template is named ANY_UNITS_USING_BLOODTHIRSTY. True when any member of the
// player's teams has Object status 0x41 (rowed testStatus 0x0004E536). The
// BFME1 donor ScriptConditionsAnyUnitsUsingBloodthirsty.cpp has the same walk;
// its status bit name is not carried over.
//
// Skirmish comparison conditions (Zero Hour ScriptConditions.cpp names; the
// condition numbers come from evaluateCondition's jump table and the template
// help strings initConditionTemplates stores for them):
//
// ?evaluateSkirmishUnownedFactionUnitComparison@ScriptConditions@@IAE_NPAVParameter@@00@Z @ 0x003E749E 249B,
// condition 91 "Unowned faction unit -- comparison". Walks
// the neutral player (PlayerList+0x18, Zero Hour's getNeutralPlayer) and
// counts members with disabled-mask bit 5 (Object+0x1C8 & 0x20; Zero Hour
// DISABLED_UNMANNED), then Zero Hour's six-way comparison switch.
//
// ?evaluateSkirmishPlayerHasComparisonGarrisoned@ScriptConditions@@IAE_NPAVParameter@@00@Z @ 0x003E7597 333B,
// condition 93 "Player has garrisoned buildings --
// comparison". Counts members whose Object+0x250 contain module answers
// isGarrisonable (vtable +0x10) and getContainCount(0) > 0 (+0x114, the slot
// ScriptConditions_evaluateIsBuildingEmpty.cpp already uses).
//
// ?evaluateSkirmishPlayerHasComparisonCapturedUnits@ScriptConditions@@IAE_NPAVParameter@@00@Z @ 0x003E76E4 283B,
// condition 94 "Player has captured units -- comparison".
// Counts members with private status bit 0x04 (Object+0x438; Zero Hour
// isCaptured).
//
// ?evaluateSkirmishPlayerHasDiscoveredPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z @ 0x003E79F5 263B,
// condition 99 "Player has discovered another player".
// True when a member's shroud status for the discovering player's index
// (Player+0x54) is 1 or 2. The callee 0x0028D2A2 is rowed as
// Object::getShroudStatusForPlayer returning CellShroudStatus; its fallback
// value 1 and this caller's 1/2 test are Zero Hour's getShroudedStatus
// OBJECTSHROUD_CLEAR / OBJECTSHROUD_PARTIAL_CLEAR, so the result is read
// through that enum here.
//
// BFME2 differs from Zero Hour in the three player-parameter conditions:
// they walk every player of the parameter's mask (rowed getEachPlayerFromMask
// 0x002A7BC9) instead of playerFromParam, and evaluate the comparison per
// player, as the BFME1 donors ScriptConditionsGarrisonedUnits.cpp and
// ScriptConditionsSkirmishPlayerHasDiscoveredPlayer.cpp also do.
//
// Donor shape (Zero Hour): the DLINK_ITERATOR with the checked advance and
// the null-team / null-member skips, as in PlayerRva002AD93A.cpp.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef bool Bool;
typedef int Int;

class Object;

template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}
	void advance()
	{
		if (m_cur)
			m_cur = ((*m_cur).*(m_getNextFunc))();
	}
	Bool done() const
	{
		return m_cur == 0;
	}
	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

// The member iterator BFME2 returns by value from Team::iterate_TeamMemberList
// (24 bytes, out-of-line advance; see TeamRva0039DDC2.cpp).
template <>
class DLINK_ITERATOR<Object>
{
private:
	Object *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	Bool done() const { return m_cur == 0; }
	Object *cur() const { return m_cur; }
	// Retail re-reads the iterator's current object after each callee (the loop test and the
	// second member call do not share the first load); a view reproduces that.
	Object *vcur() const { return *(Object * volatile *)&m_cur; }
};

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};

#include "Common/Snapshot.h"

class AsciiString;

class Parameter
{
public:
	Int getInt() const { return m_int; }
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the getInt copy loses to the first-in-order copy. No flags touched.
	Int bfme_getInt_f996b() const { return m_int; }
	const AsciiString *getString() const { return (const AsciiString *)m_string; }
private:
	unsigned char m_beforeInt[8];
	Int m_int; // +0x08
	float m_real; // +0x0C
	unsigned char m_string[4]; // +0x10 (AsciiString)
};

enum KindOfType
{
	KINDOF_90 = 90
};

class ThingTemplate
{
public:
	Bool isEquivalentTo(const ThingTemplate *other) const;
	Bool isKindOf(KindOfType t) const
	{
		return (m_kindOf[t >> 3] >> (t & 7)) & 1;
	}
	// LINK: same-body helper under a TU-unique name (identical inlined bytes); the isKindOf
	// copy loses to the kept copy. No flags touched.
	Bool bfme_isKindOf_puc(KindOfType t) const
	{
		return (m_kindOf[t >> 3] >> (t & 7)) & 1;
	}
private:
	unsigned char m_pad[0x108];
	unsigned char m_kindOf[16]; // +0x108
};

class Vector3i16;

// ledger 0x000B49A1 (named MeshGeometryClass::get_polys): [[this+0x2C]+0xC].
class MeshGeometryClass
{
protected:
	Vector3i16 *get_polys();
};

class ExperienceTracker : public MeshGeometryClass
{
public:
	Int getRank() const { return m_rank; }
	Int getLevelCap() { return (Int)get_polys(); }
private:
	unsigned char m_pad[0x24];
	Int m_rank; // +0x24
};

enum DisabledType
{
	DISABLED_UNMANNED = 5
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_COUNT = 0x80
};

// ThingFactory's template lookup (ledger 0x002D06CA, held under this name).
class UpgradeTemplate;

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

// The module record Object::rva0028C197 returns: a vtable whose slot 59
// (+0xEC) answers a status flag.
class Rva0028C197Module
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04();
	virtual void slot05(); virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54();
	virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58();
	virtual Bool slot59();
};

// Object::testBit 0x0028D891: the opaque bit-test twin owner (the Object itself).
class Rva0028D891Owner
{
public:
	Bool testBit(Int bit) const;
};

// Object::rva0028BD92(0x27) returns a record whose +0x20 sub-object answers
// a flag in vtable slot 2.
class Rva0028BD92Flag
{
public:
	virtual void slot00(); virtual void slot01();
	virtual Bool answers();
};

struct ContainedItemsNode
{
	ContainedItemsNode *m_next;
	ContainedItemsNode *m_prev;
	Object *m_data;
};

struct ContainedItemsList
{
	ContainedItemsNode *m_node;
};

// Returned by value (hidden pointer) from contain-module vtable slot 0x118;
// the walk reads only the list pointer at +4.
class Rva003E8863ContainedItems
{
public:
	const ContainedItemsList *getList() const { return m_list; }
private:
	Int m_unknown;
	const ContainedItemsList *m_list;
};

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Bool isGarrisonable() const; // +0x10
	virtual void slot05(); virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54();
	virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63(); virtual void slot64();
	virtual void slot65(); virtual void slot66(); virtual void slot67(); virtual void slot68();
	virtual unsigned int getContainCount(Int extra) const; // +0x114
	virtual Rva003E8863ContainedItems getContainedItems() const; // +0x118
};

enum ObjectPrivateStatusBits
{
	CAPTURED = 0x04
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR
};

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR
};

class Object
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex) const;
	ContainModuleInterface *getContain() const { return m_contain; }
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool testBit(Int bit) const { return ((const Rva0028D891Owner *)this)->testBit(bit); }
	Bool rva00290D2B(const UpgradeTemplate *upgrade) const;
	void *rva0028C197() const;
	void *rva0028BD92(Int slot);
	const ThingTemplate *getTemplate() const { return m_template; }
	ExperienceTracker *getExperienceTracker() const { return m_experienceTracker; }
	Bool isCaptured() const { return (m_privateStatus & CAPTURED) != 0; }
	Bool isDisabledByType(DisabledType type) const
	{
		return (m_disabledMask[type >> 3] >> (type & 7)) & 1;
	}
	Bool bfme_isDisabledByType_puc(DisabledType type) const
	{
		return (m_disabledMask[type >> 3] >> (type & 7)) & 1;
	}
private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad[0x1C8 - 8];
	unsigned char m_disabledMask[4]; // +0x1C8
	unsigned char m_pad1CC[0x250 - 0x1CC];
	ContainModuleInterface *m_contain; // +0x250
	unsigned char m_pad254[0x264 - 0x254];
	ExperienceTracker *m_experienceTracker; // +0x264
	unsigned char m_pad268[0x438 - 0x268];
	unsigned char m_privateStatus; // +0x438
};

class Team : public MemoryPoolObject, public Snapshot
{
public:
	Team *dlink_next_TeamInstanceList() const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
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

struct PlayerTeamNode
{
	PlayerTeamNode *m_next;
	PlayerTeamNode *m_prev;
	TeamPrototype *m_value;
};

class Player
{
public:
	PlayerTeamNode *getPlayerTeams() const { return m_playerTeamPrototypes; }
	Int getPlayerIndex() const { return m_playerIndex; }
private:
	char m_pad[0x54];
	Int m_playerIndex; // +0x54
	char m_pad58[0x32C - 0x58];
	PlayerTeamNode *m_playerTeamPrototypes; // +0x32C
};

class PlayerList
{
public:
	Player *getPlayerFromMask(Int mask);
	Player *getEachPlayerFromMask(Int &mask);
	Player *getNeutralPlayer() const { return m_neutralPlayer; }
private:
	unsigned char m_pad[0x18];
	Player *m_neutralPlayer; // +0x18
};
extern PlayerList *ThePlayerList;

class ObjectTypes;

class ScriptEngine
{
public:
	Int rva00357B82(Parameter *playerParm);
	Int rva00357475(const AsciiString &name, Bool *exists = 0);
	ObjectTypes *getObjectTypes(const AsciiString &name);
};
extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool rva003E8785(Parameter *playerParm, Parameter *countParm, Parameter *upgradeParm);
	Bool rva003E85E0(Parameter *playerParm, Parameter *countParm, Parameter *rankParm);
	Bool rva003E8AA9(Parameter *playerParm);
	Bool rva003E86A3(Parameter *playerParm, Parameter *countParm, Parameter *modeParm);
	Bool rva003E8863(Parameter *playerParm, Parameter *countParm, Parameter *loadedParm, Parameter *transportParm);
	Bool rva003E89A9(Parameter *playerParm, Parameter *templateParm);
	Bool rva003E8B47(Parameter *playerParm, Parameter *templateParm);
	Bool rva003E8C24(Parameter *playerParm, Parameter *templateParm);
	Bool evaluateSkirmishUnownedFactionUnitComparison(Parameter *pSkirmishPlayerParm, Parameter *pComparisonParm, Parameter *pCountParm);
	Bool evaluateSkirmishPlayerHasComparisonGarrisoned(Parameter *pSkirmishPlayerParm, Parameter *pComparisonParm, Parameter *pCountParm);
	Bool evaluateSkirmishPlayerHasComparisonCapturedUnits(Parameter *pSkirmishPlayerParm, Parameter *pComparisonParm, Parameter *pCountParm);
	Bool evaluateSkirmishPlayerHasDiscoveredPlayer(Parameter *pSkirmishPlayerParm, Parameter *pDiscoveredByParm);
	Bool rva003E8E23(Parameter *playerParm, Parameter *typeParm, Parameter *comparisonParm, Parameter *rankParm);
};


class Rva00376A62
{
public:
	Bool rva00376A84(const void *thing);
};
class ObjectTypes
{
public:
	virtual ~ObjectTypes();
	Bool isInSet(const ThingTemplate *tmpl) const
	{
		return ((Rva00376A62 *)this)->rva00376A84(tmpl);
	}
};
class ObjectTypesTemp
{
public:
	ObjectTypesTemp();
	~ObjectTypesTemp() { ::delete m_types; }
	ObjectTypes *m_types;
};
void Script_objectTypesFromParam(Parameter *typeParm, ObjectTypes *types);

// Retail passes ObjectTypes by value and uses global delete after virtual destruction.
// The true-exit cleanup is three bytes longer than retail; see reverse/attempt_support/3e8e23-worker-20261019.md.
Bool ScriptConditions::rva003E8E23(Parameter *playerParm, Parameter *typeParm, Parameter *comparisonParm, Parameter *rankParm)
{
	Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357475(*playerParm->getString(), 0));
	if (!player)
		return false;
	const ThingTemplate *thingTemplate = 0;
	ObjectTypes *types = TheScriptEngine->getObjectTypes(*typeParm->getString());
	ObjectTypesTemp typesTemp;
	if (types)
		Script_objectTypesFromParam(typeParm, typesTemp.m_types);
	else
		thingTemplate = TheThingFactory->findTemplate(*typeParm->getString());
	PlayerTeamNode *head = player->getPlayerTeams();
	for (PlayerTeamNode *it = head->m_next; it != player->getPlayerTeams(); it = it->m_next)
	{
		for (DLINK_ITERATOR<Team> iter = it->m_value->iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			Team *team = iter.cur();
			if (!team)
				continue;
			Object *obj;
			for (DLINK_ITERATOR<Object> iter2 = team->iterate_TeamMemberList(); (obj = iter2.cur()) != 0; iter2.advance())
			{
				_ReadWriteBarrier();
				Bool typeMatches;
				if (types)
					typeMatches = typesTemp.m_types->isInSet(obj->getTemplate());
				else
					typeMatches = obj->getTemplate()->isEquivalentTo(thingTemplate);
				if (typeMatches)
				{
					ExperienceTracker *tracker = obj->getExperienceTracker();
					if (tracker)
					{
						Int rank = tracker->getRank();
						Bool matches = false;
						switch (comparisonParm->getInt())
						{
							case 0: matches = rank < rankParm->getInt(); break;
							case 1: matches = rank <= rankParm->getInt(); break;
							case 2: matches = rank == rankParm->getInt(); break;
							case 3: matches = rank >= rankParm->getInt(); break;
							case 4: matches = rank > rankParm->getInt(); break;
							case 5: matches = rank != rankParm->getInt(); break;
						}
						if (matches == 1)
							return true;
					}
				}
			}
		}
	}
	return false;

}
