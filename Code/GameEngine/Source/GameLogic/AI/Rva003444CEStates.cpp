// cl: /DNDEBUG /MD /EHsc
// ??0BackAwayAndCowerStateMachine@@QAE@PAVObject@@0I@Z @0x003444CE 174B.
// StateMachine-family ctor (thiscall): base-constructs the rowed
// StateMachine base from (owner, name, 0), installs its vftable 0x00811FE8
// (shared with the destructor 0x003402D0, whose unit names the class from
// the slot 2 getter 0x003402DB), runs the rowed
// StateMachine::rva004D750F hook on the second object param, then two
// new-expression state blocks into the dead name slot with post-call eax
// feeding rowed defineState directly (B952-family shape). Zero CSEs into
// ebx; this stays in esi; 0x270F rides edi. The third argument is the
// machine's name key, forwarded unchanged into the base's unsigned name slot
// and never destroyed (the only caller, AIBackAwayAndCowerState::onEnter
// 0x00347C38, pushes the constant 0xD944B508).

class Object;
struct State;
struct StateConditionInfo;

class StateMachine
{
public:
	StateMachine(Object *owner, unsigned int name, bool flag);
	virtual ~StateMachine();
	void defineState(unsigned int id, State *state, unsigned int successID, unsigned int failureID, const StateConditionInfo *conditions);
	void rva004D750F(Object *obj);
};


// Rowed 0x0034301B as AIBackAwayState::AIBackAwayState (AIStateRva0034005DCtor.cpp).
class AIBackAwayState
{
public:
	AIBackAwayState(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x58 - 4];
};

class Rva0033F7C8
{
public:
	Rva0033F7C8(StateMachine *machine);
private:
	void *m_vtbl;
	char m_pad[0x20 - 4];
};

class BackAwayAndCowerStateMachine : public StateMachine
{
public:
	BackAwayAndCowerStateMachine(Object *owner, Object *arg, unsigned int nameKey);
	virtual ~BackAwayAndCowerStateMachine();
};

BackAwayAndCowerStateMachine::BackAwayAndCowerStateMachine(Object *owner, Object *arg, unsigned int nameKey)
	: StateMachine(owner, nameKey, false)
{
	((StateMachine *)this)->rva004D750F(arg);
	AIBackAwayState *s0 = new AIBackAwayState((StateMachine *)this);
	((StateMachine *)this)->defineState(0, (State *)s0, 1, 0x270F, (const StateConditionInfo *)0);
	Rva0033F7C8 *s1 = new Rva0033F7C8((StateMachine *)this);
	((StateMachine *)this)->defineState(1, (State *)s1, 0x270E, 0x270F, (const StateConditionInfo *)0);
}
