// ?createContent@OldSchoolHelpBoxContentSource@@UAE?AUTreeHintRef00217D4C@@XZ
// partial score=0.955 date=2026-10-16
// W9-O1 r1 (2026-10-16, claude-opus-5.5, 125 min): callee 0x2940B9 is now rowed as ?affectedByUpgrade@Object@@QBE_NPBVUpgradeTemplate@@@Z
// (const) - the old rva002940B9 name left this bank UNRESOLVED; fixed below (nn10 / 3292 B, EH exact, same 3 hunks as r14).
// Findings: (1) the sciences loop may be a plain `for (int i = 0; i < (unsigned)(end()-begin()); ++i)` - cl rotates it to exactly the
// manual guard/do-while form (nn10 identical); (2) hero loop: guard `if (sciences.end()!=sciences.begin())` (operand order differs from the
// loop test) keeps the guard WITHOUT the barrier (for/do/while all canonicalise) -> 3285 B nn12, residue is only the retail `mov ebx,eax`
// copy (ours coalesces begin into ebx: `mov ebx,[ebp-0x5c]; cmp [ebp-0x58],ebx`); guard spelled like the loop test is threaded away.
// (3) else-arm residue mechanism (toy build/o1/tz.py, z11 frame): cl hoists the common `end` load of both arms into the predecessor BEFORE
// CSE, and CSE never flows from the predecessor into the jump-target arm, so `science = v[0]` reloads m_commandButton; with no inner guard
// in the loop arm (toy q2) the arm keeps its own reload and [0] CSEs with it. 216-variant toy grid (first/guard/else/[0] spellings),
// 180-variant real grid of the three size sites, IR-dead irsweep at 28 lines x 3 snippets, /O1 flag-order and /G6: all inert.
// ?createContent@OldSchoolHelpBoxContentSource@@UAE?AUTreeHintRef00217D4C@@XZ
// partial score=0.955 date=2026-10-15
// W7-G1 r14 RECIPE (nn10 / 3292 B vs bank 3287 nn10; residue = 3 hunks, see below). Stack of levers on the previous bank:
//  (1) bool requireAll / Player *payer locals with the assignment inside the call/comma (W7-ASTRA recipe): fixes the push-memory hunks;
//  (2) hero-science loop as guarded do/while (no entry jmp);
//  (3) NEW: the `_ReadWriteBarrier()` after `upgrade = m_commandButton->m_upgrade` is REMOVED and every m_sciences size() test is spelled
//      `(unsigned)(m_commandButton->m_sciences.end() - m_commandButton->m_sciences.begin())` (site 1, loop pretest guard, ==1 site):
//      the barrier only existed to stop cl materialising &m_commandButton->m_sciences (`add eax,0xa4`, `mov edi,0xa4`); the direct end-begin spelling
//      folds [eax+0xa8]/[eax+0xa4] like retail and fixes the extra `mov eax,[esi+0xc]` reload after the upgrade load (retail keeps eax = button);
//  (4) the loop is a manual do/while whose bottom test keeps `.size()` (retail's `add eax,0xa4; sub ecx,[eax]` this-form).
// RESIDUE: (a) loop pretest / ==1 site: ours copies the button to ecx (`mov ecx,eax; mov eax,[ecx+0xa8]`) and keeps the count in eax, retail keeps
// button in eax and the count in ecx (toy: build/g1/toys/z11.cpp reproduces it; declaration order/spelling grids inert); (b) hero loop begin:
// retail `mov eax,[begin]; cmp eax,[end]; ...; mov ebx,eax`, ours reloads `mov ebx,[ebp-0x5c]` because a barrier is needed to keep the guard
// (any guard without the fence is dropped by cl and the loop becomes jmp-to-test).
// ?createContent@OldSchoolHelpBoxContentSource@@UAE?AUTreeHintRef00217D4C@@XZ
// partial score=0.9543031778078934 date=2026-10-14
// ?createContent@OldSchoolHelpBoxContentSource@@UAE?AUTreeHintRef00217D4C@@XZ
// partial score=0.9543031778078934 date=2026-10-13
// W7-ASTRA next lead: starting from this size-exact body, hoisting the two
// argument values fixes independent native spill/load sites: declare bool
// requireAll and pass (requireAll=m_commandButton->m_requireAll) through the
// allRequiredUpgradesComplete call; declare Player *payer and assign
// payer=ThePlayerList->m_local before the UpgradeCenter call. Converting the
// guarded sciences for-loop to do/while removes its entry jump. Combined body
// is 3291B: normalized residue only upgrade-load reload and science begin
// reload instead of mov ebx,eax. Caching begin before the empty test instead
// makes 3284B: begin uses EBX too early and the 128-byte conditional becomes
// short. Neither variant is byte-exact. This bank retains best full score.
// ?createContent@OldSchoolHelpBoxContentSource@@UAE?AUTreeHintRef00217D4C@@XZ
// ?createContent@OldSchoolHelpBoxContentSource@@UAE?AUTreeHintRef00217D4C@@XZ
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// ?createContent@OldSchoolHelpBoxContentSource@@UAE?AUTreeHintRef00217D4C@@XZ
// Retail 0x00405E3D 3287 bytes RET4 (EH frame). Slot 3 of the help-source
// vftable 0x00838970 (deleting dtor 0x00406B1D first). WB twin 0x01078070
// OldSchoolHelpBoxContentSource::createContent in ControlBarPopupDescription.cpp
// gives the order: title / cost / time / description strings filled from the
// selected object's command button (science chain sciences upgrade object
// build cost command points prerequisites unit revival and castle unpack)
// then a 12-byte help record (rowed ctor 0x0056D5BD) returned through the
// reference-counted handle (ArmySummaryHelpSource pattern). Callee names are
// the ledger rows/pins at each address; offsets are read from retail.

