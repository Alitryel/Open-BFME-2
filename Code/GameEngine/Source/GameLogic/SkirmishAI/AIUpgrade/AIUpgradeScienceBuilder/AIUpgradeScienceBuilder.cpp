// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
//
// AIUpgradeScienceBuilder.cpp (the unit its random-value asserts name; the
// constructor tables establish both callback interfaces).
//
//   0x00597E30  at most once per g_00E063CC frames and while the AI manager's
//               record for the owner (0x002A8AB1) has +0x16C >= 1: pick a
//               random entry; unless already done (+0x2C) or owned (slot
//               16), build it (slot 6) when an object of kind 3 or 90 the
//               owner's relationship flag 4 accepts is alive within 400 of
//               the entry's slot-13 position (BFME2's partition filter
//               chain, the view AIStructureCreepTactic.cpp documents)
//   0x00597C58  Register (WB 01532AD0, asserts at lines 73..104): an object
//               whose +0x280 is negative contributes, per command button of
//               its command set, an upgrade record (cost, ID, button, name,
//               heuristic) or, for a science-build button whose template
//               lacks flags 0x11B&0x10 and 0x116&0x40, a building record
//               (button, name, position, angle, ID); any other object only
//               its ID. The second argument is one unused stack word.
#include <string.h>
#include "ascii_string.h"

class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00C004D8, allow 0x00261409: the player's relationship to the
// object's team against the +0x10 flags, +0x0C whether a hit allows.
class Rva00261409Filter : public Rva000421C8
{
public:
	Rva00261409Filter(Player *player, bool match, int flags)
		: m_player(player), m_match(match), m_flags(flags) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	Player *m_player;
	bool m_match;
	int m_flags;
};

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00C1A25C: any of the mask's kinds.
class Rva003959FA : public Rva000421C8
{
public:
	Rva003959FA(const BfmeFixedStorage0004543D &mask);	// 0x003959FA
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

// A KindOfMaskType view: 224 bits, zeroed then set bit by bit.
struct Rva00597E30Mask
{
	Rva00597E30Mask() { memset(this, 0, sizeof(*this)); }
	void set(int bit) { m_bits[bit >> 5] |= 1u << (bit & 31); }
	unsigned int m_bits[7];
};

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

#include "../../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);	// 0x00233FF4

struct Rva002A8AB1Record
{
	char m_pad00[0x16C];
	int get16C() const { return m_16C; }
	int m_16C;		// +0x16C
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);	// 0x002A8AB1
};
extern Rva002A8F24 *TheSkirmishAIManager;

extern unsigned g_00E063CC;	// frames between attempts

// One upgrade or science to build: slot 6 builds it, slot 13 is where,
// slot 16 whether the owner already has it, +0x2C whether it was done.
class Rva00597E30Entry
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void rva00597E30Slot6(Player *owner, int arg);
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual Coord3D rva00597E30Slot13();
	virtual void slot14();
	virtual void slot15();
	virtual int rva00597E30Slot16(Player *owner);
	char m_pad04[0x2C - 0x04];
	bool m_2C;		// +0x2C
};

// Register's views. Offsets come from native 00597C58..00597E30 and the rowed
// record constructors 0x005970ED and 0x005DAA71; the record class names are
// address names, their original types unresolved.
class Object
{
public:
	const AsciiString *rva00290E67() const;	// 0x00290E67
	char m_pad00[0x38];
	Coord3D m_position;	// +0x38
	float m_angle;		// +0x44
	char m_pad48[0x74 - 0x48];
	unsigned m_id;		// +0x74
	char m_pad78[0x280 - 0x78];
	float m_280;		// +0x280
	float get280() const { return m_280; }
};

class UpgradeTemplate
{
public:
	unsigned calcCostToBuild(Player *owner, unsigned object) const;	// 0x0026EF50 the cost
	char m_pad00[8];
	AsciiString m_name;	// +0x08
	char m_pad0C[0x98 - 0x0C];
	int m_heuristic;	// +0x98
};

class ThingTemplate;
class CommandButton
{
public:
	const ThingTemplate *rva0035B570() const;	// 0x0035B570
	char m_pad00[0x14];
	int m_command;		// +0x14
	char m_pad18[0x24 - 0x18];
	UpgradeTemplate *m_upgrade;	// +0x24
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;
};

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *name);	// 0x0031D5F8 the command set
};
class ControlBar;
extern ControlBar *TheControlBar;

