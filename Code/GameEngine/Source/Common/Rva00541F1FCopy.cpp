// cl: /EHsc /DNDEBUG /MD
// stlport
//
// ??0Rva00541F1F@@QAE@ABV0@@Z @0x00541F1F 83B: copy constructor. It copies
// the rowed polymorphic base Rva0053FADE (0x0053FADE), installs vtable
// 0x00C69514, then copies the member-plus-vector holders at +0x24 (rowed
// Rva00541913 copy 0x00541913) and +0x44 (rowed Rva00541A6E copy
// 0x00541A6E). Identities are address-derived.

class Rva0053FADE
{
public:
	Rva0053FADE(const Rva0053FADE &other);
	virtual ~Rva0053FADE();

private:
	char m_pad[0x20];
};

// Link repair (class U-twin). The copy ctor emits its vtable and its EH cleanup
// funclets, and the declared-only placeholder dtors left those funclets'
// ??1Rva00541913@@QAE@XZ / ??1Rva00541A6E@@QAE@XZ unresolved. Retail's +0x24 and
// +0x44 members are its 28-byte narrow record, whose whole 65B teardown is the
// rowed ICF twin ??1BfmeNarrowRecord0041A5D2@@QAE@XZ (0x0041A200, dup
// 0x00541E77), so bind each holder's dtor to that shared name via the canonical
// record header. The class dtor stays undeclared as in the sibling
// Rva00540845Ctor.cpp: cl emits the implicit dtor in this TU, which the vtable's
// dtor slot and the scalar deleting dtor reference.
#include "BfmeNarrowRecord0041A5D2.h"

class Rva00541913
{
public:
	Rva00541913(const Rva00541913 &that);
	~Rva00541913() { ((BfmeNarrowRecord0041A5D2 *)this)->BfmeNarrowRecord0041A5D2::~BfmeNarrowRecord0041A5D2(); }

private:
	char m_pad[0x20];
};

class Rva00541A6E
{
public:
	Rva00541A6E(const Rva00541A6E &that);
	~Rva00541A6E() { ((BfmeNarrowRecord0041A5D2 *)this)->BfmeNarrowRecord0041A5D2::~BfmeNarrowRecord0041A5D2(); }

private:
	char m_pad[0x20];
};

class Rva00541F1F : public Rva0053FADE
{
public:
	Rva00541F1F(const Rva00541F1F &other);

private:
	Rva00541913 m_24;
	Rva00541A6E m_44;
};

Rva00541F1F::Rva00541F1F(const Rva00541F1F &other) :
	Rva0053FADE(other),
	m_24(other.m_24),
	m_44(other.m_44)
{
}