// Vector storage is released through the pinned _STL::free (0x00030830).
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <vector>
#undef free
#include "ascii_string.h"
#include "unicode_string.h"

typedef unsigned short WideChar;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

struct TargetRef00217D4C
{
	void *vtable;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C(TargetRef00217D4C *p) : m_ptr(p)
	{
		if (m_ptr) ++m_ptr->references;
	}
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr) ++m_ptr->references;
	}
	~TreeHintRef00217D4C()
	{
		if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr);
	}
	TargetRef00217D4C *m_ptr;
};

struct UnicodeHeaderView
{
	int refs;
	unsigned short length;
};

struct UnicodeView
{
	static __forceinline bool isEmpty(const UnicodeString &s)
	{
		const UnicodeHeaderView *h = *(const UnicodeHeaderView *const *)&s;
		return h == 0 || h->length == 0;
	}
};

class Player;
class Object;
class ThingTemplate;
class UpgradeTemplate;
class Module;
class CreateAHeroData;
struct UpgradeRange
{
	UpgradeTemplate **m_begin;
	UpgradeTemplate **m_end;
};

#define HELP_SLOTS4(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3();
#define HELP_SLOTS16(p) HELP_SLOTS4(p##0) HELP_SLOTS4(p##1) HELP_SLOTS4(p##2) HELP_SLOTS4(p##3)

class GameTextInterface
{
public:
	HELP_SLOTS4(a) HELP_SLOTS4(b) HELP_SLOTS4(c)
	virtual void d0(); virtual void d1();
	virtual UnicodeString fetchA(const AsciiString &label, bool *exists);      // +0x38
	virtual UnicodeString fetchC(const char *label, bool *exists);             // +0x3C
	virtual UnicodeString *fetchPtrA(const AsciiString &label, bool *exists);  // +0x40
	virtual UnicodeString *fetchPtrC(const char *label, bool *exists);         // +0x44
};
extern GameTextInterface *TheGameText;

struct DrawableNode;
class Drawable
{
public:
	Object *getObject() const { return m_object; }

	char m_pad000[0xFC];
	Object *m_object;               // +0xFC
};

struct DrawableNode
{
	DrawableNode *next;
	DrawableNode *prev;
	Drawable *data;
};

