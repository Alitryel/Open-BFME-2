// ?rva0046BEAC@HordeContain@@UAEXPAVObject@@@Z
// partial score=0.99 date=2026-10-15
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /D_CRTIMP= /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7 /Ireference/shims/bfmelist /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
// BANK for 0x0046BEAC (863 B): insert into
// Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
// before "// The +0x20 contain interface (vtable 0x00C44EC8) as its slots see it",
// with these declaration edits in that unit:
//  - Rva0046BB38Iface11C: `virtual void gap38() = 0;` -> `virtual void rva0046BEAC(Object *obj) = 0;`
//  - HordeContain: add `virtual void rva0046BEAC(Object *obj);` before rva0046BD70
//  - Pathfinder: add `bool IsValidMovementPositionForObject(const Coord3D *pos, int layer, int surfaces, const Object *obj);`
//  - AI: add `Pathfinder *pathfinder() { return m_pathfinder; }`
//  - Object: add `void rva0028B4CE(PathfindLayerEnum layer);` after rva0028B511
// Compiled in that unit: 863/863, only the first addss of the contained-list
// centre loop has its operands swapped against retail.
// The locomotor set's valid-surfaces mask (+0x10), as the slot-38 walk reads it.
struct LocomotorSetSurfacesView
{
	unsigned char m_pad00[0x10];
	int m_validLocomotorSurfaces; // +0x10
};
// ?rva0046BEAC@HordeContain@@UAEXPAVObject@@@Z @0x0046BEAC: slot 38 (WB twin
// 0x010C3050): averages the positions of the live +0x170 key Objects that pass
// 0x00290FBB and of every contained Object (slot 70), then moves the given
// Object to the member position closest to that center (contained members
// only where the pathfinder accepts the spot for the given Object's layer and
// locomotor surfaces) and gives it that member's layer (default ground).
void HordeContain::rva0046BEAC(Object *obj)
{
	Coord3D center;
	center.zero();
	int count = 0;
	int layer = 1;
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *member = TheGameLogic->findObjectByID((ObjectID)*k);
		if (member && member->rva00290FBB())
		{
			center.add(member->getPosition());
			++count;
		}
	}
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
	{
		Object *member = *it;
		if (member)
		{
			center.add(member->getPosition());
			++count;
		}
	}
	if (count > 0)
	{
		float bestDist = -1.0f;
		center.scale(1.0f / count);
		Coord3D bestPos;
		bestPos.set(obj->getPosition());
		for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
		{
			Object *member = TheGameLogic->findObjectByID((ObjectID)*k);
			if (member && member->rva00290FBB())
			{
				Coord3D pos;
				pos.set(member->getPosition());
				Coord3D delta;
				delta.set(&pos);
				delta.sub(&center);
				if (bestDist < 0.0f || delta.lengthSqr() < bestDist)
				{
					bestPos = pos;
					bestDist = delta.lengthSqr();
					layer = member->rva0028B511();
				}
			}
		}
		for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
		{
			Object *member = *it;
			Coord3D pos;
			pos.set(member->getPosition());
			AIUpdateInterface *ai = obj->m_ai;
			int surfaces = ((const LocomotorSetSurfacesView *)&ai->getLocomotorSet())->m_validLocomotorSurfaces;
			if (TheAI->pathfinder()->IsValidMovementPositionForObject(&pos, obj->rva0028B511(), surfaces, obj))
			{
				Coord3D delta;
				delta.set(&pos);
				delta.sub(&center);
				if (bestDist < 0.0f || delta.lengthSqr() < bestDist)
				{
					bestPos = pos;
					bestDist = delta.lengthSqr();
					layer = member->rva0028B511();
				}
			}
		}
		((Thing *)obj)->setPosition(&bestPos);
		obj->rva0028B4CE((PathfindLayerEnum)layer);
	}
}

