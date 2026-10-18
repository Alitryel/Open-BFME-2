// cl: /GF
// Native VA 00DD8310 points at the complete "ID" key at 00BED340.
// Keep the existing data-ledger name and ABI; the rowed addInt callee
// consumes the key as a C string.
void *g_bfmeWhatBKG = (void *)"ID";

class BfmeSubBKG
{
public:
	void bfmeDoBKG(void *one, void *two);
};

void __stdcall bfmeGoBKG(BfmeSubBKG *sub, void *what)
{
	sub->bfmeDoBKG(g_bfmeWhatBKG, what);
}
