// ?rva0046D2C3@HordeContain@@UAEPAVObject@@H@Z
// partial score=0.91 date=2026-10-15
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /D_CRTIMP= /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7 /Ireference/shims/bfmelist /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
// d3 seat2 bank: append to Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
// after these edits in that unit:
//  - interface: replace `virtual void gap69() = 0;` with `virtual Object *rva0046D2C3(int kind) = 0;`
//  - HordeContain: declare `virtual Object *rva0046D2C3(int kind);` after rva0046D27A
//  - before class ThingTemplate: `enum KindOfType { KINDOF_FIRST = 0 };`; in ThingTemplate:
//    `bool isKindOf(KindOfType t) const;` (pinned ?isKindOf@ThingTemplate@@QBE_NW4KindOfType@@@Z 0x456AC)
//  - Object: `const ThingTemplate *getTemplate() const { return m_template; }` and
//    `bool isKindOf(KindOfType t) const { return getTemplate()->isKindOf(t); }`
// Result: 175B size-exact, nd20: only this (ours EBX, retail EDI) / cursor+obj (ours EDI, retail EBX) swap.

Object *HordeContain::rva0046D2C3(int kind)
{
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	_STL::list<Object *>::const_iterator end = p.m04->end();
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != end; ++it)
	{
		if (!(*it)->isKindOf((KindOfType)kind))
			return *it;
	}
	_STL::list<Object *>::const_iterator front = end;
	++front;
	if (front != end)
		return *front;
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && !obj->isKindOf((KindOfType)kind))
			return obj;
	}
	_STL::set<int>::iterator first = m_170.begin();
	if (first != m_170.end())
		return TheGameLogic->findObjectByID((ObjectID)*first);
	return 0;
}
