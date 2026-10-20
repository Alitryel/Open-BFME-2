// cl: /DNDEBUG /MD
//
// ?create@ApplyRandomForceNugget@@UBEXPBVObject@@0I@Z @0x001F01F1 86B.
// Tiny x87 float helper (ObjectCreationNugget neighbourhood, per the range
// notes): null-checks the param at [ebp+8] and its +0x25C object pointer,
// spills this+4..this+16 as four floats through calcRandomForce at
// 0x001F0247 into a three-float stack vector, then issues the thiscall at
// 0x003909FA on the +0x25C object with (&force, 0, 0). Evidence (target facts
// read from game.dat): ret 0xC with only [ebp+8] read (the two trailing
// parameters are unused); fld/fstp order is this+16 first; caller
// cleanup add esp,0x14 proves the 0x001F0247 call takes 5 stack args with
// ecx untouched (cdecl spelling); the 0x003909FA call is a direct
// E8 with ecx=esi (thiscall spelling on an opaque struct, pinned).
// It is a virtual: slot 2 of ApplyRandomForceNugget's vtable 0x00BE0A00
// (installed by its ctor 0x001F01C8), the slot where the base vtable
// 0x00BE09D0 holds the rowed ObjectCreationNugget::create(const Object *,
// const Object *, UnsignedInt) const at 0x001F0132, so it overrides that
// overload (the one this tree's ObjectCreationList.cpp gives the nugget);
// +0x0 is the vptr and +0x25C of the primary object its physics pointer.
#include "../../../Libraries/Include/Lib/Coord3D.h"

struct Rva003909FAObj
{
	void consume(void *buf, int a, int b);
};

// The existing ObjectCreationList.cpp owner supplies this same native call.
void __cdecl calcRandomForce(float minMag, float maxMag,
	float minPitch, float maxPitch, Coord3D *force);

class Object;

struct Rva001F01F1Primary
{
	char m_pad[0x25C];
	Rva003909FAObj *m_obj;
};

class ApplyRandomForceNugget
{
public:
	virtual void create(const Object *primary, const Object *secondary, unsigned int lifetimeFrames) const;
	float m_04;
	float m_08;
	float m_0C;
	float m_10;
};

void ApplyRandomForceNugget::create(const Object *primary, const Object *, unsigned int) const
{
	if (primary == 0)
		return;
	Rva003909FAObj *obj = ((const Rva001F01F1Primary *)primary)->m_obj;
	if (obj == 0)
		return;
	Coord3D force;
	calcRandomForce(m_04, m_08, m_0C, m_10, &force);
	obj->consume(&force, 0, 0);
}