struct DrawableList
{
	DrawableNode *m_node;
};

class InGameUI
{
public:
	HELP_SLOTS16(a) HELP_SLOTS16(b) HELP_SLOTS16(c) HELP_SLOTS16(d)
	HELP_SLOTS4(e0)
	virtual void e10(); virtual void e11();
	virtual int getSelectCount();                    // +0x118
	virtual void f1(); virtual void f2();
	virtual const DrawableList *getAllSelectedDrawables(); // +0x124
	virtual void f4();
	virtual Drawable *getFirstSelectedDrawable();    // +0x12C
};
extern InGameUI *TheInGameUI;

class BfmeMemberRV;
class BfmeThingRV
{
public:
	BfmeMemberRV *bfmePickRV();
};

class PlayerList
{
public:
	char m_pad00[0x10];
	Player *m_local;                // +0x10
};
extern PlayerList *ThePlayerList;

class ScienceStore
{
public:
	bool playerHasRootPrereqsForScience(const Player *player, ScienceType science) const;
	int getSciencePurchaseCost(ScienceType science) const;
};
extern ScienceStore *TheScienceStore;

class UpgradeCenter
{
public:
	bool rva0026F11A(Player *player, const UpgradeTemplate *upgrade, Object *obj, bool test);
};
extern UpgradeCenter *TheUpgradeCenter;

class UpgradeTemplate
{
public:
	unsigned int rva0026EF50(Player *player, Object *obj) const;
 void *m_0; int m_4;
};

class Rva002D371DAddImm32Field
{
public:
	int get() const;
};
class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

class Player
{
public:
	bool hasScience(ScienceType science) const;
	bool rva002AB82D(CreateAHeroData *data) const;
	bool rva002AB855(CreateAHeroData *data) const;
	bool rva002AA8EF(const UpgradeTemplate *upgrade) const;
	bool rva002AB87D(const UpgradeTemplate *upgrade) const;
	bool allowedToBuild(const ThingTemplate *thing) const;
};

class ProductionInterface
{
public:
	HELP_SLOTS4(a) HELP_SLOTS4(b) HELP_SLOTS4(c)
	virtual float getCost1(Player *player);          // +0x30
	virtual void d1(); virtual void d2(); virtual void d3();
	HELP_SLOTS4(e)
	virtual float getCost2(Player *player);          // +0x50
};

class BodyModule
{
public:
	HELP_SLOTS4(a)
	virtual void b0();
	virtual float getHealthPercent() const;          // +0x14
};

class QueueModule
{
public:
	HELP_SLOTS16(a)
	virtual void b0();
	virtual int getQueueState();                     // +0x44
};

class Rva00395F57
{
public:
	bool canUnpack(bool force);
};

class Rva0039718B
{
public:
	int rva003970E7(Player *player);
};

class CastleBehavior
{
public:
	static NameKeyType rva0003955DA();
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void *rva0028BD17() const;
	bool rva0028D491() const;
	void *rva0028BC58(int which);
	bool rva00290D2B(const UpgradeTemplate *upgrade) const;
	bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
	protected:
 Module *findModule(NameKeyType key) const;
public:
 __forceinline Module *helpFindModule(NameKeyType key) const { return findModule(key); }

	char m_pad000[0x254];
	BodyModule *m_body;             // +0x254
};

class ProductionPrerequisite
{
public:
	UnicodeString getRequiresList(const Player *player) const;

	char m_data[0x24];
};

class Rva0033AC7F
{
public:
	bool rva0033AC7F(StringBase<unsigned short> &out);
	bool rva0033ACA2(StringBase<unsigned short> &out);
	bool rva0033ACC5(AsciiString &out);
};

class ThingTemplate
{
public:
	int getPrereqCount() const {return m_prereqInfo.size();}
 const ProductionPrerequisite *getNthPrereq(int i) const {return &m_prereqInfo[i];}
 int rva0033A69A(const Player *player, int obj, int which) const;

