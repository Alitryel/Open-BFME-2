// cl: /O1 /DNDEBUG /MD
//
// ??_GTeamPrototype@@MAEPAXI@Z, retail 0x003A38B1 (28 bytes): slot 0
// of vtable 0x00C1AE94, whose slot-2 name getter returns "TeamPrototype" (the only
// vtable using that getter). Scalar deleting destructor: calls the
// destructor at 0x003A33CD and then the global operator delete when bit 0 of
// the flags is set. That destructor re-stores vtable 0x00C1AE94, which
// identifies it as TeamPrototype::~TeamPrototype (pinned in reverse/symbols.csv).
// Class shape from Zero Hour's Common/Team.h (pooled).
// Zero Hour pools the class (MEMORY_POOL_GLUE: protected virtual
// destructor and an inline class operator delete); BFME 2's form frees
// through the global operator delete, so the class is modelled with none.
// The destructor is declared, not defined, so the call resolves to the pin;
// the dummy tag constructor (no retail counterpart) only makes this TU emit
// the vtable and with it the deleting destructor.

struct EmitVtableTag;
class Xfer;

class TeamPrototype
{
public:
	TeamPrototype(EmitVtableTag *);
protected:
	virtual ~TeamPrototype();
	// The rest of vtable 0x00C1AE94 (TeamPrototypeCtor.cpp's rows), declared so
	// this TU's ??_7TeamPrototype is the same four-slot table.
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *);
};

// ?<TeamPrototype::TeamPrototype> absent-from-retail
TeamPrototype::TeamPrototype(EmitVtableTag *)
{
}
