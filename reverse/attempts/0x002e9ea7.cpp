// ?rva002E9EA7@Pathfinder@@QAE_NPAVObject@@HHW4PathfindLayerEnum@@HHPAH@Z
// partial score=0.8241 date=2026-10-16
// cl: /O1 /DNDEBUG /MD
// Pathfinder::rva002E9EA7 @0x002E9EA7 531B, RET 0x1C. Semantic guide: ZH
// Pathfinder::checkDestination and BFME 1 PathfindCheckDestination.cpp
// (donor facts): numCellsAbove = radius, +1 when centred; ignoreId/objID
// from the AI interface (+0x258, getter 0x6E009) and object id (+0x74);
// i/j rectangle walk with getCell, an obstacle cell continuing to j++ when
// IsObstaclePresent(ignoreId). BFME 2 additions (target bytes): a template
// kind-of override (+0x115 bit 0x20, layer 1 terrain probe through 0x2E79A8
// and TheTerrainLogic slot 50) forcing radius 1 centred, a second override
// (+0x113 bit 4, +0x109 bit 1, layer != 1) forcing radius 1 uncentred, and
// two occupant lists counting into *count. ignoreId and j reuse the dead
// iRadius/centerInCell parameters, which reproduces retail's frame slots.
void __cdecl rva002E79A8(int a1, unsigned char a2, int a3, int a4, int a5);

struct Rva002E8BCFSrc
{
	char _00[0x10];
	int m10;
	char _14;
	bool m15;
};

// 0x2E79A8 writes 3 floats through a1 ([eax], [eax+4], [eax+8]).
struct Rva002E79A8Out
{
	float m_0;
	float m_4;
	float m_8;
};

enum Relationship
{
	REL_0 = 0,
	REL_1 = 1,
	REL_2 = 2
};

enum PathfindLayerEnum
{
	PF_LAYER_0 = 0
};

struct ObjectInner
{
	char _00[0x109];
	unsigned char m_109;
	char _10A[0x113 - 0x10A];
	unsigned char m_113;
	char _114;
	unsigned char m_115;
};

class Object
{
public:
	bool rva0028AFBB() const;
	Relationship getRelationship(const Object *other) const;
	bool IsAtGoalPosition() const;
	char _00[4];
	ObjectInner *m_04;
	char _08[0x74 - 8];
	int m_74;
	char _78[0x258 - 0x78];
	void *m_258;
	char _25C[0x274 - 0x25C];
	Object *m_274;
};

class Rva0006E009DwordField
{
public:
	int get() const;
};

struct Rva002E9EA7Occ1
{
	Rva002E9EA7Occ1 *m_next;
	char _04[4];
	Object *m_obj;
};

struct Rva002E9EA7Head1
{
	char _00[0x14];
	Rva002E9EA7Occ1 *m_14;
};

struct Rva002E9EA7Occ2
{
	Rva002E9EA7Occ2 *m_next;
	char _04[4];
	Object *m_obj;
};

enum ObjectID
{
	INVALID_ID = 0
};

class PathfindCell
{
public:
	bool IsObstaclePresent(ObjectID id) const;
	PathfindCell *m_0;
	char _04[8];
	unsigned int m_C;
	char _10[0x10];
	Rva002E9EA7Occ2 *m_20;
};

class Pathfinder
{
public:
	PathfindCell *getCell(PathfindLayerEnum layer, int x, int y);
	bool rva002E9EA7(Object *a1, int a2, int a3, PathfindLayerEnum a4, int a5i, int a5b, int *a6);
};


// TheTerrainLogic vtable slot 50 (+0xC8) bool probe over the 0x1C-byte
// 0x2E79A8 output. Earlier slots unmodelled.
class __declspec(novtable) TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual bool rva002E9EA7Slot50(void *tmp) = 0;
};

extern TerrainLogic *TheTerrainLogic;

bool Pathfinder::rva002E9EA7(Object *obj, int cellX, int cellY, PathfindLayerEnum layer, int iRadius, int centerInCell, int *count)
{
	Rva002E79A8Out tmp;
	int radius;
	unsigned char center;
	if ((obj->m_04->m_115 & 0x20) != 0 && (layer != 1 || (rva002E79A8((int)&tmp, 1, cellX, cellY, 1), TheTerrainLogic->rva002E9EA7Slot50(&tmp))))
	{
		radius = 1;
		center = 1;
	}
	else
	{
		radius = iRadius;
		center = (unsigned char)centerInCell;
	}
	if ((obj->m_04->m_113 & 4) != 0 && (obj->m_04->m_109 & 1) != 0 && layer != 1)
	{
		radius = 1;
		center = 0;
	}
	int numCellsAbove = radius;
	if (center)
		numCellsAbove++;
	*count = 0;
	iRadius = INVALID_ID;
	int objID = 0;
	if (obj->m_258 != 0)
	{
		iRadius = ((Rva0006E009DwordField *)obj->m_258)->get();
		objID = obj->m_74;
	}
	for (int i = cellX - radius; i < cellX + numCellsAbove; i++)
	{
		for (centerInCell = cellY - radius; centerInCell < cellY + numCellsAbove; centerInCell++)
		{
			PathfindCell *cell = getCell(layer, i, centerInCell);
			if (cell == 0)
				return false;
			unsigned int tag = cell->m_C;
			if ((tag & 15) == 5)
				return false;
			if ((((unsigned char)(tag >> 18) & 1) != 0) && obj->rva0028AFBB())
				return false;
			unsigned int tag2 = cell->m_C;
			int k = tag2 & 15;
			if (k == 2)
				return false;
			if (k == 4)
			{
				if (cell->IsObstaclePresent((ObjectID)iRadius))
					continue;
				return false;
			}
			if (k == 5 || k == 6)
				return false;
			if ((((unsigned char)(tag2 >> 18) & 1) != 0) && obj->rva0028AFBB())
				return false;
			void *n1 = cell->m_0;
			Rva002E9EA7Occ1 *b = n1 ? ((Rva002E9EA7Head1 *)n1)->m_14 : 0;
			while (b != 0)
			{
				Object *o = b->m_obj;
				if (o->m_74 != objID && o->m_74 != iRadius && o->m_274 != obj)
				{
					if (obj->getRelationship(o) == REL_2)
						(*count)++;
					else if (o->IsAtGoalPosition())
						return false;
				}
				b = b->m_next;
			}
			cell = (PathfindCell *)cell->m_0;
			Rva002E9EA7Occ2 *s = cell ? cell->m_20 : 0;
			while (s != 0)
			{
				Object *o = s->m_obj;
				if (o->m_74 != objID && o->m_274 != obj)
				{
					if (obj->getRelationship(o) == REL_2)
						*count += 3;
					else
						(*count)++;
				}
				s = s->m_next;
			}
		}
	}
	return true;
}
