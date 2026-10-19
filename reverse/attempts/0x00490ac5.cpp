// ?rva00490AC5@ArrowStormUpdate@@QAEXXZ
// partial score=0.985 date=2026-10-19
// ?rva00490AC5@ArrowStormUpdate@@QAEXXZ
// partial score=0.9787234042553191 date=2026-10-19
// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /G7 /I.
// 0x00490AC5 bank 2026-10-19 (claude-opus-5-5): hack-free 470/470, 7 differing bytes, all frame offsets
// (module-data spill -0x20 vs retail -0x1c, ID slot -0x1c vs -0x20); the old bank had 10 bytes and six
// equal-arm ternaries. Levers: BitFlags<218> m_kindof with forceinline test/isKindOf returning unsigned
// long (a bool return breaks codegen); WB twin 0x11DD160 order (Object *obj before data) and tail shape.
// Retail uses two separate ID temporaries (WB local_64/local_68) that share one slot; ours only shares
// them in straight-line code. Lead: the two lists are different real STLport types (the +0x88 list's
// push_back is out of line at 0x2A1B6F, the local list inlines insert(end(),x) -> 0x2A1316).
// Home: new Code/GameEngine/Source/GameLogic/Object/Update/ArrowStormUpdate.cpp. Scratch: build/nbr/r4/490ac5/.
// stlport
// Notes kept from the earlier banks of this body:
// W9-O3 2026-10-16: both list calls now resolve: push_back -> the pinned BridgeBehaviorObjectIDList::push_back (0x2A1B6F) view, the inline insert -> the pinned private Rva002A1B6FNativeList::insert (0x2A1316, member/aggregate-result ABI) through a friend view (no alternatename). Size exact nd 19: (1) three 4-byte frame homes rotated (retail data -0x1c, extra -0x18, id temp -0x20; ours -0x20/-0x1c/-0x18); (2) size() walks keep head in ECX/cursor EAX where retail has EAX/ECX. Inert/worse: p != m_node, first/last distance forms, iterator pair.
// ArrowStormUpdate's target gathering 0x00490AC5, tail-called by its slot-15
// override 0x00490D0A after the +0x88 list is reset (ArrowStormUpdateSlots.cpp).
// Every alive object other than this one that 0x00260EB1 accepts with flags
// 1 within the module data's +0xCC radius of the +0x44 target point (BFME2's
// partition filter chain, the view AIStructureCreepTactic.cpp documents) and
// whose template has none of the tested KindOf bits goes into the +0x88
// list, and also into a local list when its template has +0x109 bit 2. A
// non-empty +0x88 list short of the data's +0xD8 count is then topped up by
// cycling through the local list (or through itself when the local list is
// empty).
#include <list>

class Object;

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

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00BFBC90, allow 0x00260EB1: +0x08 the object, +0x0C flags,
// +0x10 whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};


#include "Code/Libraries/Include/Lib/Coord3D.h"

#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

enum ObjectID
{
	INVALID_ID = 0
};

template<int NUMBITS> class BitFlags
{
public:
	unsigned long m_words[(NUMBITS + 31) / 32];
	__forceinline unsigned long test(unsigned pos) const { return m_words[pos / 32] & (1UL << (pos % 32)); }
};

class ThingTemplate
{
public:
	char m_pad000[0x108];
	BitFlags<218> m_kindof;	// +0x108
	__forceinline unsigned long isKindOf(unsigned t) const { return m_kindof.test(t); }
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	const ThingTemplate *getTemplate() const { return m_template; }
	char m_pad000[0x04];
	const ThingTemplate *m_template;	// +0x04
	char m_pad008[0x74 - 0x08];
	ObjectID m_id;		// +0x74
};

// STLport list<ObjectID>: nodes +0 next, +4 previous, +8 the ID.
struct Rva0029FB3BNode
{
	Rva0029FB3BNode *m_next;
	Rva0029FB3BNode *m_previous;
	ObjectID m_value;
};

struct Rva0029FB3BAlloc
{
	Rva0029FB3BAlloc() {}
	~Rva0029FB3BAlloc() {}
};

