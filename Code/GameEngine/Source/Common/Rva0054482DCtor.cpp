// cl: /MD
// ??0Rva0054482D@@QAE@PAVStateMachine@@@Z, retail 0x0054482D, 29 bytes.
// Derived AIInternalMoveToState ctor via pinned base ctor 0x0033F279 with hash
// 0x58821EDA then vtable 0x00C69B58. Evidence: vtable store at [this]; base
// AIInternalMoveToState ctor pin; caller 0x0054497B in 0x005448A1; prev/next
// ConstIntGetters4 same dir.
class StateMachine;

class __declspec(novtable) AIInternalMoveToState
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
};

// The retail table at RVA 0x00869B58: 18 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GAIFollowWaypointPathExactState@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?name@Rva0033F2F7Named@@QBEPBDXZ")();
void __identifier("?xfer@AIInternalMoveToState@@MAEXPAVXfer@@@Z")();
void __identifier("?onEnter@Rva0054482D@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?onExit@Rva0054482D@@UAEXW4StateExitType@@@Z")();
void __identifier("?update@Rva0054482D@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?disable@Rva0033F2D7ByteSetter@@QAEXXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?computePath@AIInternalMoveToState@@MAE_NXZ")();
}
extern const void *const g_00C69B58[18] = {
	(const void *)&__identifier("??_GAIFollowWaypointPathExactState@@UAEPAXI@Z"), // slot 0 0x00346CFB
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?name@Rva0033F2F7Named@@QBEPBDXZ"), // slot 2 0x0033F2F7
	(const void *)&__identifier("?xfer@AIInternalMoveToState@@MAEXPAVXfer@@@Z"), // slot 3 0x0033FF76
	(const void *)&__identifier("?onEnter@Rva0054482D@@UAE?AW4StateReturnType@@XZ"), // slot 4 0x00544364
	(const void *)&__identifier("?onExit@Rva0054482D@@UAEXW4StateExitType@@@Z"), // slot 5 0x00544425
	(const void *)&__identifier("?update@Rva0054482D@@UAE?AW4StateReturnType@@XZ"), // slot 6 0x005443ED
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

class Rva0054482D : public AIInternalMoveToState
{
public:
	Rva0054482D(StateMachine *machine);
};

Rva0054482D::Rva0054482D(StateMachine *machine) : AIInternalMoveToState(machine, 0x58821EDAu)
{
	*(const void **)this = g_00C69B58;
}
