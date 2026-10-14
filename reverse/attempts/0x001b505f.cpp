// ?rva001B505F@SubsystemInterfaceList@@QAEEXZ
// partial score=0.85 date=2026-10-14
// cl: /O1 /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva001B505F@SubsystemInterfaceList@@QAEEXZ @0x001B505F 225B
// Sibling of the rowed 0x001B5140 collector over the same two arrays (8-byte entries at +0/+4, pointers at
// +0xC/+0x10): every non-null entry is offered to the rowed 0x001B4E21 helper (virtual slot 4 under a guard
// byte), a success flags the result, and the entry is collected in a local vector; the collected entries then
// each get virtual slot 7 called with the helper's flag byte, and the rowed Rva0002BBC9Update runs when
// anything succeeded. Evidence: target bytes; callers of 0x001B4E21 are exactly this body; pin comment on the
// member returning a byte its caller normalises (GameEngine slot 16). Roles of the entries are unproven.
#include <vector>

class ModuleData;

class Rva001B5140Pred
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual void vf4();
	virtual void vf5();
	virtual void vf6();
	virtual void vf7(unsigned char flag);
};

struct Rva001B505FEntry8
{
	Rva001B5140Pred *m_obj;
	int m_pad;
};

void Rva0002BBC9Update();

class SubsystemInterfaceList
{
public:
	unsigned char rva001B505F();
	unsigned char Rva001B4E21Get(void *arg1, void *arg2);

private:
	Rva001B505FEntry8 *m_firstBegin;	// +0
	Rva001B505FEntry8 *m_firstEnd;	// +4
	void *m_pad8;
	Rva001B5140Pred **m_secondBegin;	// +0xC
	Rva001B5140Pred **m_secondEnd;	// +0x10
};

unsigned char SubsystemInterfaceList::rva001B505F()
{
	unsigned char any;
	unsigned char flag = any = 0;
	_STL::vector<const ModuleData *> collected;
	for (Rva001B505FEntry8 *p = m_firstBegin; p != m_firstEnd; ++p)
	{
		const ModuleData *obj = (const ModuleData *)p->m_obj;
		if (obj == 0)
			continue;
		if (Rva001B4E21Get((void *)obj, &flag))
			any = 1;
		collected.push_back(obj);
	}
	for (Rva001B5140Pred **q = m_secondBegin; q != m_secondEnd; ++q)
	{
		const ModuleData *obj = (const ModuleData *)*q;
		if (obj == 0)
			continue;
		if (Rva001B4E21Get((void *)obj, &flag))
			any = 1;
		collected.push_back(obj);
	}
	for (_STL::vector<const ModuleData *>::iterator it = collected.begin(); it != collected.end(); ++it)
	{
		if (*it)
			((Rva001B5140Pred *)*it)->vf7(flag);
	}
	if (any)
		Rva0002BBC9Update();
	return any;
}
