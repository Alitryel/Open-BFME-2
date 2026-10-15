// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// InGameUI's heading query, native 0x0029B3C1..0x0029B45C (155B, RET4);
// WorldBuilder DB5240 is the debug twin. Without the override flag (+0x9B4)
// it is the object's own orientation (+0x1C0); with it, the heading from the
// object's position (+0x38) toward the override point (+0x9B8) in the XY
// plane -- the orientation again when that point is within 1 of it --
// recovered from the normalized direction's x by ACos, negated for a
// negative y. W3DModelDraw::reactToTransformChange (0x0029B3C1 callers)
// rotates the model by it. The method name is address-derived. The else
// after the near-target return keeps cl's cross-jump on the first
// orientation block (retail's ja back to 0x0029B3D3).

#include "../../../Libraries/Include/Lib/Coord3DInline.h"

float ACos(float);

static inline float lengthSqr2D(const Coord3D &c)
{
	return c.x * c.x + c.y * c.y;
}

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	// Keep this BFME offset-specific view inlined; the other private Object
	// layouts must not share its standalone getter.
	__declspec(dllimport) __forceinline float getOrientation() const { return m_orientation; }
private:
	char m_pad000[0x38];
	Coord3D m_position;			// +0x38
	char m_pad044[0x1C0 - 0x44];
	float m_orientation;		// +0x1C0
};

class InGameUI
{
public:
	float rva0029B3C1(const Object *obj) const;
private:
	char m_pad000[0x9B4];
	bool m_overrideHeading;		// +0x9B4
	char m_pad9B5[3];
	Coord3D m_headingTarget;	// +0x9B8
};

float InGameUI::rva0029B3C1(const Object *obj) const
{
	if (!m_overrideHeading)
		return obj->getOrientation();
	Coord3D dir;
	dir.set(&m_headingTarget);
	dir.sub(obj->getPosition());
	if (lengthSqr2D(dir) < 1.0f)
		return obj->getOrientation();
	else {
		dir.Normalize2D();
		if (dir.y < 0.0f)
			return -ACos(dir.x);
		else
			return ACos(dir.x);
	}
}
