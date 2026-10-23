// cl: /MD
// ??0Rva005445D4@@QAE@PAVStateMachine@@@Z, retail 0x005445D4, 37 bytes.
// Derived State ctor via rowed/pinned State hash ctor 0x004D73FC with hash
// 0x90B65C1D then zero of +0x20/+0x24 then vtable 0x00869A20. Evidence:
// vtable store at [this]; base StateCtor hash pin; caller 0x005449DD in
// FUN_009448a1; prev 0x005440CD same dir.
class StateMachine;

class __declspec(novtable) State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	StateMachine *m_machine;
	bool m_tail1C;
	unsigned char m_pad1D[0x20 - 0x1D];
};

// The retail table at RVA 0x00869A20: 17 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GTurretAIIdleState@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Rva005445F9Get@@YAHXZ")();
void __identifier("?xfer@Rva005445D4@@UAEXPAVXfer@@@Z")();
void __identifier("?onEnter@AIDockProcessDockState@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?onExit@AIDockProcessDockState@@UAEXW4StateExitType@@@Z")();
void __identifier("?update@AIDockProcessDockState@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}
extern const void *const g_00C69A20[17] = {
	(const void *)&__identifier("??_GTurretAIIdleState@@UAEPAXI@Z"), // slot 0 0x004D8507
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?Rva005445F9Get@@YAHXZ"), // slot 2 0x005445F9
	(const void *)&__identifier("?xfer@Rva005445D4@@UAEXPAVXfer@@@Z"), // slot 3 0x00544AD2
	(const void *)&__identifier("?onEnter@AIDockProcessDockState@@UAE?AW4StateReturnType@@XZ"), // slot 4 0x00544646
	(const void *)&__identifier("?onExit@AIDockProcessDockState@@UAEXW4StateExitType@@@Z"), // slot 5 0x00544670
	(const void *)&__identifier("?update@AIDockProcessDockState@@UAE?AW4StateReturnType@@XZ"), // slot 6 0x00544B96
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 7 0x000B3FD0
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 8 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 9 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 11 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 12 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 13 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 14 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 15 0x0047A699
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 16 0x000B3FD0
};

class Rva005445D4 : public State
{
public:
	Rva005445D4(StateMachine *machine);
private:
	int m_20;
	int m_24;
};

Rva005445D4::Rva005445D4(StateMachine *machine) : State(machine, 0x90B65C1Du)
{
	m_20 = 0;
	m_24 = 0;
	*(const void **)this = g_00C69A20;
}
