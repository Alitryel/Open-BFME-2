// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva002ADD75Equal@@YAHPBUAsciiRange002ADD75@@0@Z @0x002ADD75 (61B): AsciiString range pair equal.
// Checks the two 8-byte ranges (begin/end) have equal size via sub-xor-test
// -4 then delegates to rowed Rva002ACFFBEqual at 0x002ACFFB for
// element-wise StringBase compare. Same 61B shape as sibling Rva002AAC9EEqual
// at 0x002AAC9E (float-range equal via size xor plus helper returning int 1/0).
// Callers at 0x002B0EA4 0x002B2179 0x00360F2C 0x00360F3F 0x004E2E36 test al.
// Prev grantScience next ObjectLookupMapFindSlot.
#include "ascii_string.h"

struct AsciiRange002ADD75
{
	StringBase<char> *m_begin;
	StringBase<char> *m_end;
};

bool __cdecl Rva002ACFFBEqual(StringBase<char> *first1, StringBase<char> *last1, StringBase<char> *first2);

int __cdecl Rva002ADD75Equal(const AsciiRange002ADD75 *lhs, const AsciiRange002ADD75 *rhs)
{
	int sizeA = (char const *)lhs->m_end - (char const *)lhs->m_begin;
	int sizeB = (char const *)rhs->m_end - (char const *)rhs->m_begin;
	if ((((sizeA ^ sizeB) & -4) == 0) && Rva002ACFFBEqual(lhs->m_begin, lhs->m_end, rhs->m_begin))
		return 1;
	return 0;
}