	char m_pad000[0x30];
	UnicodeString m_displayName;    // +0x30
	char m_pad034[0x11B - 0x34];
	unsigned char m_flags11B;       // +0x11B
	char m_pad11C[0x324 - 0x11C];
	_STL::vector<ProductionPrerequisite> m_prereqInfo;
	char m_pad330[0x618-0x330];
	int m_buildPoints;              // +0x618
};

class UnitRevivalEntry
{
public:
	void *getThingTemplate();

	char m_pad00[0x0C];
	int m_rank;                     // +0x0C
	char m_pad10[0xA0 - 0x10];
	bool m_isRevive;                // +0xA0
};

class Rva0037E421
{
public:
	void *rva0037E421(int index);
};

class Rva0037E6E8
{
public:
	int rva0037E649(int index, Object *obj);
};

class Rva0029FCB4
{
public:
	_STL::vector<ScienceType> rva0029FCB4();
};

class CommandButton
{
public:
	const ThingTemplate *rva0035B570() const;
	const AsciiString &rva0035B26F() const;
	const AsciiString &rva0035B1E9() const;

	char m_pad00[0x14];
	int m_commandType;              // +0x14
	char m_pad18[4];
	unsigned int m_options;         // +0x1C
	char m_pad20[4];
	const UpgradeTemplate *m_upgrade; // +0x24
	UpgradeRange m_requiredUpgrades;  // +0x28
	char m_pad30[4];
	bool m_requireAll;              // +0x34
	char m_pad35[0x44 - 0x35];
	Rva0029FCB4 *m_createAHero;     // +0x44
	char m_pad48[0x70 - 0x48];
	AsciiString m_alreadyUpgradedLabel;   // +0x70
	AsciiString m_conflictingLabel;       // +0x74
	AsciiString m_lacksPrereqLabel;       // +0x78
	char m_pad7C[0xA4 - 0x7C];
	_STL::vector<ScienceType> m_sciences; // +0xA4
	char m_padB0[0xC0 - 0xB0];
	int m_revivalIndex;             // +0xC0
};

class Rva0056D3FD
{
public:
	Rva0056D3FD(const UnicodeString &title, const UnicodeString &cost, const UnicodeString &time, const UnicodeString &description, const AsciiString &extra);

	char m_data[12];
};

bool rva00405B0A(const AsciiString &label, const Player *player, const ThingTemplate *thing, UnicodeString *out);

class OldSchoolHelpBoxContentSource
{
public:
	virtual ~OldSchoolHelpBoxContentSource();
	virtual void s1();
	virtual void s2();
	virtual TreeHintRef00217D4C createContent();

	bool allRequiredUpgradesComplete(Object *obj, UpgradeRange *range, bool requireAll);

