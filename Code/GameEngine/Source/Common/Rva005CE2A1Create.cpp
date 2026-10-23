// cl: /O1 /MD /EHsc
// Target evidence: retail 0x005CE2A1 allocates 0x10 bytes, calls the
// 0x005CE259 constructor, stores the result in the returned handle's m_00,
// increments the object's refcount when non-null, and returns the handle by
// value (hidden return pointer). Its callers (ThrowingNewHelpers.cpp,
// StrategicInGameUIPlanningPhaseBuildingSelectionCtor.cpp) receive the handle
// as a by-value temporary, so the function is the by-value creator; the
// cleared [ebp-4] word is the compiler's return-construction flag under /EHsc,
// and the non-throwing 0x005CE259 ctor view keeps the allocation free of an
// unwind state (retail has no EH frame). The
// address-derived names preserve uncertainty about the surrounding subsystem.

#include <new>

class Rva005CE259
{
public:
	struct Payload { int v[2]; };
	Rva005CE259(const Payload *src) throw();
	virtual ~Rva005CE259();
	int m_ref; // +4
	Payload m_data; // +8
};

class Rva005CE2A1
{
public:
	Rva005CE2A1(Rva005CE259 *p) : m_00(p) { if (p != 0) p->m_ref++; }
	~Rva005CE2A1();
	Rva005CE259 *m_00;
};

Rva005CE2A1 __cdecl Rva005CE2A1Create(const Rva005CE259::Payload *src)
{
	return Rva005CE2A1(new Rva005CE259(src));
}
