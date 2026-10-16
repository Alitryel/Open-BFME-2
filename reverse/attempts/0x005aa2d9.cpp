// ?rva005AA2D9@Rva0015334F@@QAEXPAURva005AA55DRecord@@PBUCoord3D@@1@Z
// partial score=0.97 date=2026-10-16
// ?rva005AA2D9@Rva0015334F@@QAEXPAURva005AA55DRecord@@PBUCoord3D@@1@Z
// partial score=0.97 date=2026-10-16
// W9-O2 (claude-opus-5.5): whole-owner bank of AIFlankAttackTactic.cpp with calculatePath 0x5AA2D9 in WB
// 0x151B010 statement order: 489/488 B, nd 14, frame 0x38 exact. Levers that got here: (1) member-wise copy of
// *to into dir/beyond (a POD struct copy gives rep movsd), (2) visible __declspec(noinline) inline
// Coord3D::length and ::normalize as in AIAttackApproachComputePath.cpp (side's address no longer escapes:
// frame 0x44 -> 0x38, dead side stores gone; normalize visible with length opaque is 0x44 again), (3) the
// retail __FILE__ string and literal lines 78/91 (push imm8), (4) unsigned distance (fild + 2^32 fix-up), no side
// zero-init. Residue: the final pivot += side*d: retail multiplies y, then x as movaps d / mulss [side.x], then
// z, ours loads side x,y,z and multiplies in place (and stores pivot.y early). Inert/worse: explicit
// pivot.c += side.c*d (484 B), d*side.c, scaled copy, all six component orders of the scale/add, local or
// function-scope float d, opaque length.
// cl: /MD /GX /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// The "FlankAttack" skirmish-AI tactic (vtable 0x00871EB0; ctor 0x005AA23E in
// Rva004ECECDTacticCtors.cpp, dtor 0x005AA55D in Rva005AA55DDtor.cpp, slot 9
// in Rva004ECECDTacticCreate.cpp). Base chain, all address-derived:
// AITacticOffensive (ctor 0x005DC722) over the AITactic.cpp object AITactic.
// +0x58 owns the flank route (Rva0015334F, 0x10 bytes): the index of the next
// point and a vector<Coord3D> of points, filled by 0x005AA2D9 and transferred
// by 0x005AA4C1.
//
//   0x005AA0D8  slot 1: never against a target sitting on its owner's
//               "Player_%d_Start" waypoint when that waypoint is of kind 5,
//               nor one closer than sqrt(2000000) to this owner's base
//               (0x004EBF4B), else the base test
//   0x005AA60F  slot 5: xfer: the AITactic's, then the route
//   0x005AA5AE  slot 6: with a team, plan the route from the team's centre
//               to the +0x20 record's point; otherwise stop
//   0x005AA1EA  slot 7 (not here yet): while running, once 0x004ED169 says so or the record
//               is flagged, head for the next route point, or stop (1, 0)
//               when the route is done
#include <vector>
#include <math.h>
#include "ascii_string.h"

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

#include "../../../../../../../Libraries/Include/Lib/Coord3D.h"

class Xfer;
class Player;

class Object
{
public:
	Player *getControllingPlayer() const;
};

class GameSlot
{
public:
	char m_pad00[0x10];
	int m_10;		// +0x10, the slot's start position index
};

struct Rva00506C82Arg;
GameSlot *__cdecl Rva00506C82Find(const Rva00506C82Arg *arg);

class Waypoint
{
public:
	char m_pad00[0x60];
	int m_60;		// +0x60
};
Waypoint *Rva00506CC3FindWaypoint(const AsciiString &name);

class Rva002C589B
{
public:
	Object *rva002C5DA6();
	char m_pad00[0x0C];
	Coord3D m_0C;		// +0x0C
};

class Rva004EBF4B
{
public:
	Coord3D rva004EBF4B();
};

struct Rva002A8AB1Record;

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;

class Team
{
public:
	Coord3D *rva0039DA2A(Coord3D *out) const;
};

struct Rva005AA55DRecord
{
	char m_pad00[0x0C];
	Coord3D m_point0C;	// +0x0C
	bool m_18;		// +0x18
};

// getPivotPoint's hidden result (Rva005AA05APivotPoint.cpp): member-wise copy constructor.
struct Rva005AA05APoint { float x, y, z; Rva005AA05APoint(const Coord3D &v) { x = v.x; y = v.y; z = v.z; } };

class Rva0015334F
{
public:
	void rva005AA2D9(Rva005AA55DRecord *record, const Coord3D *from, const Coord3D *to);
	Rva005AA05APoint getPivotPoint(Rva005AA55DRecord *record, const Coord3D *from, const Coord3D *to);
	void xfer(Xfer *xfer);
	bool done() const { return m_next == m_points.end()-m_points.begin(); }
	Coord3D *next() { int n=m_next++; return &(this ? m_points : m_points)[n]; }
	int m_next;			// +0x00
	_STL::vector<Coord3D> m_points;	// +0x04
};

class AITactic
{
public:
	virtual ~AITactic();
	virtual bool canRun(void *request);
	virtual void cleanUp();
	virtual void initializeTeamTemplate();
	virtual void v4();
	virtual void xfer(Xfer *xfer);
	virtual void run();
	virtual void update();
	virtual void v8();
	virtual AITactic *create();
	Team *rva004ECECD(int index);
	unsigned char rva004ED169();
	void rva004ED342(void *point);
	void end(bool a, bool b);
};

class AITacticOffensive : public AITactic
{
public:
	virtual ~AITacticOffensive();
	unsigned char checkTarget(void *request);
	char m_pad04[0x10 - 4];
	bool m_running;			// +0x10
	char m_pad11[0x20 - 0x11];
	Rva005AA55DRecord *m_record;	// +0x20
	void *m_owner;			// +0x24
	char m_pad28[0x58 - 0x28];
};

