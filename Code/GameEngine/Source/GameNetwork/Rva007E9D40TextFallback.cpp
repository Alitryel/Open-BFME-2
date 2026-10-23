// cl: /O2
// Open-BFME-1 donor at cd32c8ef06dfb0d995b2f47e93e41622e4447092:
// Rva007E9D40TextFallback.cpp at BFME1 RVA 0x007E9D40.
// The target address map selects BFME2 RVA 0x00656CF0 from two placements.
// Retail independently reads the inline text at +0x101 and calls the source
// object's slot seven through the pointer at +0xC.

struct Rva007E9D40Source
{
	virtual void slot0(); virtual void slot1(); virtual void slot2();
	virtual void slot3(); virtual void slot4(); virtual void slot5();
	virtual void slot6();
	virtual char *fallback();
};

struct Rva007E9D40Owner
{
	char m_pad0[12];
	Rva007E9D40Source *m_source;
	char m_pad10[0xF1];
	char m_text[1];
	char *getText();
};

char *Rva007E9D40Owner::getText()
{
	char *local = m_text;
	if (*local)
		return local;
	return m_source ? m_source->fallback() : 0;
}
