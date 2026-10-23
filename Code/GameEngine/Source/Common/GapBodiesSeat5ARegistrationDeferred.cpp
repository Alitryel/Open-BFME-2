// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Existing registration constructors whose virtual-slot providers remain unresolved.
// Preserve their native evidence apart from the independent GapBodiesSeat5A routines.

// --- 0x005C43CF, 0x005C459E, 0x005C47F0 (24B each): derived constructors
// over the rowed registration base 0x0052B894 (name passed through), each
// then installing its own vtable (0x00C745A0, 0x00C74698, 0x00C7475C).
class AsciiString;
class Rva0052B894Registration
{
public:
	Rva0052B894Registration(const AsciiString &name);		// 0x0052B894
	virtual void slot0();
};

#define SEAT5_REGISTRATION_CTOR(RVA) \
class Rva##RVA##Registration : public Rva0052B894Registration \
{ \
public: \
	Rva##RVA##Registration(const AsciiString &name); \
	virtual void slot0(); \
}; \
Rva##RVA##Registration::Rva##RVA##Registration(const AsciiString &name) \
	: Rva0052B894Registration(name) \
{ \
}

SEAT5_REGISTRATION_CTOR(005C43CF)
SEAT5_REGISTRATION_CTOR(005C459E)
SEAT5_REGISTRATION_CTOR(005C47F0)