// The ThingTemplate fields Register reads.
struct ScienceBuildTemplateView
{
	char m_pad00[0x64];
	AsciiString m_name;	// +0x64
	char m_pad68[0x116 - 0x68];
	unsigned char m_116;	// +0x116
	char m_pad117[0x11B - 0x117];
	unsigned char m_11B;	// +0x11B
};

class Rva0055B0CC
{
public:
	virtual ~Rva0055B0CC();
	float m_delay;		// +0x04
	unsigned m_id;		// +0x08
	AsciiString m_name;	// +0x0C
	char m_pad10[0x21 - 0x10];
	bool m_registered;	// +0x21
	char m_pad22[0x2C - 0x22];
};

class AIUpgrade : public Rva0055B0CC
{
public:
	void rva005975C0();
	unsigned m_cost;			// +0x2C
	const CommandButton *m_command;	// +0x30
};

class Rva005970ED : public AIUpgrade
{
public:
	Rva005970ED();				// 0x005970ED
	void rva0059717F(int heuristic);	// 0x0059717F
	char m_pad34[0x44 - 0x34];
};

class Rva005DAAB6 : public Rva0055B0CC
{
public:
	Rva005DAAB6();				// 0x005DAA71
	bool m_used;				// +0x2C
	Coord3D m_position;			// +0x30
	float m_angle;				// +0x3C
	const CommandButton *m_command;	// +0x40
};

// ScienceType preserves the existing generic 4-byte vector provider ABI only;
// this vector stores the object identifier field and does not establish
// ScienceType semantics. The record vectors call the folded 4-byte append
// (0x004DFCB0) through two of its existing storage views, ModuleData pointers
// and longs: retail's two calls name distinct instantiations (one view would
// let the compiler merge the calls), and no record is a ModuleData or long.
enum ScienceType
{
	SCIENCE_DUMMY = 0
};
class ModuleData;
namespace _STL
{
	template<class T> class allocator
	{
	};
	template<class T, class A = allocator<T> > class vector
	{
	public:
		void push_back(const T &value);
		T *m_begin, *m_end, *m_limit;
	};
}

class Object;
class BaseA
{
public:
    virtual void Register(Object *, void *) = 0;
    virtual void UnRegister(Object *) = 0;
    virtual ~BaseA();
    int m_04;
    int m_08;
};

class Rva00506B1B
{
public:
    virtual ~Rva00506B1B();
    virtual void rva00597fc5() = 0;
    virtual void shutdown() = 0;
    bool m_04;
};

class AIUpgradeScienceBuilder : public BaseA, public Rva00506B1B
{
public:
    virtual void Register(Object *, void *);
    virtual void UnRegister(Object *);
    virtual ~AIUpgradeScienceBuilder();
    virtual void rva00597fc5();
    virtual void shutdown();
	bool rva0059764A(Object *object);	// 0x0059764A
	void buildExpansionUpgrades();
private:
	Player *m_14;			// +0x14 the owner
	_STL::vector<ScienceType> m_objects;	// +0x18
	_STL::vector<const ModuleData *> m_upgrades;	// +0x24
	Rva00597E30Entry **m_30;	// +0x30 the entries
	Rva00597E30Entry **m_34;	// +0x34 their end
	char m_pad38[0x3C - 0x38];
	unsigned m_3C;			// +0x3C the last frame
};

