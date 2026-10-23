class BfmeSubBDB
{
public:
	void bfmeDoBDB(void *what, int flag);
};

void bfmeGoBDB(void *one, BfmeSubBDB *two)
{
	two->bfmeDoBDB(one, 0);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeCbVJM@@YGXXZ=?bfmeGoBDB@@YAXPAXPAVBfmeSubBDB@@@Z")
