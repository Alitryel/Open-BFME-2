// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /Oy-
//
// ?update@MonitorConditionUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail 0x0049176C, 289 bytes.
// Slot 0 of MonitorConditionUpdate's +0x10 UpdateModuleInterface vftable
// 0x00C4DACC (this at +0x10, so the module data is [this-0xC] and the object
// [this-8], as in the rowed SlaughterHordeContain::update). Swaps the
// object's command-set override by condition: while the object's +0x10C
// mask overlaps the module data's +0x08 mask it uses the +0x54 set, while
// the object's +0x370 status set passes the data's +0x58 test it uses the
// +0x68 set; switching to either remembers the set it replaced (at +0x20,
// unless that was the other monitored set). With neither condition it
// restores the remembered set and clears it. Every change dirties
// TheControlBar (+0x28). Always UPDATE_SLEEP_NONE.
//
// Evidence (target): the vftable slot and this adjustment, the rowed
// callees (mask overlap 0x00263546, Object command-set string 0x00290E67,
// AsciiString compare/set, the +0x370 getter 0x0028B7AE and its test
// 0x00331682, Object::setCommandSetStringOverride 0x0029336F), the
// AsciiString at +0x20 the rowed constructor zeroes, TheControlBar +0x28.
// Data member names are descriptive; the condition fields' identities are
// structural inferences.

#include "ascii_string.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class Rva00263546
{
public:
	bool rva00263546(const Rva00263546 *other) const;
private:
	int m_mask[19];
};

class Rva00331682Holder
{
public:
	bool test(const void *other) const;
};

// Object +0x370 (rowed out-of-line lea getter).
class Rva0028B7AELeaGetter
{
public:
	void *get() const;
};

class Object
{
public:
	const AsciiString *rva00290E67() const;
	void setCommandSetStringOverride(const AsciiString &newCommandSet);
	const Rva00263546 *getMask10C() const { return &m_mask10C; }
	const Rva00331682Holder *getStatus370() const
	{
		return (const Rva00331682Holder *)((const Rva0028B7AELeaGetter *)this)->get();
	}
private:
	unsigned char m_pad000[0x10C];
	Rva00263546 m_mask10C; // +0x10C
};

class ControlBar
{
public:
	void markUIDirty() { m_UIDirty = true; }
private:
	unsigned char m_pad00[0x28];
	bool m_UIDirty; // +0x28
};
extern ControlBar *TheControlBar;

struct MonitorConditionUpdateModuleData
{
	unsigned char m_pad00[0x08];
	Rva00263546 m_mask;              // +0x08
	AsciiString m_maskCommandSet;    // +0x54
	unsigned char m_status[0x10];    // +0x58
	AsciiString m_statusCommandSet;  // +0x68
};

struct Iface00
{
	virtual void f00();
	const MonitorConditionUpdateModuleData *m_moduleData; // +0x04
	Object *m_object;                                     // +0x08
};
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual UpdateSleepTime update() = 0; };

class MonitorConditionUpdate : public Iface00, public Iface0C, public Iface10
{
public:
	virtual UpdateSleepTime update();
private:
	unsigned char m_pad14[0x20 - 0x14];
	AsciiString m_rememberedCommandSet; // +0x20
};

// ?update@MonitorConditionUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x0049176C
UpdateSleepTime MonitorConditionUpdate::update()
{
	const MonitorConditionUpdateModuleData *d = m_moduleData;
	Object *obj = m_object;
	if (obj == 0 || d == 0)
		return UPDATE_SLEEP_NONE;

	if (obj->getMask10C()->rva00263546(&d->m_mask))
	{
		const AsciiString *current = obj->rva00290E67();
		if (current->compare(d->m_maskCommandSet) == 0)
			return UPDATE_SLEEP_NONE;
		current = obj->rva00290E67();
		if (current->compare(d->m_statusCommandSet) != 0)
			m_rememberedCommandSet.set(*obj->rva00290E67());
		obj->setCommandSetStringOverride(d->m_maskCommandSet);
		TheControlBar->markUIDirty();
	}
	else
	{
	const Rva00331682Holder *status = obj->getStatus370();
	if (status->test(d->m_status))
	{
		const AsciiString *current = obj->rva00290E67();
		if (current->compare(d->m_statusCommandSet) == 0)
			return UPDATE_SLEEP_NONE;
		current = obj->rva00290E67();
		if (current->compare(d->m_maskCommandSet) != 0)
			m_rememberedCommandSet.set(*obj->rva00290E67());
		obj->setCommandSetStringOverride(d->m_statusCommandSet);
		TheControlBar->markUIDirty();
	}
	else
	{
		if (m_rememberedCommandSet.compare(AsciiString::TheEmptyString) == 0)
			return UPDATE_SLEEP_NONE;
		if (m_rememberedCommandSet.compare(*obj->rva00290E67()) == 0)
			return UPDATE_SLEEP_NONE;
		obj->setCommandSetStringOverride(m_rememberedCommandSet);
		m_rememberedCommandSet.set(AsciiString::TheEmptyString);
		TheControlBar->markUIDirty();
	}
	}
	return UPDATE_SLEEP_NONE;
}