void AIUpgradeScienceBuilder::Register(Object *object, void *)
{
	if (rva0059764A(object))
		return;
	CommandSet *commands = (CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8(object->rva00290E67());
	if (object->get280() < 0.0f) {
		if (commands) for (int i = 0; i < 32; ++i) {
			const CommandButton *button = commands->getCommandButton(i);
			if (!button)
				continue;
			UpgradeTemplate *upgrade = button->m_upgrade;
			if (upgrade) {
				unsigned cost = upgrade->calcCostToBuild(m_14, (unsigned)object);
				Rva005970ED *record = new Rva005970ED;
				// Opening the item's scope before the cost store puts it in
				// the new-expression's frame slot, as retail does.
				{
					AIUpgrade *item = record;
					record->m_cost = cost;
					record->m_id = object->m_id;
					record->m_command = button;
					// The folded conditional reproduces retail's register
					// assignment and argument order.
					// Native copy calls use the rowed StringBase<char> worker366F0.
					record->m_name.setCopyInline(i ? upgrade->m_name : upgrade->m_name);
					record->rva0059717F(upgrade->m_heuristic);
					m_upgrades.push_back(reinterpret_cast<const ModuleData *const &>(item));
				}
			} else if (button->m_command == 1 && button->rva0035B570() &&
				!(((const ScienceBuildTemplateView *)button->rva0035B570())->m_11B & 0x10) &&
				!(((const ScienceBuildTemplateView *)button->rva0035B570())->m_116 & 0x40)) {
				Rva005DAAB6 *record = new Rva005DAAB6;
				{
					Rva0055B0CC *item = record;
					record->m_command = button;
					record->m_name.setCopyInline(((const ScienceBuildTemplateView *)button->rva0035B570())->m_name);
					record->m_delay = -1.0f;
					record->m_position = object->m_position;
					*(unsigned *)&record->m_angle = *(const unsigned *)&object->m_angle;
					record->m_id = object->m_id;
					record->m_registered = true;
					reinterpret_cast<_STL::vector<long> *>(&m_30)->push_back(
						reinterpret_cast<const long &>(item));
				}
			}
		}
	} else {
		unsigned id = object->m_id;
		m_objects.push_back((const ScienceType &)id);
	}
}

void AIUpgradeScienceBuilder::buildExpansionUpgrades()
{
	if (m_30 == m_34)
		return;
	if (TheGameLogic->getFrame() - m_3C < g_00E063CC)
		return;
	if (TheSkirmishAIManager->rva002A8AB1(m_14)->get16C() < 1)
		return;
	Rva00597E30Entry *entry = m_30[GetGameLogicRandomValue(0, (m_34 - m_30) - 1,
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIUpgrade\\AIUpgradeScienceBuilder\\AIUpgradeScienceBuilder.cpp", 0x1A1)];
	if (!entry || entry->m_2C)
		return;
	if (entry->rva00597E30Slot16(m_14))
		return;
	Rva00597E30Mask mask;
	mask.set(3);
	mask.set(90);
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&entry->rva00597E30Slot13(), 400.0f, 0,
		Rva0026119DFilter().link(&Rva00261409Filter(m_14, true, 4))->link(&Rva003959FA(*(BfmeFixedStorage0004543D *)&mask)), 0);
	if (hits.next()) {
		entry->rva00597E30Slot6(m_14, 0);
		entry->m_2C = true;
		m_3C = TheGameLogic->getFrame();
	}
}

// Address-derived range-30 body at 0x00597FC5 (66 bytes). Target bytes pass
// this-0x0C to the rowed 0x005977D3, 0x0059781D, and
// AIUpgradeScienceBuilder::buildExpansionUpgrades at 0x00597E30. They then
// walk the begin/end pair at this+0x18/+0x1C and call 0x005975C0 for entries
// whose byte at +0x34 is set. The 0x00597983 callee has a string-xref lead
// into this file, but its identity remains unknown.
class Rva005977D3
{
public:
	void rva005977D3();
};

class Rva0059781D
{
public:
	void rva0059781D();
};

class Rva00597983
{
public:
	void rva00597983();
};

class Rva005975C0
{
public:
	unsigned char m_pad00[0x34];
	bool m_34;
};

void AIUpgradeScienceBuilder::rva00597fc5()
{
	AIUpgradeScienceBuilder *subobject = this;
	reinterpret_cast<Rva005977D3 *>(subobject)->rva005977D3();
	reinterpret_cast<Rva0059781D *>(subobject)->rva0059781D();
	reinterpret_cast<Rva00597983 *>(subobject)->rva00597983();
	reinterpret_cast<AIUpgradeScienceBuilder *>(subobject)->buildExpansionUpgrades();

	const ModuleData **end = m_upgrades.m_end;
	const ModuleData **it = m_upgrades.m_begin;
	while (it != end)
	{
		Rva005975C0 *entry = reinterpret_cast<Rva005975C0 *>(const_cast<ModuleData *>(*it));
		if (entry->m_34)
			reinterpret_cast<AIUpgrade *>(entry)->rva005975C0();
		++it;
	}
}
