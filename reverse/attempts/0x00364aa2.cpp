// ?rva00364AA2@Path@@QAEXPAVPathNode@@00M@Z
// partial score=0.6981127453099645 date=2026-10-19
// ?rva00364AA2@Path@@QAEXPAVPathNode@@00M@Z
// partial score=0.6606047434 date=2026-10-16
// cl: /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep /ICode/Libraries/Include/Lib

#define NULL 0

// Path node reclamation and teardown (GameLogic AI pathfinding). Nodes live
// in the Rva pool behind the global at 0x00E01E94 and are returned through
// its rowed FreeObject body; the local node type carries its next link at
// +0x0 (matching the rowed PathNode layout).

struct Rva00065964ObjectPool
{
	void FreeObject(void *obj);
};

// g_pathNodePool: matched references place it at VA 0xe01e94 (zero-filled; a plain-data view).
Rva00065964ObjectPool g_pathNodePool;

#include "vector3.h"
#include "Coord2D.h"
#define COORD3D_VIEW_DTOR
#include "Coord3DCtorView.h"

class LineSegClass
{
public:
	LineSegClass(const Vector3 &p0, const Vector3 &p1);
	void Set(const Vector3 &p0, const Vector3 &p1);
	bool Find_Intersection(const LineSegClass &other_line, Vector3 *p1, float *fraction1, Vector3 *p2, float *fraction2) const;
	const Vector3 &Get_Dir(void) const { return Dir; }
	float Get_Length(void) const { return Length; }

	Vector3 P0;
	Vector3 P1;
	Vector3 DP;
	Vector3 Dir;
	float Length;
};

struct Rva00363B4BVector { float x, y, z; };
float rva00363B4BAngle(const Rva00363B4BVector *a, const Rva00363B4BVector *b);

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };

class PathNode
{
public:
	const Coord3D *getPosition(void) const { return &m_pos; }
	void setPosition(const Coord3D *pos) { m_pos = *pos; }
	PathfindLayerEnum getLayer(void) const { return m_layer; }

	PathNode *m_next;
	char m_pad04[8];
	Coord3D m_pos;
	PathfindLayerEnum m_layer;
	int m_1c;
	int m_id20;
};


class Path
{
	void *m_unknown00;
	PathNode *m_head04;

public:
	~Path();

	void rva002655E3(const Coord3D *pos, PathfindLayerEnum layer, int portal);
	void rva003649B1(const PathNode *node);
	int rva003641AE(float angle, float radius);
	void rva00364AA2(PathNode *prev, PathNode *cur, PathNode *next, float radius);
};

// ?FreePooledNode@@YAXPAX@Z, retail 0x00265488, 22 bytes. Null-checked
// pool free: drops nulls, otherwise returns the node to the path pool.
void __cdecl FreePooledNode(void *node)
{
	if (node == NULL)
		return;
	g_pathNodePool.FreeObject(node);
}

// ??1Path@@QAE@XZ, retail 0x00364A89, 25 bytes. Walks the node list
// returning each node to the path pool.
Path::~Path()
{
	PathNode *node = m_head04;
	if (node == NULL)
		return;
	PathNode *next;
	do
	{
		next = node->m_next;
		FreePooledNode(node);
		node = next;
	} while (next != NULL);
}

class Rva00364A37
{
public:
	~Rva00364A37();
};

class Rva003652FF
{
public:
	void rva003652FF();
};

void Rva003652FF::rva003652FF()
{
	((Rva00364A37 *)this)->~Rva00364A37();
}

class Rva00364A60
{
public:
	~Rva00364A60();
};

class Rva00365304
{
public:
	void rva00365304();
};

void Rva00365304::rva00365304()
{
	((Rva00364A60 *)this)->~Rva00364A60();
}

