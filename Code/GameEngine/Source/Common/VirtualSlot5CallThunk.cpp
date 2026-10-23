// Ported from Open-BFME-1's game/GameEngine/Source/Common/VirtualSlot5CallThunk.cpp
// (donor revision: reference/open-bfme-1 @ a38d345e) via tools/bfme1_sweep.py.
//
// The donor must be carried in pieces: it defines functions the sweep never
// placed, and .githooks/pre-commit's find_declared_unmatched refuses a source
// with any definition the ledger lacks. So this TU carries ONLY the body that
// places, which is the donor's `RetainedReferenceSetterThunk::setValue` shape
// (donor b1 0x0045E480, 18B -> game.dat 0x002D34E2, 18B).
//
// The name is address-derived, not the donor's: lotrbfme.exe folded this body
// across eight addresses, so `?d_0045e480@@YAXXZ` is only one of the twins the
// sweep cannot tell apart, and AGENTS.md forbids spending a guessed name on a
// folded address. The BYTES are not in doubt -- the sweep placed the 18 masked
// bytes uniquely at 0x002D34E2, and retail there is a whole function:
//
//   8b 54 24 04   mov edx, [esp+4]        ; the incoming pointer
//   85 d2         test edx, edx
//   8b c1         mov eax, ecx            ; return this
//   89 10         mov [eax], edx          ; m_value = incoming
//   74 03         je   +3
//   ff 42 04      inc dword ptr [edx+4]   ; ++incoming->m_referenceCount
//   c2 04 00      ret 4
//
// with 0x002D34E1 (`ret`) immediately before it, so the boundary is proven.
// The count sits at +4 because the counted object is polymorphic: the vptr
// occupies +0, exactly as in the donor.

struct Rva002D34E2RefCounted
{
	virtual void release( int deletingFlag );

	int m_referenceCount;					// +0x04, behind the vptr
};

class Rva002D34E2Setter
{
public:
	Rva002D34E2Setter *set( Rva002D34E2RefCounted *incoming );

	Rva002D34E2RefCounted *m_value;			// +0x00
};

// Defined out of line on purpose: an in-class definition is implicitly inline,
// and MSVC 7.1 does not emit an inline member this TU never calls, so the body
// would be missing from the object and the byte gate would have nothing to
// compare. The emitted code is the same either way.
Rva002D34E2Setter *Rva002D34E2Setter::set( Rva002D34E2RefCounted *incoming )
{
	m_value = incoming;

	if( incoming != 0 )
		++incoming->m_referenceCount;

	return this;
}
