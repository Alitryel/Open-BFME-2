// cl: /DNDEBUG /MD
//
// ?rva0049CD24@ProductionUpdate@@QAEXPAVObject@@@Z @0x0049CD24 43B.
// When the argument, the pointer at this+8, and the dword at that
// object's +0x45C are all nonzero, forwards them to GameLogic::rva0023D0C2.
// TheGameLogic is the global at VA 0x00DFE78C.

class Object;

class Holder
{
public:
	char m_pad[0x45C];
	int m_handle;
};

#include "GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class ProductionUpdate
{
public:
	void rva0049CD24(Object *obj);

private:
	char m_pad[8];
	Holder *m_holder;
};

void ProductionUpdate::rva0049CD24(Object *obj)
{
	if (obj == 0)
		return;
	Holder *holder = m_holder;
	if (holder == 0)
		return;
	int handle = holder->m_handle;
	if (handle == 0)
		return;
	TheGameLogic->rva0023D0C2(obj, handle);
}
