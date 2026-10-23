// cl: /MD /EHsc
// ??0Rva00342EAC@@QAE@PAVStateMachine@@@Z @0x00342EAC 37B: AIInternalMoveToState-derived ctor, hash 0x822AD648, vtable 0x00812E90, dwords 0x4C 0x50 zero via and.
// Donor Code/GameEngine/Source/GameLogic/AI/AIStatesSmallUpdates.cpp AIFollowWaypointPathExactState ctor pattern (base + vtable + members).
// Callers 0x00343C08 0x0035251C 0x00545DB7 unclaimed.
class StateMachine;
#include "../../../Libraries/Include/Lib/Coord3D.h"
class State
{
public:
	virtual ~State();
	virtual void slot01();
	virtual void slot02();
	virtual void xfer();
	virtual int onEnter();
	virtual void onExit();
	virtual int update();
protected:
	unsigned char m_pad04[0x18 - 0x04];
	StateMachine *m_machine;
};
class AIInternalMoveToState : public State
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
	virtual ~AIInternalMoveToState();
	virtual void xfer();
	virtual int onEnter();
	virtual void onExit();
	virtual int update();
protected:
	unsigned char m_pad1C[0x20 - 0x1C];
	Coord3D m_goalPosition;
	unsigned char m_pad2C[0x48 - (0x20 + sizeof(Coord3D))];
	bool m_adjustsDestination;
};
class Rva00342EAC : public AIInternalMoveToState
{
public:
	Rva00342EAC(StateMachine *machine);
private:
	int m_4C;
	int m_50;
};
Rva00342EAC::Rva00342EAC(StateMachine *machine)
	: AIInternalMoveToState(machine, 0x822AD648u)
{
	m_4C = 0;
	m_50 = 0;
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?onEnter@AIInternalMoveToState@@UAEHXZ=?onEnter@AIEnterState@@UAE?AW4StateReturnType@@XZ")
#pragma comment(linker, "/alternatename:?onExit@AIInternalMoveToState@@UAEXXZ=?onExit@AIEnterState@@UAEXW4StateExitType@@@Z")
#pragma comment(linker, "/alternatename:?update@AIInternalMoveToState@@UAEHXZ=?update@AIEnterState@@UAE?AW4StateReturnType@@XZ")
#pragma comment(linker, "/alternatename:?xfer@AIInternalMoveToState@@UAEXXZ=?xfer@Rva00341930@@MAEXPAVXfer@@@Z")
