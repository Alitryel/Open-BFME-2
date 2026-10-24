// cl: /MD
// ?rva002CF2D5@Rva002CF2D5@@QAEXPAURva002CF2D5Node@@@Z @0x002CF2D5 45B.
// Tree erase: recurse right via +0xC, free the node via rowed _free 0x00030830,
// walk left via +0x8, ret 4. Same 45B shape as the rowed _M_erase 0x00357153.
// Caller at 0x002CF7C3 unblocks 0x002CF7B5.
extern "C" void __cdecl free(void *block);

struct Rva002CF2D5Node
{
	unsigned char m_pad00[8];
	Rva002CF2D5Node *m_left;
	Rva002CF2D5Node *m_right;
};

struct Rva002CF2D5
{
	void rva002CF2D5(Rva002CF2D5Node *node);
};

void Rva002CF2D5::rva002CF2D5(Rva002CF2D5Node *node)
{
	while (node != 0) {
		rva002CF2D5(node->m_right);
		Rva002CF2D5Node *y = node->m_left;
		free(node);
		node = y;
	}
}
