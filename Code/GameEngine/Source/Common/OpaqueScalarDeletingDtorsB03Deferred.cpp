// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B03: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner. Each destructor is declared, not defined, so the call
// resolves to its pin in reverse/symbols.csv (address names unless the
// destructor already carried one); the dummy tag constructors (no retail
// counterpart) only make this TU emit each vtable and with it the deleting
// destructor. Owner identities are not recovered, and these declarations
// model no layout (docs/reconstruction/deleting-destructor-identity-audit.md)
// beyond the secondary-base offsets their adjustor thunks prove.
//
//   wrapper     dtor        vtable#slot
//   0x00148DC3 was rehomed to the concrete NameKeyGenerator lifetime unit.
//   0x0014DCAC  0x0014DC9E  0x00BD3898#0
//   0x00150A5B  0x001505CD  0x00BD3A34#0
//   0x001684BA  0x001684D6  0x00BD41C8#1
//   0x0018010E  0x0017FFCA  0x00BD4F50#9
//   0x001D93B2  0x001D92C0  0x00BD9CB0#0
//   0x001DF3D5  0x001DF057  0x00BDC5B8#0
//   0x001E1241  0x001E125D  0x00BDD95C#0
//   0x001E28EA  0x001E2906  0x00BDD978#0
//   0x001E2C92  0x001E2AD9  0x00BDD97C#0
//   0x001E7EAE  0x001E72B4  0x00BDE970#0
//   0x001EB815  0x0037DEE4  0x00BDF158#0
//   0x001ED52D  0x001ED41B  0x00BDF260#0
//   0x001F4B47  0x001F4B01  0x00BE171C#0
//   0x001F61E5  0x001F4D22  0x00BE174C#0
//   0x001FA779  0x001F9D98  0x00BE18C8#0
//   0x001FC17F  0x001FBD17  0x00BE1A10#0
//   0x001FC3A3  0x001FC0F1  0x00BE1A38#0
//   0x001FE772  0x001FE06A  0x00BE1BE8#0

struct EmitVtableTag;

// Unchanged provider-blocked families isolated from the linking siblings.
class Rva001505CD
{
public:
	Rva001505CD(EmitVtableTag *);
public:
	virtual ~Rva001505CD();
};

// ?<Rva001505CD::Rva001505CD> absent-from-retail
Rva001505CD::Rva001505CD(EmitVtableTag *)
{
}

class Rva0037DEE4
{
public:
	Rva0037DEE4(EmitVtableTag *);
public:
	virtual ~Rva0037DEE4();
};

// ?<Rva0037DEE4::Rva0037DEE4> absent-from-retail
Rva0037DEE4::Rva0037DEE4(EmitVtableTag *)
{
}

class Rva001FE06A
{
public:
	Rva001FE06A(EmitVtableTag *);
public:
	virtual ~Rva001FE06A();
};

// ?<Rva001FE06A::Rva001FE06A> absent-from-retail
Rva001FE06A::Rva001FE06A(EmitVtableTag *)
{
}
