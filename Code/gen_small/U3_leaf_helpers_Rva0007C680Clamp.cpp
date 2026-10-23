// cl: -DNDEBUG -MD -EHs-c- /Os -Ireference/open-bfme-1/game/gen_small
// ?Rva0007C680Clamp@@YAHHHH@Z
// retail 0x00078C82, 26 bytes. Dedicated TU carrying the Open-BFME-1 donor
// preamble (game/gen_small/U3_leaf_ctors.cpp, reference/open-bfme-1) and only
// this body; the donor's other definitions are omitted. The donor TU compiled
// /Os emits this function byte-identical to retail (unique masked placement on
// unclaimed .text).
//
// Donor provenance: game/gen_small/U3_leaf_ctors.cpp, which states that every
// row in it compares byte for byte with nothing masked out: none touches a
// global, a string or a vftable, so there is no DIR32 site anywhere and no
// REL32 either. That also means nothing in the image names them, so the
// identities are address-derived; what the bytes do fix is the shape and, for
// the free comparison helpers, the operand order. The donor notes that the
// Max sibling `__b < __a ? __a : __b` is the reversed spelling and not
// STLport's `__a < __b ? __b : __a`, because retail jumps on GREATER to keep
// the FIRST argument.

typedef int Int;

// ---------------------------------------------------------------------------
// free comparison helpers; __cdecl, three Int arguments by value

// ?Rva0007C680Clamp@@YAHHHH@Z
Int Rva0007C680Clamp(Int low, Int value, Int high)
{
	if (value < low)
	{
		return low;
	}

	if (value > high)
	{
		return high;
	}

	return value;
}