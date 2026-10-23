// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// Twin of 0x0092F070 (Bfme5MeshMatDescGetTexture.cpp's Gen_0092F070::bfmeGet)
// with the same forwarding shape but calling the already-matched
// Gen_009299D0::bfmeGet (0x009299D0) instead of Gen_00929A20::bfmeGet.
// BFME2 retail reads the forwarder at +0x94 (37-word head), not the donor's
// +0x9C, so the mirror is sized accordingly here.
// Address-derived class — owning type is not recovered.

class BfmeThingCX
{
public:
	int m_bfmeHead;						// +0x00
	unsigned short m_bfmeRefs;				// +0x04
};

class BfmeHandleCX
{
public:
	BfmeHandleCX(void)
	{
		m_bfmeThing = 0;
	}

	BfmeHandleCX(const BfmeHandleCX &other)
	{
		BfmeThingCX *thing = other.m_bfmeThing;

		m_bfmeThing = thing;

		if (thing)
			++thing->m_bfmeRefs;
	}

	~BfmeHandleCX(void);

	BfmeThingCX *m_bfmeThing;				// +0x00
};

class Gen_00929260
{
public:
	__declspec(noinline) BfmeHandleCX bfmeGet(int index) const;

private:
	int m_bfmeHead[2];					// +0x00
	BfmeHandleCX *m_bfmeSlots;				// +0x08
};

class Gen_009299D0
{
public:
	BfmeHandleCX bfmeGet(int pidx, int pass, int stage) const;

private:
	int m_bfmeHead[29];					// +0x00
	BfmeHandleCX m_bfmeSlots[8];				// +0x74
	int m_bfmeMid[8];					// +0x94
	Gen_00929260 *m_bfmeArrays[8];				// +0xB4
};

class Rva006FD440
{
public:
	__declspec(noinline) BfmeHandleCX bfmeGet(int pidx, int pass, int stage) const;

private:
	int m_bfmeHead[37];					// +0x00
	Gen_009299D0 *m_cur;					// +0x94
};

// ?bfmeGet@Rva006FD440@@QBE?AVBfmeHandleCX@@HHH@Z
BfmeHandleCX Rva006FD440::bfmeGet(int pidx, int pass, int stage) const
{
	return m_cur->bfmeGet(pidx, pass, stage);
}
