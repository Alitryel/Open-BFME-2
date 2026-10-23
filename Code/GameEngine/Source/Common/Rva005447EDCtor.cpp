// cl: /MD
// ??0Rva005447ED@@QAE@PAVStateMachine@@@Z, retail 0x005447ED, 29 bytes.
// Derived AIInternalMoveToState ctor via pinned base ctor 0x0033F279 with hash
// 0x26F20F3B then vtable 0x00869AB0. Evidence: vtable store at [this]; base
// AIInternalMoveToState ctor pin; caller 0x005448E3 in 0x005448A1; prev/next
// ConstIntGetters4 same dir.
class StateMachine;

class __declspec(novtable) AIInternalMoveToState
{
public:
	AIInternalMoveToState(StateMachine *machine, unsigned int hash);
};

// The retail table at RVA 0x00869AB0: 18 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GAIFollowWaypointPathExactState@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Rva0054480AGet@@YAHXZ")();
void __identifier("?xfer@AIDockApproachState@@MAEXPAVXfer@@@Z")();
void __identifier("?onEnter@Rva005447ED@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?onExit@AIDockApproachState@@UAEXW4StateExitType@@@Z")();
void __identifier("?update@AIDockApproachState@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?disable@Rva0033F2D7ByteSetter@@QAEXXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?computePath@AIInternalMoveToState@@MAE_NXZ")();
}
extern const void *const g_00C69AB0[18] = {
	(const void *)&__identifier("??_GAIFollowWaypointPathExactState@@UAEPAXI@Z"), // slot 0 0x00346CFB
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?Rva0054480AGet@@YAHXZ"), // slot 2 0x0054480A
	(const void *)&__identifier("?xfer@AIDockApproachState@@MAEXPAVXfer@@@Z"), // slot 3 0x00341979
	(const void *)&__identifier("?onEnter@Rva005447ED@@UAE?AW4StateReturnType@@XZ"), // slot 4 0x00544133
	(const void *)&__identifier("?onExit@AIDockApproachState@@UAEXW4StateExitType@@@Z"), // slot 5 0x005441AF
	(const void *)&__identifier("?update@AIDockApproachState@@UAE?AW4StateReturnType@@XZ"), // slot 6 0x00544348
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

class Rva005447ED : public AIInternalMoveToState
{
public:
	Rva005447ED(StateMachine *machine);
};

Rva005447ED::Rva005447ED(StateMachine *machine) : AIInternalMoveToState(machine, 0x26F20F3Bu)
{
	*(const void **)this = g_00C69AB0;
}
