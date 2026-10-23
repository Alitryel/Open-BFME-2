// cl: /MD
// ??0Rva00346CDD@@QAE@PAVStateMachine@@@Z, retail 0x00346CDD, 24 bytes.
// Evidence: calls rowed base ??0Rva0034005D@@QAE@PAVStateMachine@@@Z and stores
// vtable g_00C136A0, ret 4 single StateMachine arg. Vtable slot unknown.
class StateMachine;
class Rva0034005D
{
public:
	Rva0034005D(StateMachine *machine);
};
// The retail table at RVA 0x008136A0: 18 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GAIFollowWaypointPathExactState@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Rva00346CF5Get@@YAHXZ")();
void __identifier("?xfer@AIDockApproachState@@MAEXPAVXfer@@@Z")();
void __identifier("?onEnter@AIMoveToPositionAndEnterState@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?onExit@AIMoveToPositionAndEnterState@@UAEXW4StateExitType@@@Z")();
void __identifier("?update@AIMoveToPositionAndEnterState@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?disable@Rva0033F2D7ByteSetter@@QAEXXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?computePath@AIInternalMoveToState@@MAE_NXZ")();
}
extern const void *const g_00C136A0[18] = {
	(const void *)&__identifier("??_GAIFollowWaypointPathExactState@@UAEPAXI@Z"), // slot 0 0x00346CFB
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?Rva00346CF5Get@@YAHXZ"), // slot 2 0x00346CF5
	(const void *)&__identifier("?xfer@AIDockApproachState@@MAEXPAVXfer@@@Z"), // slot 3 0x00341979
	(const void *)&__identifier("?onEnter@AIMoveToPositionAndEnterState@@UAE?AW4StateReturnType@@XZ"), // slot 4 0x00350020
	(const void *)&__identifier("?onExit@AIMoveToPositionAndEnterState@@UAEXW4StateExitType@@@Z"), // slot 5 0x0034C035
	(const void *)&__identifier("?update@AIMoveToPositionAndEnterState@@UAE?AW4StateReturnType@@XZ"), // slot 6 0x00354945
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
class Rva00346CDD : public Rva0034005D
{
public:
	Rva00346CDD(StateMachine *machine);
};
Rva00346CDD::Rva00346CDD(StateMachine *machine)
	: Rva0034005D(machine)
{
	*(const void **)this = g_00C136A0;
}
