// cl: /O1 /DNDEBUG /MD
//
// ??_GAIGroup@@MAEPAXI@Z, retail 0x0036E8EA (28 bytes): slot 0
// of vtable 0x00C17D00, whose slot-2 name getter returns "AIGroup" (the only
// vtable using that getter). Scalar deleting destructor: calls the
// destructor at 0x0036E564 and then the global operator delete when bit 0 of
// the flags is set. That destructor re-stores vtable 0x00C17D00, which
// identifies it as AIGroup::~AIGroup (pinned in reverse/symbols.csv).
// Class shape from Zero Hour's GameLogic/AI.h (pooled).
// Zero Hour pools the class (MEMORY_POOL_GLUE: protected virtual
// destructor and an inline class operator delete); BFME 2's form frees
// through the global operator delete, so the class is modelled with none.
// The destructor is declared, not defined, so the call resolves to the pin;
// the dummy tag constructor (no retail counterpart) only makes this TU emit
// the vtable and with it the deleting destructor.

struct EmitVtableTag;
class Xfer;

class AIGroup
{
public:
	AIGroup(EmitVtableTag *);
protected:
	virtual ~AIGroup();
	// Snapshot slots, as AIGroupConstructor.cpp (first in link order) declares them.
public:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
protected:
	virtual void xfer(Xfer *xfer);
};

// ?<AIGroup::AIGroup> absent-from-retail
AIGroup::AIGroup(EmitVtableTag *)
{
}
