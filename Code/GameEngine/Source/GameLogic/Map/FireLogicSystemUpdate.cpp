// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include
// stlport
//
// FireLogicSystem::update (0x00287FAD, vtable 0x00BFB7BC slot 10;
// WorldBuilder's Map/FireLogicSystem.cpp body at WB 0x00C36B60, asserts at
// lines 404..546). It burns a tenth of the grid's rows a frame: a burning
// cell consumes fuel, credits each object id in the cell through
// TheTerrainLogic (0x0027F09F) and leaves m_cellsOnFire once it falls back
// under its flammability; the objects watching a burning cell take fire
// damage; burnt cells regrow fuel from their terrain material; heat spreads
// to the four neighbours through the static pending list (push_back
// 0x00287F76); and every tenth frame each burning key ticks (0x002856CF).
//
// Target facts: the layout and helper views are the ones
// FireLogicSystemObjects.cpp matches (cells at +0x70, counts at +0x78/+0x7C,
// m_cellsOnFire at +0x84). This unit needs STLport (the damage map and the
// pending vector), which that /GX unit does not compile with. Codegen: the
// erase keys are named locals and the insert keys temporaries, as in the
// WorldBuilder body; the spread pass reads the set size through an inline
// getter and the tick walk is an inlined for_each, which together give
// retail's register assignment.
#include <map>
#include <vector>
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class ThingTemplate;

// A burning cell's key in m_cellsOnFire: the cell's world-centre
// coordinates (constructed at 0x00285B91, destroyed at 0x00285BEC).
class Rva00285BECBase
{
public:
	virtual ~Rva00285BECBase();
};
class Rva00285BECSnapshotBase
{
public:
	virtual ~Rva00285BECSnapshotBase();
};
class Rva00285BEC : public Rva00285BECBase, public Rva00285BECSnapshotBase
{
public:
	Rva00285BEC(int a, int b);
	virtual ~Rva00285BEC();
	int m_08;
	int m_0C;
	int m_10;
};

// m_cellsOnFire's tree find (0x00286214) and erase (0x002860CF).
class Rva00285672;
struct Rva00286214Node;
struct Rva002860CFIterator
{
	Rva00286214Node *m_node;
	Rva002860CFIterator(Rva00286214Node *node) : m_node(node) {}
	Rva002860CFIterator(const Rva002860CFIterator &that) : m_node(that.m_node) {}
};
class Rva002860CFHost
{
public:
	void rva002860CF(Rva002860CFIterator it);
};
struct Rva00287B2AResult
{
	Rva00287B2AResult(Rva00286214Node *node, bool inserted) : m_node(node), m_inserted(inserted) {}
	Rva00286214Node *m_node;
	bool m_inserted;
};
struct Rva0028688AKey;
struct Rva0028688ANode;
struct Rva00286E33Result { Rva0028688ANode *node; bool inserted; };
struct Rva0028688A { Rva00286E33Result rva00286E33(const Rva0028688AKey &); };
class Rva00286214
{
public:
	Rva00286214Node *rva00286214(const Rva00285672 *key);
	void erase(Rva002860CFIterator pos) { ((Rva002860CFHost *)this)->rva002860CF(pos); }
	Rva00286214();	// the map's default ctor 0x00242F01
	~Rva00286214();	// the tree teardown 0x0028681A
 __declspec(noinline) Rva00287B2AResult rva00287B2A(const Rva00285672 *key);	// insert 0x00287B2A
	Rva00286214Node *m_header;
	unsigned int m_size;	// +0x04
	unsigned int size() const { return m_size; }
	char m_pad08[4];
};


struct FireCellCentre
{
	Int x;
	Int y;
};
class PolygonTrigger;
class ThingTemplate;

// The subsystem base (ctor 0x001B4E63, dtor 0x001B4E74) and Snapshot at
// +0x0C, the second base whose vtable 0x00BBB554 the destructor restores.
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init();
	virtual bool loadIniFilesFromLegend();
	virtual void postProcessLoad();
	virtual bool vslot04(int);
	virtual bool vslot05();
	virtual int vslot06();
	virtual void vslot07(int);
	virtual void vslot08();
	virtual void reset();
	virtual void update();
	virtual bool vslot11(int);
	virtual void vslot12();
	virtual void vslot13(int);

