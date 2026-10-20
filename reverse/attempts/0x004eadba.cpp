// ?rva004EADBA@AIWall@@QAEMPBVCoord2D@@@Z
// partial score=0.995 date=2026-10-20
// ?distSqToSegment@@YAMPBUCoord2D@@00@Z (0x4EACF5, 197 B) + ?distanceSq@Polyline@@UBEMPBUCoord2D@@@Z (0x4EADBA, 227 B)
// r26 joint candidate. helper fit 0.9481 (10 insn diffs, IPRA regs now exact: p=ECX a=EAX b=EDX); caller exact except
// the unresolved local call. Params (p, a, b) = (pt, lineStart, lineEnd) as ZH Geometry.cpp calcPointToLineDistSquared;
// retail caller lea order edx(b), eax(a), ecx(p) = right-to-left of (p, a, b). Separate returns raise p's use count (8 > b's 6).
// w1 2026-10-20: owner is AIWall by layout (+4 selected04, +8 orders08 vector, vslot13 position() by value), the
// 4EBB58 previous/current idiom and adjacency to 4EAF18; name stays address-derived. Canonical Coord2D/Coord3D (class
// gate clean, no Coord2D ctor). Each early-out copies its endpoint into a local Coord2D before calcDistSquared: helper
// 0 structural, 4 operand diffs left (apy computed before apx at entry); caller exact except the local call reloc.
// Struct lineToPt fixes that order but colours dx/dy xmm2/xmm3. See reverse/attempt_support/0x004eadba_20261020_w1.md
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
#include "../../Code/Libraries/Include/Lib/Coord2D.h"
#include "../../Code/Libraries/Include/Lib/Coord3D.h"
struct WallBoundaryPoint : Coord2D {
	WallBoundaryPoint &set(float a, float b) { x=a; y=b; return *this; }
};
class WallPositionOrderView {
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12();
	virtual Coord3D position();
};
template <typename NUM> inline NUM sqr(NUM x) { return x * x; }
static float calcDistSquared(const Coord2D &a, const Coord2D &b) { return sqr(a.y - b.y) + sqr(a.x - b.x); }
// Squared distance from pt to the segment lineStart..lineEnd; native IPRA args lineStart=EAX lineEnd=EDX pt=ECX.
static __declspec(noinline) float distSqToSegment(const Coord2D *pt, const Coord2D *lineStart, const Coord2D *lineEnd)
{
	float dx = lineEnd->x;
	float dy = lineEnd->y;
	float apx = pt->x - lineStart->x;
	float apy = pt->y - lineStart->y;
	dx -= lineStart->x;
	dy -= lineStart->y;
	float dot = apy * dy;
	dot += apx * dx;
	if (dot <= 0.0f)
	{
		// angle is obtuse
		Coord2D closest;
		closest.x = lineStart->x;
		closest.y = lineStart->y;
		return calcDistSquared(closest, *pt);
	}
	float lineLenSqr = calcDistSquared(*lineEnd, *lineStart);
	if (dot >= lineLenSqr)
	{
		Coord2D closest;
		closest.x = lineEnd->x;
		closest.y = lineEnd->y;
		return calcDistSquared(closest, *pt);
	}
	float tmp = dot / lineLenSqr;
	Coord2D closest;
	closest.x = lineStart->x + tmp * dx;
	closest.y = lineStart->y + tmp * dy;
	return calcDistSquared(closest, *pt);
}
class AIWall
{
public:
	float rva004EADBA(const Coord2D *pt);
private:
	void *unknown00;
	WallPositionOrderView *selected04;
	WallPositionOrderView **orders08;	// AIWall.cpp: _STL::vector<WallPositionOrderView *> begin
	WallPositionOrderView **orders0c;	// and finish
};
// Smallest squared distance from pt to the wall polyline selected04 -> orders08[...].
float AIWall::rva004EADBA(const Coord2D *pt)
{
	float best = -1.0f;
	WallBoundaryPoint p;
	p.x = pt->x;
	p.y = pt->y;
	WallBoundaryPoint previous;
	previous.set(selected04->position().x, selected04->position().y);
	WallPositionOrderView **end = orders0c;
	for (WallPositionOrderView **order = orders08; order != end; ++order)
	{
		WallBoundaryPoint current;
		current.set((*order)->position().x, (*order)->position().y);
		float d = distSqToSegment(&p, &previous, &current);
		if (best < 1.0f || d < best)
			best = d;
		previous = current;
	}
	return best;
}
