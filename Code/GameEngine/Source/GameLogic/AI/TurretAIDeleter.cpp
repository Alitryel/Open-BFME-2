// cl: /O1 /DNDEBUG /MD
//
// ??_GTurretAI@@MAEPAXI@Z, retail 0x004D8974 (28 bytes): slot 0
// of vtable 0x00C60D78, whose slot-2 name getter returns "TurretAI" (the only
// vtable using that getter). Scalar deleting destructor: calls the
// destructor at 0x004D86C1 and then the global operator delete when bit 0 of
// the flags is set. That destructor re-stores vtable 0x00C60D78, which
// identifies it as TurretAI::~TurretAI (pinned in reverse/symbols.csv).
// Class shape from Zero Hour's GameLogic/TurretAI.h (pooled).
// Zero Hour pools the class (MEMORY_POOL_GLUE: protected virtual
// destructor and an inline class operator delete); BFME 2's form frees
// through the global operator delete, so the class is modelled with none.
// The destructor is declared, not defined, so the call resolves to the pin;
// the dummy tag constructor (no retail counterpart) only makes this TU emit
// the vtable and with it the deleting destructor.

struct EmitVtableTag;

class TurretAI
{
public:
	TurretAI(EmitVtableTag *);
protected:
	virtual ~TurretAI();
};

// ?<TurretAI::TurretAI> absent-from-retail
TurretAI::TurretAI(EmitVtableTag *)
{
}