private:
	char m_pad[8];
};
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@URva00287F76Element@@V?$allocator@URva00287F76Element@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00287F76Element;
namespace _STL { template <> void vector<Rva00287F76Element,allocator<Rva00287F76Element> >::_M_insert_overflow(Rva00287F76Element *,Rva00287F76Element const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ?erase@?$vector@UBfmePod8@@V?$allocator@UBfmePod8@@@_STL@@@_STL@@QAEPAUBfmePod8@@PAU3@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod8;
namespace _STL { template <> BfmePod8 * vector<BfmePod8,allocator<BfmePod8> >::erase(BfmePod8 *,BfmePod8 *); }

// A material entry (0x18 bytes): the array constructor zeroes all six
// dwords (0x00286297) and the destructor releases the string at +4
// (0x0029D7C2, folded with CameraMarker's).
struct Rva00286297
{
	Rva00286297();
	~Rva00286297();
	Int unknown00, unknown04;
	Int fuel;
	unsigned int field18, field00, field10;
};

class FireLogicSystem : public SubsystemInterface, public Snapshot
{
public:
	FireLogicSystem();
	virtual ~FireLogicSystem();
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	void ChangeBurnRate(Int x0, Int x1, Int y, Int delta, bool onlyBurning);
	void ChangeBurnRate(const Coord3D *origin, const Coord3D *dir, float threshold, Int x0, Int x1, Int y, Int delta, bool onlyBurning);
	void ChangeBurnRateInArea(const Coord3D *pos, float radius, Int delta, bool onlyBurning);
	void ChangeBurnRateInArea(const Coord3D *pos, float radius, const Coord3D *dir, float threshold, Int delta, bool onlyBurning);
	void rva002872BA(const PolygonTrigger *area, Int delta, bool onlyBurning);
	void ChangeCellToObjectFlammability(Int x, Int y, const ThingTemplate *tmpl);
    void rva0028641F(unsigned int id, const Coord3D *pos);
    void ResetCellToOriginalFlammability(Int x, Int y);
	void rva00286373(Int id, const Coord3D *pos, const ThingTemplate *tmpl);
	void *rva00286D4E(ObjectID id, Int x, Int y, bool add);
	bool rva00286772(const PolygonTrigger *area, Int minBurn);
	void rva00286CC4();
	virtual void update();
private:
	// A cell's watcher list (16-byte nodes from the 0xDFEC94 pool).
	struct WatcherNode
	{
		WatcherNode *m_next;
		Int m_04;
		ObjectID m_id;
		short m_x;
		short m_y;
	};
	struct ObjectNode
	{
		Int m_id;
		ObjectNode *m_next;
	};
	struct Cell
	{
		Int m_type;
		unsigned short m_fuel;
		unsigned short m_check;
		unsigned int m_flammability : 10;
        unsigned int m_field10 : 8;
        unsigned int m_field18 : 12;
        unsigned int m_field30 : 1;
        unsigned int m_field31 : 1;
		WatcherNode *m_0C;
		ObjectNode *m_objects; // +0x10
	};
	typedef Rva00286297 Material;
    Material m_materials[4];	// +0x10
	Cell **m_cells;
	Cell *m_storage;	// +0x74, the rows' shared cell block
	Int m_numRows;
	Int m_numCols;
	Int m_80;
	Rva00286214 m_cellsOnFire;
	Int m_90;
	Int m_94;
	Int m_98;
	void (__cdecl *m_9C)(Int x, Int y);	// a cell's burn state changed
};


class TerrainLogic {
public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual bool isUnderwater(float x, float y, float *waterZ = 0, float *terrainZ = 0, Int unused = 0);	// slot 0x4C
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual unsigned char materialAt(float x, float y);
};
extern TerrainLogic *TheTerrainLogic;

struct Rva00286214Node
{
	char m_pad00[8];
	Rva00286214Node *m_left;		// +0x08
	char m_pad0C[0x18 - 0x0C];
	FireCellCentre m_key;			// +0x18, the cell's centre
};

// The 0x7C-byte damage record uses the rowed Rva00263895Member initializer.
// Object consumes its damage and death types and the per-cell amount.
class Rva00263895Member { public: Rva00263895Member(); };
class DamageInfo
{
public:
	__declspec(dllimport) __forceinline DamageInfo() { ((Rva00263895Member *)this)->Rva00263895Member::Rva00263895Member(); }
	char m_pad00[0x10];
	Int m_10;		// +0x10, damage type
	char m_pad14[0x1C - 0x14];
	Int m_1C;		// +0x1C, death type
	float m_amount;		// +0x20
	char m_pad24[0x7C - 0x24];
};
class Object
{
public:
	bool isSignificantlyAboveTerrain() const;	// 0x0030ADDC
	void attemptDamage(DamageInfo *info);		// 0x0029848E
};
// An object's burn share in a cell (0x0027F09F through TheTerrainLogic) and
// the per-key tick of a burning cell (0x002856CF).
class Rva0027F09F
{
public:
	void rva0027F09F(Int id, Int amount);
};
class Rva002856CFHost
{
public:
	void rva002856CF();
};
typedef _STL::_Rb_tree_iterator<Rva00285BEC, _STL::_Nonconst_traits<Rva00285BEC> > FireTickIt;
typedef _STL::_Rb_tree_node<Rva00285BEC> FireTickNode;
template <class _InputIter, class _Function>
__forceinline _Function fireForEach(_InputIter __first, _InputIter __last, _Function __f) {
  for ( ; __first != __last; ++__first)
    __f(*__first);
  return __f;
}
struct FireTickFn { void operator()(Rva00285BEC &k) const { ((Rva002856CFHost *)&k)->rva002856CF(); } };
// The pending heat of one cell, applied after the spread pass (push_back
// 0x00287F76); the static list itself is the BfmePod8 vector whose clear
// is 0x003FA4DB.
struct BfmePod8 { int a[2]; };

// The set insert (0x00287B2A, rowed in FireLogicSystemObjects.cpp) stays
// visible so the compiler sees it keeps no pointer to the key temporaries;
// hidden, it shifts update's frame by four bytes.
inline Rva00287B2AResult Rva00286214::rva00287B2A(const Rva00285672 *key)
{
	Rva00286E33Result p = ((Rva0028688A *)this)->rva00286E33(*(const Rva0028688AKey *)key);
	return Rva00287B2AResult((Rva00286214Node *)p.node, p.inserted);
}

static inline Rva00287B2AResult insertCell(Rva00286214 &set, const Rva00285BEC &key)
{
	return set.rva00287B2A((const Rva00285672 *)&key);
}
struct Rva00287F76Element
{
	void *m_cell;
	unsigned short m_value;
};

// The rowed placement copy preserves the six live bytes of each eight-byte slot.
void __cdecl Rva002861B0Copy(void *, const void *);
namespace _STL {
template <> __declspec(dllimport) __forceinline void
_Construct<Rva00287F76Element, Rva00287F76Element>(Rva00287F76Element *dest, const Rva00287F76Element &source)
{ Rva002861B0Copy(dest, &source); }
typedef pair<const ObjectID, int> FireDamagePair;
typedef _Rb_tree<ObjectID, FireDamagePair, _Select1st<FireDamagePair>, less<ObjectID>, allocator<FireDamagePair> > FireDamageTree;
template <> pair<FireDamageTree::iterator, bool> FireDamageTree::insert_unique(const FireDamagePair &);
}

// ?update@FireLogicSystem@@UAEXXZ @0x00287FAD
// Burns a tenth of the grid's rows a frame, damages the objects watching a
// burning cell, regrows burnt fuel and spreads heat to neighbours.
void FireLogicSystem::update()
{
	if (!m_storage || m_numRows < 1 || m_numCols < 1)
		return;
	Int startRow = m_80 * m_numRows / 10;
	Int endRow = (m_80 + 1) * m_numRows / 10;
	Int row;
	for (row = startRow; row < endRow; ++row)
	{
		Int worldX = row * 10 + 5;
		Cell *cell = m_cells[row] + m_numCols;
		while (cell != m_cells[row])
		{
			--cell;
			if (cell->m_check == 0)
				continue;
			Int worldY = (cell - m_cells[row]) * 10 + 5;
			if (cell->m_check <= cell->m_flammability + m_98)
			{
				if (!cell->m_field30)
				{
					Rva00285BEC key(worldX, worldY);
					Rva002860CFIterator i = m_cellsOnFire.rva00286214((const Rva00285672 *)&key);
					if (i.m_node != m_cellsOnFire.m_header)
						m_cellsOnFire.erase(i);
				}
				cell->m_field30 = 0;
				cell->m_check = 0;
				if ((float)cell->m_fuel > 0.0f)
				{
					cell->m_type = 2;
					m_9C(worldX, worldY);
				}
			}
			else
			{
				if (cell->m_field30)
				{
					cell->m_field30 = 0;
					if (m_cellsOnFire.m_size >= (unsigned int)m_90)
					{
						cell->m_check = 0;
						continue;
					}
					Rva00287B2AResult added = insertCell(m_cellsOnFire, Rva00285BEC(worldX, worldY));
				}
				cell->m_check -= (unsigned short)(cell->m_flammability + m_98);
				Int consumed;
				if (cell->m_fuel <= cell->m_check)
				{
					consumed = cell->m_fuel;
					Rva00285BEC key(worldX, worldY);
					Rva002860CFIterator i = m_cellsOnFire.rva00286214((const Rva00285672 *)&key);
					if (i.m_node != m_cellsOnFire.m_header)
						m_cellsOnFire.erase(i);
					cell->m_check = 0;
					cell->m_field31 = 1;
					if ((float)cell->m_fuel > 0.0f)
					{
						cell->m_type = 2;
						m_9C(worldX, worldY);
					}
				}
				else
				{
					consumed = cell->m_check;
					cell->m_type = 1;
					m_9C(worldX, worldY);
				}
				cell->m_fuel -= (unsigned short)consumed;
				ObjectNode *node = cell->m_objects;
				while (node)
				{
					ObjectNode *next = node->m_next;
					if (TheTerrainLogic)
						((Rva0027F09F *)TheTerrainLogic)->rva0027F09F(node->m_id, consumed);
					node = next;
				}
			}
		}
	}

	_STL::map<ObjectID, Int> damage;
	Rva00286214 *onFire = &m_cellsOnFire;
	for (Rva00286214Node *n = onFire->m_header->m_left; n != onFire->m_header;
		n = (Rva00286214Node *)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base *)n))
	{
		Cell *cell = &m_cells[n->m_key.x / 10][n->m_key.y / 10];
		if (cell->m_check)
			for (WatcherNode *watcherNode = cell->m_0C; watcherNode; watcherNode = watcherNode->m_next)
				damage[watcherNode->m_id] += cell->m_check;
	}