struct Rva0029FB3BIter
{
	Rva0029FB3BIter(Rva0029FB3BNode *node) : m_node(node) {}
	Rva0029FB3BIter(const Rva0029FB3BIter &that) : m_node(that.m_node) {}
	Rva0029FB3BNode *m_node;
};

struct Rva002A1316Iterator
{
	explicit Rva002A1316Iterator(void *p) : node(p) {}
	Rva002A1316Iterator(const Rva002A1316Iterator &other) : node(other.node) {}
	void *node;
};
class BridgeBehaviorObjectIDList
{
public:
	void push_back(const ObjectID &id);	// 0x002A1B6F
};
class Rva0029FB3BMember;
class Rva002A1B6FNativeList
{
	friend class Rva0029FB3BMember;
	Rva002A1316Iterator insert(Rva002A1316Iterator pos, void *const &value);	// 0x002A1316
};

class Rva0029FB3BMember
{
public:
	Rva0029FB3BMember(const Rva0029FB3BAlloc &alloc = Rva0029FB3BAlloc());	// 0x0029FB3B
	~Rva0029FB3BMember() throw();	// 0x00268902
	bool empty() const { return m_node->m_next == m_node; }
	unsigned size() const
	{
		return ((_STL::list<ObjectID> const *)this)->size();
	}
	Rva0029FB3BIter end() { return Rva0029FB3BIter(m_node); }
	__forceinline void push_back(const ObjectID &id) { ((BridgeBehaviorObjectIDList *)this)->push_back(id); }
	__forceinline void pushBackInline(const ObjectID &id) { ((Rva002A1B6FNativeList *)this)->insert(Rva002A1316Iterator(m_node), *(void *const *)&id); }
	void reset();	// 0x0026549E
	Rva0029FB3BNode *m_node;
};

struct ArrowStormUpdateModuleData
{
	unsigned char m_pad00[0xCC];
	float m_CC;		// +0xCC the radius
	unsigned char m_padD0[0xD8 - 0xD0];
	unsigned m_D8;		// +0xD8 the count
};

class ModuleData;
class SpecialAbilityUpdate
{
public:
	virtual ~SpecialAbilityUpdate();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x44 - 0x0C];
	Coord3D m_44;	// +0x44 the target point
	unsigned char m_pad50[0x88 - 0x50];
};

class ArrowStormUpdate : public SpecialAbilityUpdate
{
public:
	void rva00490AC5();
private:
	Rva0029FB3BMember m_88;	// +0x88
};

void ArrowStormUpdate::rva00490AC5()
{
	Object *obj = m_object;
	const ArrowStormUpdateModuleData *data = (const ArrowStormUpdateModuleData *)m_moduleData;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&m_44, data->m_CC, 0,
		Rva00260EB1Filter(obj, 1, false).link(Rva0026119DFilter().link(&Rva002611BFFilter(obj))), 1);
	Rva0029FB3BMember extra;
	Object *other;
	while ((other = hits.next()) != 0) {
		if (other->getTemplate()->isKindOf(104) || other->getTemplate()->isKindOf(89)
				|| other->getTemplate()->isKindOf(47) || other->getTemplate()->isKindOf(150)
				|| other->getTemplate()->isKindOf(54) || other->getTemplate()->isKindOf(134))
			continue;
		ObjectID id = other->getID();
		m_88.push_back(id);
		if (other->getTemplate()->isKindOf(10)) {
			id = other->getID();
			extra.pushBackInline(id);
		}
	}
	if (m_88.size() == 0)
		return;
	if (m_88.size() < data->m_D8) {
		Rva0029FB3BMember *source = &m_88;
		if (!extra.empty())
			source = &extra;
		Rva0029FB3BNode *it = source->m_node->m_next;
		while (m_88.size() < data->m_D8) {
			m_88.push_back(it->m_value);
			it = it->m_next;
			if (it == source->m_node)
				it = source->m_node->m_next;
		}
	}
	extra.reset();
}