class AIFlankAttackTactic : public AITacticOffensive
{
public:
	virtual ~AIFlankAttackTactic();
	virtual bool canRun(void *request);
	virtual void xfer(Xfer *xfer);
	virtual void run();
	virtual void update();
private:
	Rva0015334F *m_route;	// +0x58
};

bool AIFlankAttackTactic::canRun(void *request)
{
	Rva002C589B *target = (Rva002C589B *)request;
	Object *obj = target->rva002C5DA6();
	if (obj) {
		GameSlot *slot = Rva00506C82Find((const Rva00506C82Arg *)obj->getControllingPlayer());
		if (slot) {
			int start = slot->m_10;
			AsciiString name;
			name.format("Player_%d_Start", start + 1);
			Waypoint *waypoint = Rva00506CC3FindWaypoint(name);
			if (waypoint && waypoint->m_60 == 5)
				return false;
		}
	}
	Rva004EBF4B *record = (Rva004EBF4B *)g_00DFEEF8->rva002A8AB1(m_owner);
	Coord3D base = record->rva004EBF4B();
	base.x -= target->m_0C.x;
	base.y -= target->m_0C.y;
	base.z -= target->m_0C.z;
	if (base.x * base.x + base.y * base.y + base.z * base.z < 2000000.0f)
		return false;
	if (checkTarget(request))
		return true;
	return false;
}

void AIFlankAttackTactic::run()
{
	Team *team = rva004ECECD(0);
	if (team) {
		Coord3D from;
		team->rva0039DA2A(&from);
		Coord3D to;
		to.x = m_record->m_point0C.x;
		to.y = m_record->m_point0C.y;
		to.z = m_record->m_point0C.z;
		m_route->rva005AA2D9(m_record, &from, &to);
	} else {
		end(0, 0);
	}
}

// The rowed leaves 0x000035B6 / length, visible and out of line as in
// AIAttackApproachComputePath.cpp: the side vector's address does not escape.
__declspec(noinline) inline float Coord3D::length() const
{
    return (float)sqrt(x * x + y * y + z * z);
}

__declspec(noinline) inline void Coord3D::normalize()
{
    float len = length();
    if (len != 0.0f) {
        float scale = 1.0f / len;
        x *= scale;
        y *= scale;
        z *= scale;
    }
}

static __forceinline void flankCopy(Coord3D &c, const Coord3D *a) { c.x = a->x; c.y = a->y; c.z = a->z; }
// BaseType.h's inline Coord3D arithmetic, which the canonical header leaves out of line.
template <class T> static __forceinline void flankAdd(T &c, const Coord3D *a) { c.x += a->x; c.y += a->y; c.z += a->z; }
static __forceinline void flankSub(Coord3D &c, const Coord3D *a) { c.x -= a->x; c.y -= a->y; c.z -= a->z; }
static __forceinline void flankScale(Coord3D &c, float scale) { c.x *= scale; c.y *= scale; c.z *= scale; }
static __forceinline void flankCross(const Coord3D *a, const Coord3D *b, Coord3D *r)
{
	r->x = a->y * b->z - a->z * b->y;
	r->y = a->z * b->x - a->x * b->z;
	r->z = a->x * b->y - a->y * b->x;
}
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
#define FLANK_SOURCE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AITacticalAI\\AITacticsGenerator\\OffensiveTactics\\AIFlankAttackTactic.cpp"

// AIFlankAttackTacticImp::calculatePath (WorldBuilder 0x0151B010), retail 0x005AA2D9
// (488 bytes, RET 12): a route of four points - the start, the pivot point
// (0x005AA05A) pushed sideways, a point 600..1000 past the destination along the
// approach, and the destination. Statement order as the WorldBuilder twin.
void Rva0015334F::rva005AA2D9(Rva005AA55DRecord *record, const Coord3D *from, const Coord3D *to)
{
	unsigned int distance = (int)(GetGameLogicRandomValueReal(0.0f, 400.0f, FLANK_SOURCE_FILE, 78) + 600.0f);
	Coord3D dir;
	flankCopy(dir, to);
	flankSub(dir, from);
	dir.normalize();
	Coord3D beyond;
	flankCopy(beyond, to);
	flankScale(dir, (float)distance);
	flankAdd(beyond, &dir);
	Rva005AA05APoint pivot = getPivotPoint(record, from, to);
	Coord3D up;
	up.x = 0.0f;
	up.y = 0.0f;
	up.z = 1.0f;
	if (GetGameLogicRandomValue(0, 1, FLANK_SOURCE_FILE, 91) == 1)
		up.z = -1.0f;
	Coord3D side;
	flankCross(&dir, &up, &side);
	side.normalize();
	flankScale(side, (float)distance);
	flankAdd(pivot, &side);
	m_points.push_back(*from);
	m_points.push_back(*(const Coord3D *)&pivot);
	m_points.push_back(beyond);
	m_points.push_back(*to);
}

void AIFlankAttackTactic::xfer(Xfer *xfer)
{
	AITactic::xfer(xfer);
	m_route->xfer(xfer);
}

// Native5AA1EA..5AA23E complete84B; existing vslot7 and route+58 prove
// this update. The same-valued route expression retains native index scaling
// before the increment store; no runtime branch or barrier is emitted.
void AIFlankAttackTactic::update()
{
 if (!m_running) return;
 if (!rva004ED169() && !m_record->m_18) return;
 if (m_route->done()) { end(true,false); return; }
 rva004ED342(m_route->next());
}