	char m_pad04[8];
	CommandButton *m_commandButton; // +0x0C
};

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
TreeHintRef00217D4C OldSchoolHelpBoxContentSource::createContent()
{
	UnicodeString title;
	UnicodeString cost;
	UnicodeString time;
	UnicodeString description;

	Drawable *draw = TheInGameUI->getFirstSelectedDrawable();
	Object *obj = draw ? draw->getObject() : 0;
	Player *localPlayer = (Player *)((BfmeThingRV *)ThePlayerList)->bfmePickRV();
	Player *player = obj ? obj->getControllingPlayer() : localPlayer;

	UnicodeString requiresList = UnicodeString::TheEmptyString;
	UnicodeString requiresString;
	bool firstRequirement = true;
	bool scienceLocked = false;

	if (m_commandButton)
	{
		const ThingTemplate *thing = m_commandButton->rva0035B570();
		ScienceType science = SCIENCE_INVALID;
		const UpgradeTemplate *upgrade = m_commandButton->m_upgrade;

		if ((unsigned)(m_commandButton->m_sciences.end() - m_commandButton->m_sciences.begin()) > 1)
		{
			int i = 0;
			if ((unsigned)(m_commandButton->m_sciences.end() - m_commandButton->m_sciences.begin()) > 0u)
			do
			{
				science = m_commandButton->m_sciences[i];
				if (m_commandButton->m_commandType != 0x19)
				{
					if (player && !player->hasScience(science) && i > 0)
						science = m_commandButton->m_sciences[i - 1];
					scienceLocked = true;
					break;
				}
				if (player && !player->hasScience(science))
					break;
				++i;
			} while (i < m_commandButton->m_sciences.size());
		}
		else if ((unsigned)(m_commandButton->m_sciences.end() - m_commandButton->m_sciences.begin()) == 1)
		{
			science = m_commandButton->m_sciences[0];
		}

		int type = m_commandButton->m_commandType;
		bool isUnitBuild = type == 6 || type == 7 || type == 8;

		if ((type == 0x33 || type == 0x3B) && obj)
		{
			ProductionInterface *production = (ProductionInterface *)obj->rva0028BD17();
			if (production)
			{
				float costValue = (type == 0x3B) ? production->getCost2(player) : production->getCost1(player);
				bool fullHealth = obj->m_body->getHealthPercent() == 1.0f;
				bool notBusy = !obj->rva0028D491();
				if (notBusy)
				{
					if (!fullHealth)
						cost.format(TheGameText->fetchPtrC("TOOLTIP:Cost", 0), (int)costValue);
				}
				else if (obj->m_body->getHealthPercent() == 0.0f)
				{
					cost.format(TheGameText->fetchPtrC("TOOLTIP:Cost", 0), (int)costValue);
				}
			}
		}

		description.clear();

		Rva0029FCB4 *hero;
		bool requireAll;Player *payer;
 if (localPlayer && m_commandButton->m_commandType == 0x26 && (hero=m_commandButton->m_createAHero))
		{
			_STL::vector<ScienceType> sciences = hero->rva0029FCB4();
			if (sciences.begin()!=sciences.end()) {
_ReadWriteBarrier();
			ScienceType heroScience = SCIENCE_INVALID;
			_STL::vector<ScienceType>::iterator it = sciences.begin();
			do
			{
				if (localPlayer->hasScience(*it))
				{
					heroScience = *it;
					break;
				}
				++it;
			} while (it != sciences.end());
			if (heroScience != SCIENCE_INVALID)
			{
				if (localPlayer->rva002AB82D((CreateAHeroData *)heroScience)
					|| localPlayer->rva002AB855((CreateAHeroData *)heroScience)
					|| !TheScienceStore->playerHasRootPrereqsForScience((const Player *)((char *)localPlayer + 4), heroScience))
				{
					description = TheGameText->fetchC("TOOLTIP:ScienceDisabled", 0);
				}
			}
			}
		}

		if (UnicodeView::isEmpty(description) && !m_commandButton->rva0035B26F().isEmpty())
		{
			description = TheGameText->fetchA(m_commandButton->rva0035B26F(), 0);
			if (obj && upgrade && !player->rva002AA8EF(upgrade) && isUnitBuild)
			{
				QueueModule *queue = (QueueModule *)obj->rva0028BC58(0);
				if (queue && queue->getQueueState() == 0x14)
				{
					description.concat(L"\n\n");
					description.concat(TheGameText->fetchC("TOOLTIP:TooltipCannotPurchaseBecauseQueueFull", 0));
				}
				else if (payer = ThePlayerList->m_local, !TheUpgradeCenter->rva0026F11A(payer, upgrade, obj, false))
				{
					description.concat(L"\n\n");
					description.concat(TheGameText->fetchC("TOOLTIP:TooltipNotEnoughMoneyToBuild", 0));
				}
			}
		}

		title = TheGameText->fetchC(m_commandButton->rva0035B1E9().str(), 0);

		if (thing && !(upgrade && isUnitBuild) && m_commandButton->m_commandType != 0x19 && m_commandButton->m_commandType != 0x34)
		{
			int buildCost = (thing->m_flags11B & 0x20) ? 0 : thing->rva0033A69A(player, (int)obj, -1);
			if (buildCost <= 0)
				cost = TheGameText->fetchC("TOOLTIP:CostFree", 0);
			else
				cost.format(TheGameText->fetchPtrC("TOOLTIP:Cost", 0), buildCost);

			int buildPoints = thing->m_buildPoints;
			if (buildPoints > 0)
				time.format(TheGameText->fetchPtrC("TOOLTIP:CommandPoints", 0), buildPoints);

			for (int p = 0; p < thing->getPrereqCount(); ++p)
			{
				const ProductionPrerequisite *prereq;prereq = thing->getNthPrereq(p);
 requiresString = prereq->getRequiresList(player);
				if (requiresString.compare(UnicodeString::TheEmptyString) != 0)
				{
					if (firstRequirement)
						firstRequirement = false;
					else
						requiresList.concat(L", ");
				}
				requiresList.concat(requiresString);
			}

			if (!UnicodeView::isEmpty(requiresList))
			{
				UnicodeString requiresFormat = TheGameText->fetchC("CONTROLBAR:Requirements", 0);
				requiresList.format(requiresFormat.str(), requiresList.str());
				if (!UnicodeView::isEmpty(description))
					description.concat(L"\n");
				description.concat(requiresList);
			}

			if (localPlayer && !localPlayer->allowedToBuild(thing))
			{
				if (!UnicodeView::isEmpty(description))
					description.concat(L"\n");
				description.concat(TheGameText->fetchC("TOOLTIP:BuildDisabled", 0));
			}
		}
		else if (upgrade)
		{
			int upgradeType = m_commandButton->m_commandType;
			bool isType6 = upgradeType == 6;
			bool isType7 = upgradeType == 7;
			bool isType8 = upgradeType == 8;
			bool hasUpgrade = player->rva002AB87D(upgrade);
			bool canUpgrade = false;
			bool lacksPrereq = false;

			if (!hasUpgrade && obj)
			{
				if ((m_commandButton->m_options & 0x40) && !obj->rva00290D2B(upgrade)
					&& !allRequiredUpgradesComplete(obj, &m_commandButton->m_requiredUpgrades, (requireAll = m_commandButton->m_requireAll)))
				{
					lacksPrereq = true;
				}
				else if (TheInGameUI->getSelectCount() == 1)
				{
					hasUpgrade = obj->rva00290D2B(upgrade);
					if (isType7)
						canUpgrade = !obj->affectedByUpgrade(upgrade);
				}
				else
				{
					hasUpgrade = true;
					canUpgrade = true;
					const DrawableList *selected = TheInGameUI->getAllSelectedDrawables();
					for (DrawableNode *node = selected->m_node->next; node != selected->m_node; node = node->next)
					{
						Drawable *selDraw = node->data;
						if (selDraw)
						{
							Object *selObj = selDraw->getObject();
							if (selObj)
							{
								hasUpgrade = hasUpgrade && selObj->rva00290D2B(upgrade);
								canUpgrade = canUpgrade && !selObj->affectedByUpgrade(upgrade);
							}
						}
						if (!hasUpgrade && !canUpgrade)
							break;
					}
				}
			}

			if (lacksPrereq)
			{
				if (!m_commandButton->m_lacksPrereqLabel.isEmpty())
					description = TheGameText->fetchA(m_commandButton->m_lacksPrereqLabel, 0);
				else
					description = TheGameText->fetchC("TOOLTIP:LacksPrerequisiteUpgradeDefault", 0);
			}
			else if (canUpgrade && !hasUpgrade)
			{
				if (!m_commandButton->m_conflictingLabel.isEmpty())
					description = TheGameText->fetchA(m_commandButton->m_conflictingLabel, 0);
				else
					description = TheGameText->fetchC("TOOLTIP:HasConflictingUpgradeDefault", 0);
			}
			else if (hasUpgrade && (isType6 || isType7 || isType8))
			{
				if (!m_commandButton->m_alreadyUpgradedLabel.isEmpty())
					description = TheGameText->fetchA(m_commandButton->m_alreadyUpgradedLabel, 0);
				else
					description = TheGameText->fetchC("TOOLTIP:AlreadyUpgradedDefault", 0);
			}

			if (!hasUpgrade)
			{
				int upgradeCost = upgrade->rva0026EF50(player, obj);
				if (upgradeCost > 0)
					cost.format(TheGameText->fetchPtrC("TOOLTIP:Cost", 0), upgradeCost);
			}
		}
		else if (science != SCIENCE_INVALID && !scienceLocked)
		{
			cost.format(TheGameText->fetchPtrC("TOOLTIP:ScienceCost", 0), TheScienceStore->getSciencePurchaseCost(science));
		}
		else if (m_commandButton->m_commandType == 0x2E)
		{
			int index = m_commandButton->m_revivalIndex;
			Rva0037E421 *revival = (Rva0037E421 *)((char *)player + 0x738);
			UnitRevivalEntry *entry = (UnitRevivalEntry *)revival->rva0037E421(index);
			const ThingTemplate *revivalThing = entry ? (const ThingTemplate *)entry->getThingTemplate() : 0;
			if (entry && revivalThing)
			{
				AsciiString label;
				if (entry->m_isRevive)
				{
					label = "CONTROLBAR:GenericReviveHero";
					if (!((Rva0033AC7F *)revivalThing)->rva0033AC7F(description))
						description = TheGameText->fetchC("CONTROLBAR:ToolTipGenericReviveHero", 0);
				}
				else
				{
					label = "CONTROLBAR:GenericRecruitHero";
					if (!((Rva0033AC7F *)revivalThing)->rva0033ACA2(description))
						description = TheGameText->fetchC("CONTROLBAR:ToolTipGenericRecruitHero", 0);
				}

				if (!rva00405B0A(label, player, revivalThing, &title))
				{
					AsciiString nameLabel;
					if (((Rva0033AC7F *)revivalThing)->rva0033ACC5(nameLabel))
						title.format(TheGameText->fetchPtrA(label, 0), TheGameText->fetchA(nameLabel, 0).str());
					else
						title.format(TheGameText->fetchPtrA(label, 0), revivalThing->m_displayName.str());
				}

				description.concat(L"\n");
				UnicodeString rank;
				rank.format(TheGameText->fetchPtrC("APT:RankLabel", 0), entry->m_rank);
				description.concat(rank);

				cost.format(TheGameText->fetchPtrC("TOOLTIP:Cost", 0), ((Rva0037E6E8 *)revival)->rva0037E649(index, obj));

				int buildPoints = revivalThing->m_buildPoints;
				if (buildPoints > 0)
					time.format(TheGameText->fetchPtrC("TOOLTIP:CommandPoints", 0), buildPoints);
			}
		}
		else if (m_commandButton->m_commandType == 0x21 && obj)
		{
			Module *castle = obj->helpFindModule(CastleBehavior::rva0003955DA());
			if (castle && ((Rva00395F57 *)castle)->canUnpack(false))
				cost.format(TheGameText->fetchPtrC("TOOLTIP:Cost", 0), ((Rva0039718B *)castle)->rva003970E7(player));
		}
	}

	AsciiString extra;
	if (theRadarWindowOverrideSource)
		extra = *(const AsciiString *)((Rva002D371DAddImm32Field *)theRadarWindowOverrideSource)->get();

	TreeHintRef00217D4C help((TargetRef00217D4C *)new Rva0056D3FD(
		title, cost, time, description, extra));
	return static_cast<const TreeHintRef00217D4C &>(help);
}

bool OldSchoolHelpBoxContentSource::allRequiredUpgradesComplete(Object *obj, UpgradeRange *range, bool flag)
{
	for (unsigned int i = 0; i < (unsigned int)(range->m_end - range->m_begin); ++i)
	{
		UpgradeTemplate *tmpl = range->m_begin[i];
		if (!tmpl)
			continue;
		int v = tmpl->m_4;
		bool r;
		if (v == 1)
			r = obj->rva00290D2B(tmpl);
		else if (v == 0)
			r = obj->getControllingPlayer()->rva002AB87D(tmpl);
		else
			return false;
		if (flag)
		{
			if (r)
				return true;
		}
		else
		{
			if (!r)
				return false;
		}
	}
	return flag == 0;
}
