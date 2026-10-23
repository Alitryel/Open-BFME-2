// Open-BFME5 conversions.

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

class BfmePoolVLR
{
public:
	virtual void bfmeSlot0VLR();
	virtual void bfmeSlot1VLR();
	virtual void *bfmeNewVLR(int n, int f);
	virtual void bfmeDelVLR(void *p, int f);
};

class GenAlloc;
GenAlloc *Gen007EFFC0();

class BfmeBufVLR
{
public:
	void bfmeSetSizeVLR(int size);
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	char *m_bfme0c;
	volatile int m_bfme10;
};

void BfmeBufVLR::bfmeSetSizeVLR(int size)
{
	if (m_bfme0c != 0)
	{
		((BfmePoolVLR *)Gen007EFFC0())->bfmeDelVLR(m_bfme0c, 0);
		m_bfme0c = 0;
		m_bfme10 = 0;
	}
	m_bfme10 = (size & ~7) + 0x80;
	m_bfme0c = (char *)((BfmePoolVLR *)Gen007EFFC0())->bfmeNewVLR(m_bfme10, 0);
	memset(m_bfme0c, 0, m_bfme10);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeSetSizeVLR@Rva007EB8B0Log@@QAEXH@Z=?bfmeSetSizeVLR@BfmeBufVLR@@QAEXH@Z")