// Normal copies expire after the angle query; tail locals use a sibling scope.
void Path::rva00364AA2(PathNode *prev, PathNode *cur, PathNode *next, float radius)
{
	Coord3D prevPos(*prev->getPosition());
	Coord3D curPos(*cur->getPosition());
	Coord3D nextPos(*next->getPosition());
	prevPos.z=curPos.z;
	nextPos.z=curPos.z;
	LineSegClass seg1(Vector3(prevPos.x, prevPos.y, 0), Vector3(curPos.x, curPos.y, 0));
	LineSegClass seg2(Vector3(curPos.x, curPos.y, 0), Vector3(nextPos.x, nextPos.y, 0));
	float minLen = seg1.Get_Length();
	if (minLen > seg2.Get_Length())
		minLen = seg2.Get_Length();
	if (radius > minLen * 0.75f)
		radius = minLen * 0.75f;
	Coord2D a, d;
	bool turnLeft;
	if (Vector3::Cross_Product_Z(seg1.Get_Dir(), seg2.Get_Dir()) < 0.0f) {
		a.x = prevPos.x; a.y = prevPos.y;
		d.x = nextPos.x; d.y = nextPos.y;
		turnLeft = true;
	} else {
		d.x = prevPos.x; d.y = prevPos.y;
		a.x = nextPos.x; a.y = nextPos.y;
		turnLeft = false;
		seg1.Set(Vector3(a.x, a.y, 0), Vector3(curPos.x, curPos.y, 0));
		seg2.Set(Vector3(curPos.x, curPos.y, 0), Vector3(d.x, d.y, 0));
	}
	float angle = rva00363B4BAngle((const Rva00363B4BVector *)&seg1.Get_Dir(), (const Rva00363B4BVector *)&seg2.Get_Dir());
	if (angle < 0.7225663304328919)
		radius *= 1.75f;
	if (cur->m_id20 != 0x7fffffff || angle > 1.7278761f) {
		rva003649B1(cur);
		return;
	}
	Vector3 v1 = radius * seg1.Get_Dir();
	Vector3 v2 = radius * seg2.Get_Dir();
	v1.Rotate_Z(-1.5707963705062866f);
	v2.Rotate_Z(-1.5707963705062866f);
	LineSegClass off1(Vector3(a.x, a.y, 0) + v1, Vector3(curPos.x, curPos.y, 0) + v1);
	LineSegClass off2(Vector3(curPos.x, curPos.y, 0) + v2, Vector3(d.x, d.y, 0) + v2);
	float arc;
	{
		Vector3 n1 = v1;
		Vector3 n2 = v2;
		n1.Normalize();
		n2.Normalize();
		arc = rva00363B4BAngle((const Rva00363B4BVector *)&n1, (const Rva00363B4BVector *)&n2);
	}
	{
		int count = rva003641AE(arc, radius);
		if (count < 2) {
			rva003649B1(cur);
			return;
		}
		float step = arc / count;
		Vector3 center;
		Vector3 other;
		float fraction;
		if (!off1.Find_Intersection(off2, &center, &fraction, &other, &fraction))
			return;
		Coord3D pt;
		if (turnLeft) {
			pt.x = center.X - v1.X; pt.y = center.Y - v1.Y; pt.z = curPos.z;
			rva002655E3(&pt, cur->getLayer(), 0x7fffffff);
			v1 *= -1.0f;
			for (int i = 1; i < count; ++i) {
				Vector3 q = center + v1;
				v1.Rotate_Z(-step);
				pt.x = q.X; pt.y = q.Y; pt.z = curPos.z;
				rva002655E3(&pt, cur->getLayer(), 0x7fffffff);
			}
			pt.x = center.X - v2.X; pt.y = center.Y - v2.Y; pt.z = curPos.z;
			rva002655E3(&pt, cur->getLayer(), 0x7fffffff);
			cur->setPosition(&pt);
		} else {
			pt.x = center.X - v2.X; pt.y = center.Y - v2.Y; pt.z = curPos.z;
			rva002655E3(&pt, cur->getLayer(), 0x7fffffff);
			v2 *= -1.0f;
			for (int i = 1; i < count; ++i) {
				v2.Rotate_Z(step);
				Vector3 q = center + v2;
				pt.x = q.X; pt.y = q.Y; pt.z = curPos.z;
				rva002655E3(&pt, cur->getLayer(), 0x7fffffff);
			}
			pt.x = center.X - v1.X; pt.y = center.Y - v1.Y; pt.z = curPos.z;
			rva002655E3(&pt, cur->getLayer(), 0x7fffffff);
			cur->setPosition(&pt);
		}
	}
}
