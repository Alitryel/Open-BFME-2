// cl: /O1 /DNDEBUG /MD
//
// ??_GAnim2D@@MAEPAXI@Z, retail 0x002D73D0 (28 bytes): slot 0 of vtable
// 0x00C03358, whose slot-2 name getter returns "Anim2D" (the only vtable
// using that getter). Scalar deleting destructor: calls the rowed
// Anim2D::~Anim2D (0x002D6E08) and then the global operator delete when bit 0
// of the flags is set.
// Zero Hour gives Anim2D a memory pool (MEMORY_POOL_GLUE), whose class
// operator delete makes the 34-byte pool form; BFME 2's 28-byte form frees
// through the global operator delete, so the class is modelled here with no
// class-specific operator delete. The destructor is declared, not defined,
// so the call resolves to the rowed body; the dummy tag constructor (no retail
// counterpart) only makes this TU emit the vtable and with it the deleting destructor.

struct EmitVtableTag;
class Xfer;

class Anim2D
{
public:
	Anim2D(EmitVtableTag *);
protected:
	virtual ~Anim2D();
	// Snapshot slots, as InGameUIFloatingAnimation.cpp's Anim2D (first in link
	// order) declares them.
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
};

// ?<Anim2D::Anim2D> absent-from-retail
Anim2D::Anim2D(EmitVtableTag *)
{
}
