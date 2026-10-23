// cl: /MD
//
// ?rva001E4A4E@Rva001E4A4E@@QAE_NH@Z @0x001E4A4E 21B
// __thiscall bool(int bit): return Rva001E4426Test(bits at this+0x1c8, bit).
// Evidence: push arg then add ecx 0x1c8 push ecx call rowed 0x001E4426,
// callers 0x00290288 0x00290369 0x00291CD8, neighbours Rva001E4954Destroy.
bool __cdecl Rva001E4426Test(unsigned int *bits, int bit);

class Rva001E4A4E
{
public:
	bool rva001E4A4E(int bit);
private:
	char _00[0x1c8];
	unsigned int m_1c8;
};

bool Rva001E4A4E::rva001E4A4E(int bit)
{
	return Rva001E4426Test(&m_1c8, bit);
}
