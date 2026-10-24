// cl: /MD
// ?rva002CF302@Rva002CF302@@QAEXPAURva002CF302Node@@@Z @0x002CF302 45B.
// Tree erase: recurse right via +0xC, free the node via rowed _free 0x00030830,
// walk left via +0x8, ret 4. Same 45B shape as the rowed 0x002CF2D5 erase.
// Caller at 0x002CF7EC unblocks 0x002CF7DE.
extern "C" void __cdecl free(void *block);

struct Rva002CF302Node
{
	unsigned char m_pad00[8];
	Rva002CF302Node *m_left;
	Rva002CF302Node *m_right;
};

struct Rva002CF302
{
	void rva002CF302(Rva002CF302Node *node);
};

void Rva002CF302::rva002CF302(Rva002CF302Node *node)
{
	while (node != 0) {
		rva002CF302(node->m_right);
		Rva002CF302Node *leftChild = node->m_left;
		free(node);
		node = leftChild;
	}
}
