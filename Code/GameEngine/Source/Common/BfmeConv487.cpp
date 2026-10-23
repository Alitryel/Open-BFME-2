struct BfmeSubBLF
{
	unsigned char m_bfmeHead[4];
};

void bfmeDoBLF(BfmeSubBLF *sub, void *what, int many);

class BfmeThingBLF
{
public:
	void bfmeGoBLF(void *what);
	unsigned char m_bfmeHead[0x174];
	BfmeSubBLF m_bfmeSub;
};

void BfmeThingBLF::bfmeGoBLF(void *what)
{
	bfmeDoBLF(&m_bfmeSub, what, 0x20);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeNoteVJI@BfmeSubVJI@@QAEXPBD@Z=?bfmeGoBLF@BfmeThingBLF@@QAEXPAX@Z")
#pragma comment(linker, "/alternatename:?bfmeDoBLF@@YAXPAUBfmeSubBLF@@PAXH@Z=?ji_0062983e@@YAXXZ")
