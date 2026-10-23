// cl: /O1 /MD
// ??0Rva00545DB0@@QAE@PAVStateMachine@@@Z @ 0x00545DB0 28B
// Derived ctor: base Rva00342EAC plus vtable 0x0086A1F0 and dword 0x54 zero.
// Evidence: retail vtable store plus and [esi+0x54],0; callee row ??0Rva00342EAC@@QAE@PAVStateMachine@@@Z; caller 0x0054605A.
class StateMachine;
class Rva00342EAC
{
public:
	Rva00342EAC(StateMachine *machine);
};
// The retail table at RVA 0x0086A1F0: 18 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GAIFollowWaypointPathExactState@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Rva00545DCCGet@@YAHXZ")();
void __identifier("?xfer@AITNGuardReturnState@@MAEXPAVXfer@@@Z")();
void __identifier("?onEnter@AITNGuardReturnState@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?rva00545CAA@Rva00545CAA@@QAEXW4StateExitType@@@Z")();
void __identifier("?update@AITNGuardReturnState@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?disable@Rva0033F2D7ByteSetter@@QAEXXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?computePath@AIInternalMoveToState@@MAE_NXZ")();
}
extern const void *const g_00C6A1F0[18] = {
	(const void *)&__identifier("??_GAIFollowWaypointPathExactState@@UAEPAXI@Z"), // slot 0 0x00346CFB
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?Rva00545DCCGet@@YAHXZ"), // slot 2 0x00545DCC
	(const void *)&__identifier("?xfer@AITNGuardReturnState@@MAEXPAVXfer@@@Z"), // slot 3 0x00545C1D
	(const void *)&__identifier("?onEnter@AITNGuardReturnState@@UAE?AW4StateReturnType@@XZ"), // slot 4 0x005465E5
	(const void *)&__identifier("?rva00545CAA@Rva00545CAA@@QAEXW4StateExitType@@@Z"), // slot 5 0x00545CAA
	(const void *)&__identifier("?update@AITNGuardReturnState@@UAE?AW4StateReturnType@@XZ"), // slot 6 0x00545C4D
	(const void *)&__identifier("?disable@Rva0033F2D7ByteSetter@@QAEXXZ"), // slot 7 0x0033F2D7
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 8 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 9 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 11 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 12 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 13 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 14 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 15 0x0047A699
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 16 0x000B3FD0
	(const void *)&__identifier("?computePath@AIInternalMoveToState@@MAE_NXZ"), // slot 17 0x003441F7
};
class Rva00545DB0 : public Rva00342EAC
{
public:
	Rva00545DB0(StateMachine *machine);
private:
	char m_pad[0x54 - sizeof(Rva00342EAC)];
	int m_54;
};
Rva00545DB0::Rva00545DB0(StateMachine *machine) : Rva00342EAC(machine)
{
	m_54 = 0;
	*(const void **)this = g_00C6A1F0;
}
