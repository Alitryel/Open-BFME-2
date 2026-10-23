// cl: -DNDEBUG -MD -EHs-c- /Os -Ireference/open-bfme-1/game/gen_small
// Open-BFME-1: the three red-black-tree lookups out of d_0005b6c0.asm, plus a
// small struct copy. Not one byte of any of them is a relocation.
//
// The target is 0x0029B6BE, 27 bytes: only the struct copy is recovered here.
// The three tree walks (lowerBoundNode, lowerBound and isBefore) are recovered
// in their own TUs.
//
// It RETURNS the destination, and that return is what the bytes prove: nothing
// reads eax afterwards, yet retail keeps the destination in eax and pays for a
// `lea edx,[eax+4]` plus an esi temp to copy the vector without clobbering it.
// Written as a void function the same source compiles to 34 bytes that reuse
// eax as the cursor.
struct Rva00069940Vector
{
	int m_x;
	int m_y;
	int m_z;
};

struct Rva00069940Value
{
	int m_kind;											///< value+0x00
	Rva00069940Vector m_vector;							///< value+0x04
};

// ?Rva00069940Assign@@YAPAURva00069940Value@@PAU1@PBU1@PBURva00069940Vector@@@Z
Rva00069940Value *Rva00069940Assign(Rva00069940Value *destination,
	const Rva00069940Value *source, const Rva00069940Vector *vector)
{
	destination->m_kind = source->m_kind;
	destination->m_vector = *vector;
	return destination;
}
