// ?f@Rva0026DF0D@@QAEXPAVObject@@HH@Z
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?f@Rva0026DF0D@@QAEXPAVObject@@HH@Z
// ?f@Rva0026DF0D@@QAEXPAVObject@@HH@Z
// ?f@Rva0026DF0D@@QAEXPAVObject@@HH@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// AIUpdateInterface-adjacent command/locomotor queue insert at 0x0026DF0D
// (359 B, RET 0xC). The +0x24 subobject is the AIUpdateInterface; its object at
// -0x1C is the controlled Object. Rejects while g_00DFE7A8 is set, the two
// +0x396/+0x397 gates are up, or the object frame +0x154 runs ahead of the
// game frame; then the relation filters, the +0x74 key search over the int
// arrays at +0x180/+0x184 and the +0x190/+0x194 age arrays, and finally the
// AIUpdateInterface 0x26CF11/0x262989 pair. All callees rowed; the two globals
// are the ledger's own TheGameLogic and g_00DFE7A8.
class Object;
class ObjectView { public: char m_pad[0x113]; unsigned char m_113; };
enum Relationship { RELATIONSHIP_ENUM_BASE = 0 };
enum ObjectStatusTypes { STATUS_3B = 0x3b };
class Object
{
public:
	bool rva002931BA();
	bool testStatus(ObjectStatusTypes status) const;
	enum Relationship getRelationship(const Object *other) const;
	Object *rva0028ACA0() const;
private:
	char m_pad004[0x74 - 0x04];
	int m_074;			// +0x74
	char m_pad078[0x274 - 0x78];
	Object *m_274;			// +0x274
};
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
extern unsigned char g_00DFE7A8;

class AIUpdateInterface
{
public:
	bool rva0026CF11(Object *obj);
	void rva00262989(unsigned value);
};

class Rva0026DF0D
{
public:
	void f(Object *obj, int b, int c);
};

void Rva0026DF0D::f(Object *obj, int b, int c)
{
	if (obj == 0)
		return;
	if (g_00DFE7A8 != 0)
		return;
	if (*(unsigned char *)((char *)this + 0x396) != 0)
		return;
	if (*(unsigned char *)((char *)this + 0x397) != 0)
		return;
	if (*(unsigned *)((char *)this + 0x154) > TheGameLogic->getFrame())
		return;
	Object *self = *(Object **)((char *)this - 0x1c);
	if (self->rva002931BA())
		return;
	if (obj->rva002931BA())
		return;
	if ((*(ObjectView **)((char *)self + 4))->m_113 & 0x20)
	{
		if (self->testStatus(STATUS_3B))
			return;
	}
	if (self->getRelationship(obj) != 0)
		return;
	Object *rel = self->rva0028ACA0();
	if (rel != 0)
	{
		if (obj == rel)
			return;
		if (*(Object **)((char *)obj + 0x274) == rel)
			return;
	}
	rel = obj->rva0028ACA0();
	if (rel != 0)
	{
		if (self == rel)
			return;
		if (*(Object **)((char *)self + 0x274) == rel)
			return;
	}
	int key = *(int *)((char *)obj + 0x74);
	int i = 0;
	if (*(unsigned *)((char *)this + 0x1a4) > 0)
	{
		int *p = (int *)((char *)this + 0x184);
		do
		{
			if (*p == key)
				break;
			++i;
			++p;
		} while (i < *(volatile unsigned *)((char *)this + 0x1a4));
	}
	if ((unsigned)i < *(unsigned *)((char *)this + 0x1a4))
	{
		int *slot = (int *)((char *)this + 0x194 + i * 4);
		if (*slot + 1 == TheGameLogic->getFrame())
		{
			*slot = *slot + 1;
			return;
		}
		*slot = *(int *)((char *)this + 0x190 + *(unsigned *)((char *)this + 0x1a4) * 4);
		*(int *)((char *)this + 0x184 + i * 4) = *(int *)((char *)this + 0x180 + *(unsigned *)((char *)this + 0x1a4) * 4);
		(*(unsigned *)((char *)this + 0x1a4))--;
	}
	AIUpdateInterface *ai = (AIUpdateInterface *)((char *)this - 0x24);
	if (ai->rva0026CF11(obj))
		ai->rva00262989(key);
}
