// cl: /O1 /DNDEBUG /MD
//
// ??_GTunnelTracker@@MAEPAXI@Z, retail 0x004F5919 (28 bytes): slot 0
// of vtable 0x00C63234, whose slot-2 name getter returns "TunnelTracker" (the only
// vtable using that getter). Scalar deleting destructor: calls the
// destructor at 0x004F561D and then the global operator delete when bit 0 of
// the flags is set. That destructor re-stores vtable 0x00C63234, which
// identifies it as TunnelTracker::~TunnelTracker (pinned in reverse/symbols.csv).
// Class shape from Zero Hour's Common/TunnelTracker.h (pooled).
// Zero Hour pools the class (MEMORY_POOL_GLUE: protected virtual
// destructor and an inline class operator delete); BFME 2's form frees
// through the global operator delete, so the class is modelled with none.
// The destructor is declared, not defined, so the call resolves to the pin;
// the dummy tag constructor (no retail counterpart) only makes this TU emit
// the vtable and with it the deleting destructor.

struct EmitVtableTag;

class TunnelTracker
{
public:
	TunnelTracker(EmitVtableTag *);
protected:
	virtual ~TunnelTracker();
};

// ?<TunnelTracker::TunnelTracker> absent-from-retail
TunnelTracker::TunnelTracker(EmitVtableTag *)
{
}