	DamageInfo info;
	info.m_10 = 0x17;
	info.m_1C = 3;
	for (_STL::map<ObjectID, Int>::iterator it = damage.begin(); it != damage.end(); ++it)
	{
		Object *obj = TheGameLogic->findObjectByID((*it).first);
		if (obj && !obj->isSignificantlyAboveTerrain())
		{
			info.m_amount = (float)(*it).second;
			obj->attemptDamage(&info);
		}
	}

	if (startRow > 0)
		--startRow;
	if (endRow + 1 < m_numRows)
		--endRow;
	static _STL::vector<BfmePod8> s_pending;
	s_pending.clear();
	_STL::vector<Rva00287F76Element> &pending = (_STL::vector<Rva00287F76Element> &)s_pending;
	for (row = startRow; row < endRow; ++row)
	{
		for (Int col = 0; col < m_numCols; ++col)
		{
			Cell *rowCells = m_cells[row]; Cell *cell = &rowCells[col];
			if (cell->m_fuel == 0)
			{
				if (cell->m_field31)
				{
					Int index = TheTerrainLogic->materialAt((float)((row + 0.5) * 10.0), (float)((col + 0.5) * 10.0));
					if (index)
					{
						Material *material = &m_materials[index];
						if (cell->m_fuel < material->fuel)
						{
							cell->m_fuel += (unsigned short)m_94;
							if (cell->m_fuel >= material->fuel)
								cell->m_fuel = (unsigned short)material->fuel;
						}
						if (cell->m_fuel >= material->fuel)
							cell->m_field31 = 0;
					}
					else
						cell->m_field31 = 0;
				}
			}
			else
			{
				Int threshold = cell->m_field10;
				Int heat = 0;
				if (row > 0)
				{
					Int n = m_cells[row - 1][col].m_check;
					if (n > threshold)
						heat += n - threshold;
				}
				if (row + 1 < m_numRows)
				{
					Int n = m_cells[row + 1][col].m_check;
					if (n > threshold)
						heat += n - threshold;
				}
				if (col > 0)
				{
					Int n = cell[-1].m_check;
					if (n > threshold)
						heat += n - threshold;
				}
				if (col + 1 < m_numCols)
				{
					Int n = cell[1].m_check;
					if (n > threshold)
						heat += n - threshold;
				}
				if (heat > 0)
				{
					if (cell->m_check == 0)
					{
						if (m_cellsOnFire.size() >= (unsigned int)m_90)
							continue;
						cell->m_field30 = 0;
						Rva00287B2AResult added = insertCell(m_cellsOnFire, Rva00285BEC(row * 10 + 5, col * 10 + 5));
					}
					unsigned int value = cell->m_check + heat;
					if (value > cell->m_field18)
						value = cell->m_field18;
					{
					Rva00287F76Element e;
					e.m_cell = cell;
					e.m_value = (unsigned short)value;
					pending.push_back(e);
					}
				}
			}
		}
	}
	for (Rva00287F76Element *p = pending.begin(); p != pending.end(); ++p)
		((Cell *)p->m_cell)->m_check = p->m_value;

	if (++m_80 >= 10)
	{
		m_80 = 0;
		fireForEach(FireTickIt((FireTickNode *)onFire->m_header->m_left), FireTickIt((FireTickNode *)onFire->m_header), FireTickFn());
	}
}

// The primary retail vtable at VA 0x00BFB7BC dispatches update through slot 10.
// Target fuel comparison at 0x002880CE converts the unsigned-short value to float.
