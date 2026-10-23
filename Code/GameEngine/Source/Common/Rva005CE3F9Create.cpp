// ?Rva005CE3F9Create@@YA?AVRva005CE3F9@@PBUPayload@Rva005CE327@@@Z
// cl: /O1 /MD /EHsc
// retail 0x005CE3F9, 50 bytes. Free __cdecl by-value creator: `new
// Rva005CE327(src)` stored into the returned handle with an AddRef inc.
// Target evidence: prolog `push ebp / mov ebp,esp / push ecx / and [ebp-4],0`
// then `push 0x10 / call 0x2fda0` (operator new), null test routed to
// `xor eax,eax`, ctor 0x005CE327, `mov [ecx],eax`, `inc [eax+4]`, leave/ret.
// Twin of 0x005CE2A1. The cleared [ebp-4] word is the /EHsc by-value
// return-construction flag; the non-throwing 0x005CE327 ctor view keeps the
// allocation free of an unwind state (retail has no EH frame). Callers take
// the handle as a by-value temporary.
#include <new>

class Rva005CE327
{
public:
	struct Payload { int v[3]; };
	Rva005CE327(const Payload *src) throw();
	virtual ~Rva005CE327();
public:
	int m_ref; // +4
	Payload m_data; // +8
};

class Rva005CE3F9
{
public:
	Rva005CE3F9(Rva005CE327 *p) : m_00(p) { if (p != 0) p->m_ref++; }
	~Rva005CE3F9();
	Rva005CE327 *m_00;
};

Rva005CE3F9 __cdecl Rva005CE3F9Create(const Rva005CE327::Payload *src)
{
	return Rva005CE3F9(new Rva005CE327(src));
}
