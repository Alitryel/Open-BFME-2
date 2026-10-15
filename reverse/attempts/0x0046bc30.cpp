// ?rva0046BC30@HordeContain@@UAEXXZ
// partial score=0.9625 date=2026-10-15
// cl: (home unit) Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
// Drop-in for the home unit, not a standalone TU (the unit is 146 KB):
//  1. in the +0x11C interface replace `virtual void gap50() = 0;` with
//     `virtual void rva0046BC30() = 0;`
//  2. in class HordeContain add `virtual void rva0046BC30();` before rva0046BD70
//  3. paste this block just before the rva0046BD70 definition.
// Measured there: size-exact 320, 8 differing lines (score 0.9625).
// ?rva0046BC30@HordeContain@@UAEXXZ @0x0046BC30: slot 50; while no +0x2A0
// target is set and the Object has a goal, moves every live contained Object
// (slot 70 walk) to the goal plus its +0x188 record offset rotated by the
// goal angle, on the goal layer (0x0028ACEE). The rotation is WWMath's
// Coord2D::Rotate(angle) (BFME1 coord2d.cpp): float sin/cos, then the hardware
// FSINCOS pair retail keeps after both CRT calls.
struct Rva0046BC30Offset : public Coord2D
{
	__forceinline void Rotate(float angle)
	{
		struct TrigValues
		{
			float sine;
			float cosine;
		} trig;

		trig.sine = sin(angle);
		trig.cosine = cos(angle);
		__asm {
			fld angle
			fsincos
			fstp trig.cosine
			fstp trig.sine
		}

		float ox = x;
		float oy = y;
		x = trig.cosine * ox - trig.sine * oy;
		y = trig.cosine * oy;
		y += trig.sine * ox;
	}
};


// partial score=0.9121 date=2026-10-15
// Home unit: Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
// (this bank is a fragment of it; its // cl: flags apply). To rebuild:
//  1. in Rva0046BB38Iface11C rename slot 50 `virtual void gap50() = 0;` to
//     `virtual void rva0046BC30() = 0;`
//  2. in class HordeContain add `virtual void rva0046BC30();` (after rva00468B5B)
//  3. insert the code below before the rva00468B5B definition.
// Measured there: 320/320 B, nd8 (rotation-product register roles only).
// ?rva0046BC30@HordeContain@@UAEXXZ @0x0046BC30: slot 50 (iface +0xC8). Without a
// pending order (+0x2A0), moves every live member to the goal position plus its
// +0x188 record offset rotated by the goal angle, on the goal layer.
struct Rva0046BC30Offset
{
	float x, y;
};
void HordeContain::rva0046BC30()
{
	if (m_2A0 != 0)
		return;
	Coord3D goal;
	if (!m_object->GetGoalPosition(&goal))
		return;
	float angle = m_object->GetGoalAngle();
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
	{
		Object *obj = *it;
		if (obj->isEffectivelyDead())
			continue;
		int index = ((Rva0046ACF6 *)(UpdateModule *)this)->rva0046ACF6(obj->getID());
		Rva0046BC30Offset offset;
		const Coord2D *src = reinterpret_cast<const Coord2D *>(&m_188Begin[index].m_04);
		offset.x = src->x;
		offset.y = src->y;
		offset.Rotate(angle);

		const Rva0046BC30Offset *src = (const Rva0046BC30Offset *)((const char *)&m_188Begin[index] + 4);
		offset.x = src->x;
		offset.y = src->y;
		struct { float sine; float cosine; } trig;
		trig.sine = (float)sin((double)angle);
		trig.cosine = (float)cos((double)angle);
		__asm
		{
			fld angle
			fsincos
			fstp trig.cosine
			fstp trig.sine
		}
		float tx = offset.x;
		offset.x = trig.cosine * tx - trig.sine * offset.y;
		offset.y = trig.sine * tx + trig.cosine * offset.y;
		Coord3D pos;
		pos.x = goal.x + offset.x;
		pos.y = goal.y + offset.y;
		pos.z = goal.z;
		obj->rva0028ACEE((int)&pos, m_object->GetGoalLayer());
	}
}

