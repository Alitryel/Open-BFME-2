// cl: /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ??1DelayedExperienceLevelGrantSystem@@UAE@XZ retail 0x00420E67 76B.
// MI dtor in the shape of Rva002D3573Dtor.cpp: primary SubsystemInterface
// (size 0xC) at +0 with vtable 0x00C3BDC4, secondary Snapshot at +0xC with
// vtable 0x00C3BDB4 restored to 0x00BBB554 by the inline Snapshot dtor, a
// member at +0x10 destroyed through 0x004EC395 (the folded _List_base dtor),
// then the rowed ??1SubsystemInterface@@UAE@XZ at 0x001B4E74. The
// snapped-boundary queue named it FXListStore's dtor; that identity is not
// established, so the class and member names are generated.

class Rva004EC395Member
{
public:
	~Rva004EC395Member();
private:
	char m_pad[8];
};

// Keep the subsystem vtable shape consistent with the paired constructor.
typedef bool Bool;
#include "subsystem_interface.h"

#include "Common/Snapshot.h"

class DelayedExperienceLevelGrantSystem : public SubsystemInterface, public Snapshot
{
public:
	virtual ~DelayedExperienceLevelGrantSystem();
private:
	Rva004EC395Member m10;
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline DelayedExperienceLevelGrantSystem::~DelayedExperienceLevelGrantSystem()
{
}

// ?bfmeAnchorRva00420E67Dtor absent-from-retail
void bfmeAnchorRva00420E67Dtor(DelayedExperienceLevelGrantSystem *p)
{
	p->DelayedExperienceLevelGrantSystem::~DelayedExperienceLevelGrantSystem();
}
