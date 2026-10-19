// cl: /DNDEBUG /MD /EHsc
// ?rva005DCC60@BuildPhase@@QAEXXZ, retail 0x005DCC60, 38 bytes.
// Range loop over pointer array at this+4..this+8; for each element with
// +0x10 == 0 call virtual slot at vtable+0x18 with (this+0x14, 0).
// Evidence: virtual call offset 0x18, callees rowed/pinned, caller 0x005DCCFB.
// Owner: the caller is the rowed BuildPhase::update (0x005DCCFB), which calls
// this on its own this; +4..+8 is BuildPhase's orders vector.

class Elem
{
public:
	virtual void dummy0();
	virtual void dummy1();
	virtual void dummy2();
	virtual void dummy3();
	virtual void dummy4();
	virtual void dummy5();
	virtual void target(int a, int b);
	char m_pad4[0x10 - 4];
	int m_10; // +0x10
};

class BuildPhase
{
public:
	void rva005DCC60();
private:
	char m_pad0[4];
	Elem **m_begin; // +0x4
	Elem **m_end; // +0x8
	char m_padC[0x14 - 0xC];
	int m_14; // +0x14
};

void BuildPhase::rva005DCC60()
{
	for (Elem **it = m_begin; it != m_end; ++it)
	{
		Elem *e = *it;
		if (e->m_10 != 0)
			continue;
		e->target(m_14, 0);
	}
}
