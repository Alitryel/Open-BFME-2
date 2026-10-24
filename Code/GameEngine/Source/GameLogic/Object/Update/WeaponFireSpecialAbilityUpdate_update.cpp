// ?update@WeaponFireSpecialAbilityUpdate@@UAE?AW4UpdateSleepTime@@XZ
// /arch:SSE comes from retail region flags (0x1D8E99..0x60273F: O1/SSE/G7); the holder local is load-bearing (reads owner->m_holder once, before the null tests).
// cl: /O1 /arch:SSE /G7 /Oy- /DNDEBUG /MD /ICode/Libraries/Include
//
// ?update@WeaponFireSpecialAbilityUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x00492BEB 110B.
// Slot 0 of WeaponFireSpecialAbilityUpdate's UpdateModuleInterface vtable
// (0x00C4E080 at +0x10, stored by the matched dtor 0x0049256B), where
// SpecialAbilityUpdate's own table has SpecialAbilityUpdate::update 0x00451FA2
// and every named sibling has update; the body ends by tail-calling that base.
// It is compiled with the +0x10 subobject this (members at this-8 and +0x20).
// When the mode (+0x30) is 2, look up the id at +0x40. If that object, the
// owner (+0x08), its pointer at +0x258, and the pointer at +0x1F0 of that
// are all live, copy the found position at +0x38 into a stack Coord3D and
// pass it to 0x001E702E.

#include "../../../Common/GameLogicObjectLookupView.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0
};

#include "Lib/Coord3D.h"

class Object;
class Thing;

class Rva001E702E
{
public:
	void rva001E702E(Thing *obj, int pos, int flag);
};

class Rva00492BEBHolder
{
public:
	char m_pad[0x1F0];
	Rva001E702E *m_inner;
};

class Object
{
public:
	char m_pad[0x38];
	Coord3D m_pos;
	char m_pad44[0x258 - 0x44];
	Rva00492BEBHolder *m_holder;
};

extern GameLogic *TheGameLogic;

class ModuleData;

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
};

class SpecialAbilityUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
protected:
	char m_pad14[0x30 - 0x14];
	int m_mode;			// +0x30
	char m_pad34[0x40 - 0x34];
	ObjectID m_id;			// +0x40
};

class WeaponFireSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	virtual UpdateSleepTime update();
};

UpdateSleepTime WeaponFireSpecialAbilityUpdate::update()
{
	if (m_mode == 2)
	{
		Object *owner = m_object;
		Object *found = TheGameLogic->findObjectByID(m_id);
		Rva00492BEBHolder *holder = owner->m_holder;
		if (found != 0 && owner->m_holder != 0)
		{
			Coord3D pos;
			pos.x = found->m_pos.x;
			pos.y = found->m_pos.y;
			pos.z = found->m_pos.z;
			if (holder->m_inner != 0)
				holder->m_inner->rva001E702E((Thing *)owner, (int)&pos, 0);
		}
	}
	return SpecialAbilityUpdate::update();
}
