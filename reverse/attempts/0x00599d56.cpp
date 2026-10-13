// ?preEmptivelyBuildDozers@AIDozerManager@@QAEXXZ
// partial score=0.93 date=2026-10-13
// ?preEmptivelyBuildDozers@AIDozerManager@@QAEXXZ 0x00599D56 (390 B)
// Identity: WB twin 0x01530980 (AIDozerManager.cpp asserts 247/273); siblings
// buildDozer 0x00599564, rva00599AE3 0x00599AE3, rva00599EDC 0x00599EDC.
// Result under explain_mismatch: 390 bytes compiled, 22 diffs left:
//  - EBX/EDI role swap through both loops: retail keeps the outer iterator in
//    ebx (spilled [ebp-0x14]) and the inner iterator in ebx, factory in edi;
//    ours is reversed. A probe adding a real extra factory use in the inner
//    loop flips it (MSVC weight-based regalloc); ~30 code-neutral shapes and
//    /Op /Ob1 /GX left 22.
//  - push_back of the 8-byte Rva00599435Keyframe vector is ICF-folded at
//    retail 0x00539A2E: land with a fold-proof pin (tools/pin_admission.py --add).
// On landing rename the rva00599D56() declaration/call in
// Code/GameEngine/Source/Common/Rva00599825ListAdd.cpp (rva00599EDC) to
// preEmptivelyBuildDozers. Key fixes so far: C++-linkage free (98->41 was the
// WB-shaped delta with inline sub/lengthSqrd2D; 41->22 the free trick).
// Home path tried: Code/GameEngine/Source/GameLogic/SkirmishAI/AIDozerManager.cpp
// cl: /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /O1 /G7 /arch:SSE /MD /EHsc
// stlport
// Retail frees vector storage through the C++-linkage free (0x00030830),
// which keeps the unwind-state store before the call.
#define free bfmeUnusedCRTFree
#include <cstdlib>
#undef free
void free(void *);
#include "../../Common/GameLogicObjectLookupView.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include <list>
#include <vector>
#include <algorithm>

extern GameLogic *TheGameLogic;

class Object
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	bool isDestroyed() const { return (m_status438 & 1) != 0; }
private:
	char m_pad000[0x38];
	Coord3D m_pos;
	char m_pad044[0x438 - 0x44];
	unsigned char m_status438;
};

struct Rva00599435Keyframe
{
	float m_value;
	unsigned int m_frame;
};

struct Rva00599435Compare
{
	bool operator()(const Rva00599435Keyframe &a, const Rva00599435Keyframe &b) const { return a.m_value > b.m_value; }
};

// Coord3D::sub and Coord3D::GetLengthSqrd2D as the WB twin calls them;
// retail inlines both.
static inline void subCoord3D(Coord3D *dst, const Coord3D *a)
{
	dst->x -= a->x;
	dst->y -= a->y;
	dst->z -= a->z;
}
static inline float lengthSqrd2D(const Coord3D *c)
{
	float x_value = c->x;
	float y_value = c->y;
	return x_value * x_value + y_value * y_value;
}

class AIDozerManager
{
public:
	void buildDozer(Object *factory);
	bool rva00599AE3(Object *factory);
	void preEmptivelyBuildDozers();
private:
	_STL::list<ObjectID> m_dozers;
	_STL::list<ObjectID> m_factories;
};

void AIDozerManager::preEmptivelyBuildDozers()
{
	if (m_dozers.size() >= m_factories.size())
		return;
	_STL::vector<Rva00599435Keyframe> candidates;
	_STL::list<ObjectID>::iterator end = m_factories.end();
	for (_STL::list<ObjectID>::iterator it = m_factories.begin(); it != end; ++it) {
		Object *factory = TheGameLogic->findObjectByID(*it);
		if (factory == 0 || factory->isDestroyed() || !rva00599AE3(factory))
			continue;
		Rva00599435Keyframe c;
		c.m_value = 0.0f;
		c.m_frame = (unsigned int)factory;
		for (_STL::list<ObjectID>::iterator d = m_dozers.begin(); d != m_dozers.end(); ++d) {
			Object *dozer = TheGameLogic->findObjectByID(*d);
			Coord3D delta;
			delta.x = dozer->getPosition()->x;
			delta.y = dozer->getPosition()->y;
			delta.z = dozer->getPosition()->z;
			subCoord3D(&delta, factory->getPosition());
			float dist = lengthSqrd2D(&delta);
			if (dist > c.m_value)
				c.m_value = dist;
		}
		candidates.push_back(c);
	}
	if (!candidates.empty()) {
		_STL::sort(candidates.begin(), candidates.end(), Rva00599435Compare());
		unsigned int count = m_factories.size() - m_dozers.size();
		if (count != 0)
			for (Rva00599435Keyframe *p = candidates.begin(); p != candidates.end() && count > 0; ++p, --count)
				buildDozer((Object *)p->m_frame);
	}
}
