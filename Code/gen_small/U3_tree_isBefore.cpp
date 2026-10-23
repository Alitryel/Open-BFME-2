// cl: -DNDEBUG -MD -EHs-c- /Os -Ireference/open-bfme-1/game/gen_small
// Open-BFME-1: the three red-black-tree lookups out of d_0005b6c0.asm. Not one
// byte of any of them is a relocation.
//
// The target is 0x00504165, 29 bytes: only the emptiness-and-front test is
// recovered here. The two walks (lowerBoundNode and lowerBound) are recovered
// in their own TUs.
//
// 0x00064850 is the emptiness-and-front test built on the same object: the
// count at +4 short-circuits to true and otherwise the leftmost node
// (header+8) supplies the key to compare against.
//
// Identity is address-derived; nothing in the image names them and the
// instantiation's value type is not recoverable from this body.
typedef int Int;
typedef unsigned int UnsignedInt;

struct Rva00064770Key
{
	unsigned char m_unreconstructed_00[0x18];
	UnsignedInt m_key;									///< key+0x18
};

struct Rva00064770Node
{
	Int m_colour;										///< node+0x00
	Rva00064770Node *m_parent;							///< node+0x04
	Rva00064770Node *m_left;							///< node+0x08
	Rva00064770Node *m_right;							///< node+0x0C
	unsigned char m_unreconstructed_10[0x18];
	UnsignedInt m_key;									///< node+0x28
};

class Rva00064770Tree
{
public:
	bool isBefore(UnsignedInt key) const;

private:
	Rva00064770Node *m_header;							///< retail this+0x00
	Int m_count;										///< retail this+0x04
};

// ?isBefore@Rva00064770Tree@@QBE_NI@Z
bool Rva00064770Tree::isBefore(UnsignedInt key) const
{
	if (m_count == 0)
	{
		return true;
	}

	return key < m_header->m_left->m_key;
}
