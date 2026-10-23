// cl: /G7 /arch:SSE2 /O1 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep

#include "vector3.h"

class LineSegClass
{
public:
	Vector3 P0;
	Vector3 P1;
	Vector3 DP;
	Vector3 Dir;
	float Length;

	LineSegClass(const Vector3 &p0, const Vector3 &p1);

protected:
	void recalculate(void);
};

inline LineSegClass::LineSegClass(const Vector3 &p0, const Vector3 &p1) : P0(p0), P1(p1)
{
	recalculate();
}

// LineSegClass's two-Vector3 constructor is a header inline elsewhere: other units emit
// select-any copies, so a strong definition here was a duplicate in the linked build. This
// anchor only makes this unit emit its copy for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitLineSegVectorCtor@@YAXPAVLineSegClass@@ABVVector3@@@Z present-unmatched
void bfmeEmitLineSegVectorCtor(LineSegClass *lineSeg, const Vector3 &v)
{
	lineSeg->LineSegClass::LineSegClass(v, v);
}
#pragma inline_depth()
