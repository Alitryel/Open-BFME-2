// ?rva0049176C@Rva0049176C@@QAE_NXZ
// partial score=0.7 date=2026-10-14
// cl: /O1 /Oy- /arch:SSE /G7 /EHsc /MD /Ireference/shims/bfme2_ascii /DNDEBUG
// ?rva0049176C@Rva0049176C@@QAE_NXZ @0x0049176C 289B: command-set switch of an upgrade module (slot
// 31 of the module's secondary base, so the module data sits at this-0xC and the object at
// this-8). While the object's current set is not already the target, the matching target set
// (up at data+0x54 or alternate at data+0x68, chosen by the overlap tests of the object's flags
// against the data masks) is installed, remembering the previous set in the string at this+0x10
// unless it is the other target; when neither test holds the remembered set is restored and
// cleared. Marks the control bar dirty. Layout views are neutral.
#include "ascii_string.h"

class Rva00263546
{
public:
	bool rva00263546(const Rva00263546 *other) const;
};

class Rva0028B7AELeaGetter { public: void *get() const; };
class Rva00331682Holder { public: bool test(const void *mask) const; };

class Object
{
public:
	const AsciiString *rva00290E67() const;
	void setCommandSetStringOverride(const AsciiString &set);
	char m_pad00[0x10C];
	Rva00263546 m_flags;
};

struct ControlBarView { char m_pad[0x28]; unsigned char m_dirty; };
extern ControlBarView *TheControlBar;

struct Rva0049176CData
{
	char m_pad00[8];
	Rva00263546 m_flagMask;
	char m_padMask[0x54 - 8 - sizeof(Rva00263546)];
	AsciiString m_setUp;
	char m_mask58[0x68 - 0x54 - sizeof(AsciiString)];
	AsciiString m_setAlt;
};

class Rva0049176C
{
public:
	bool rva0049176C();
	char m_pad00[0x10];
	AsciiString m_old;
};

struct Rva0049176CHolder
{
	Rva0049176CData *m_data;
	Object *m_object;
	Rva0049176C m_sub;
};

bool Rva0049176C::rva0049176C()
{
	Rva0049176CHolder *holder = reinterpret_cast<Rva0049176CHolder *>(reinterpret_cast<char *>(this) - 0xC);
	Object *object = holder->m_object;
	Rva0049176CData *data = holder->m_data;
	if (object && data)
	{
		const AsciiString *target;
		if (object->m_flags.rva00263546(&data->m_flagMask))
		{
			if (object->rva00290E67()->compare(*(target = &data->m_setUp)) == 0)
				return true;
			if (object->rva00290E67()->compare(data->m_setAlt) != 0)
				m_old.set(object->rva00290E67()->str());
		}
		else if (reinterpret_cast<Rva00331682Holder *>(reinterpret_cast<const Rva0028B7AELeaGetter *>(object)->get())->test(data->m_mask58))
		{
			if (object->rva00290E67()->compare(*(target = &data->m_setAlt)) == 0)
				return true;
			if (object->rva00290E67()->compare(data->m_setUp) != 0)
				m_old.set(object->rva00290E67()->str());
		}
		else
		{
			if (m_old.compare(AsciiString::TheEmptyString) == 0)
				return true;
			if (m_old.compare(*object->rva00290E67()) == 0)
				return true;
			object->setCommandSetStringOverride(m_old);
			m_old.set(AsciiString::TheEmptyString.str());
			TheControlBar->m_dirty = 1;
			return true;
		}
		object->setCommandSetStringOverride(*target);
		TheControlBar->m_dirty = 1;
	}
	return true;
}
