// cl: -DNDEBUG -MD -EHs-c- /Os -Ireference/open-bfme-1/game/gen_small
// ??0Rva00060850Record@@QAE@XZ
// retail 0x003B943D, 24 bytes. Dedicated TU carrying the Open-BFME-1 donor
// preamble (game/gen_small/U3_leaf_ctors.cpp, reference/open-bfme-1) and only
// this body; the donor's other definitions are omitted. The donor TU compiled
// /Os emits this ctor byte-identical to retail (unique masked placement on
// unclaimed .text).
//
// Donor provenance: game/gen_small/U3_leaf_ctors.cpp, which states that every
// row in it compares byte for byte with nothing masked out: none touches a
// global, a string or a vftable, so there is no DIR32 site anywhere and no
// REL32 either. That also means nothing in the image names them, so the
// identities are address-derived; what the bytes do fix is the shape, the
// field offsets and, for the constructors, the source order of the stores
// (MSVC 7.1 does not reorder straight-line constant stores).

typedef int Int;

// ---------------------------------------------------------------------------
// a six-field record whose 0x0C and 0x14 slots start at -1

class Rva00060850Record
{
public:
	Rva00060850Record(void);

private:
	Int m_value00;										///< retail this+0x00
	Int m_value04;										///< retail this+0x04
	Int m_value08;										///< retail this+0x08
	Int m_index0C;										///< retail this+0x0C
	Int m_value10;										///< retail this+0x10
	Int m_index14;										///< retail this+0x14
};

// ??0Rva00060850Record@@QAE@XZ
Rva00060850Record::Rva00060850Record(void)
{
	m_value00 = 0;
	m_value04 = 0;
	m_value08 = 0;
	m_index0C = -1;
	m_value10 = 0;
	m_index14 = -1;
}