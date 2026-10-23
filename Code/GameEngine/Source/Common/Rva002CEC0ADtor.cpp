// cl: /O1 /MD
//
// Opaque destructor at 0x002CEC0A (14B): stores its vtable, adjusts this to
// the member at +0x04, and tail-calls the vector destructor at 0x002CC70
// (pinned opaque ??1RvaVecAscii: range-destroy via AsciiString _Destroy
// 0x2CB64, then operator delete; element type unproven). Same vptr-plus-
// adjust-plus-tail-jmp shape as the Rva000AD6F4Members family, with a vector
// member instead of a clear-helper member. The vector type is only declared
// here (defined nowhere -- the dtor call resolves via the pin). Whether the
// +0x04 subobject is a member or a (non-polymorphic) base is unprovable from
// these bytes (both put the subobject at +0x04 under a fresh vptr); modeled
// as a member. Owner identity is unproven (opaque Rva name).
// Upgrades the ??1Rva002CEC0A pin (called by the landed ??_G at 0x002CEC18).

class RvaVecAscii
{
public:
	~RvaVecAscii();

private:
	void *m_begin;
	void *m_end;
	void *m_storage;
};

class Rva002CEC0A
{
public:
	virtual ~Rva002CEC0A();

private:
	RvaVecAscii m_vector04;
};

inline Rva002CEC0A::~Rva002CEC0A()
{
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva002CEC0AInlineAnchor@@YAXPAVRva002CEC0A@@@Z absent-from-retail
void _bfmeRva002CEC0AInlineAnchor(Rva002CEC0A *p)
{
    p->Rva002CEC0A::~Rva002CEC0A();
}
#pragma inline_depth()
