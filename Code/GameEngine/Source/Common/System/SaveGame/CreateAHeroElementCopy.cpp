// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB

// Twelve-byte CreateAHeroData array element. Its retail default constructor
// zeros an AsciiString and two scalar words; assignment preserves string
// ownership through StringBase::set at 0x366F0. Field meanings are unknown.
#include "ascii_string.h"
struct BfmeHeroElement005C39DE { AsciiString text; unsigned word4, word8; BfmeHeroElement005C39DE(); ~BfmeHeroElement005C39DE(); BfmeHeroElement005C39DE &operator=(const BfmeHeroElement005C39DE &); };
// The native array callback at 48BA39 destroys only the leading string.
// Define this outside the emission anchor's inline-depth setting so the
// ordinary member teardown reaches releaseBuffer directly, as retail does.
inline BfmeHeroElement005C39DE::~BfmeHeroElement005C39DE() {}
inline BfmeHeroElement005C39DE::BfmeHeroElement005C39DE() : text(), word4(0), word8(0) {}
BfmeHeroElement005C39DE &BfmeHeroElement005C39DE::operator=(const BfmeHeroElement005C39DE &o) { if (this != &o) { text=o.text; word4=o.word4; word8=o.word8; } return *this; }

// BfmeHeroElement005C39DE lifetimes are inline elsewhere: other units emit
// select-any copies, so a strong definition here was a duplicate in the linked
// build. This anchor only makes this unit emit its verified lifetime copies;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitCreateAHeroElementCopy@@YAXPAUBfmeHeroElement005C39DE@@@Z present-unmatched
void bfmeEmitCreateAHeroElementCopy(BfmeHeroElement005C39DE *p)
{
	p->BfmeHeroElement005C39DE::BfmeHeroElement005C39DE();
	p->BfmeHeroElement005C39DE::~BfmeHeroElement005C39DE();
}
#pragma inline_depth()
