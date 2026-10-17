// cl: /MD
// ??0Rva0054484A@@QAE@PAVStateMachine@@@Z, retail 0x0054484A, 29 bytes.
// Derived AIInternalMoveToState ctor via pinned base ctor 0x0033F279 with hash
// 0x493559EF then vtable 0x00C69BA0. Evidence: vtable store at [this]; base
// AIInternalMoveToState ctor pin; caller 0x005449AC in 0x005448A1; prev
// 0x0054482D same dir.
class StateMachine;

class __declspec(novtable) AIInternalMoveToState
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
};

// The retail table at RVA 0x00869BA0: 18 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GAIFollowWaypointPathExactState@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?name@Rva0033F2F7Named@@QBEPBDXZ")();
void __identifier("?xfer@AIInternalMoveToState@@MAEXPAVXfer@@@Z")();
void __identifier("?onEnter@Rva0054484A@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?onExit@Rva0054484A@@UAEXW4StateExitType@@@Z")();
void __identifier("?update@Rva0054484A@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?disable@Rva0033F2D7ByteSetter@@QAEXXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?computePath@AIInternalMoveToState@@MAE_NXZ")();
}
extern const void *const g_00C69BA0[18] = {
	(const void *)&__identifier("??_GAIFollowWaypointPathExactState@@UAEPAXI@Z"), // slot 0 0x00346CFB
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?name@Rva0033F2F7Named@@QBEPBDXZ"), // slot 2 0x0033F2F7
	(const void *)&__identifier("?xfer@AIInternalMoveToState@@MAEXPAVXfer@@@Z"), // slot 3 0x0033FF76
	(const void *)&__identifier("?onEnter@Rva0054484A@@UAE?AW4StateReturnType@@XZ"), // slot 4 0x00544480
	(const void *)&__identifier("?onExit@Rva0054484A@@UAEXW4StateExitType@@@Z"), // slot 5 0x00544572
	(const void *)&__identifier("?update@Rva0054484A@@UAE?AW4StateReturnType@@XZ"), // slot 6 0x0054452A
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

class Rva0054484A : public AIInternalMoveToState
{
public:
	Rva0054484A(StateMachine *machine);
};

Rva0054484A::Rva0054484A(StateMachine *machine) : AIInternalMoveToState(machine, 0x493559EFu)
{
	*(const void **)this = g_00C69BA0;
}
