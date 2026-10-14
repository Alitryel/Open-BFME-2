extern "C" void bfmeDtorCbDMC(void *what);
void __cdecl operator delete[](void *block);

class BfmeThingDMC
{
public:
	void *bfmeGoDMC(unsigned char flags);
};

void __stdcall bfmeVecDtorDMC(void *base, unsigned int size, int count, void (*dtor)(void *));

void *BfmeThingDMC::bfmeGoDMC(unsigned char flags)
{
	if (flags & 2)
	{
		char *base = (char *)this - 4;
		bfmeVecDtorDMC(this, 0x0C, *(int *)base, bfmeDtorCbDMC);
		if (flags & 1)
			::operator delete[](base);
		return base;
	}
	if (flags & 1)
		::operator delete(this);
	return this;
}

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:?bfmeVecDtorDMC@@YGXPAXIHP6AX0@Z@Z=??_M@YGXPAXIHP6EX0@Z@Z")
