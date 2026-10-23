// cl: /O1 /MD
//
// Opaque destructor at 0x004E32F2 (14B): stores its vtable, adjusts this to
// the member at +0x0C, and tail-calls the vector destructor at 0x002B80CE
// (pinned opaque ??1RvaVec002B80CE: range-destroy via _Destroy 0x2B70B3, then
// operator delete; element type unproven). Same vptr-plus-adjust-plus-tail-
// jmp shape as the 0x002CEC0A twin (member at +0x04 there, +0x0C here -- this
// class carries an 8-byte head under its vptr). The vector type is only
// declared here (defined nowhere -- the dtor call resolves via the pin).
// Member-vs-base is unprovable from these bytes (modeled as a member).
// Owner identity is unproven (opaque Rva name).
// Upgrades the ??1Rva004E32F2 pin (called by the landed ??_G at 0x004E37B3).

class RvaVec002B80CE
{
public:
	~RvaVec002B80CE();

private:
	void *m_begin;
	void *m_end;
	void *m_storage;
};

class Rva004E32F2
{
public:
	virtual ~Rva004E32F2();

private:
	char m_head0C[8];
	RvaVec002B80CE m_vector0C;
};

inline Rva004E32F2::~Rva004E32F2()
{
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva004E32F2InlineAnchor@@YAXPAVRva004E32F2@@@Z absent-from-retail
void _bfmeRva004E32F2InlineAnchor(Rva004E32F2 *p)
{
    p->Rva004E32F2::~Rva004E32F2();
}
#pragma inline_depth()
