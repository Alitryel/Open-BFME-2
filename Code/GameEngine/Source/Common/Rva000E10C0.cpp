// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// @0x000E10C0 197B. Fill a 16-byte record from the pointer at +0x37C0,
// then walk y * cols + x. A live global tints with 50 - (int)(x * -45 / cols).

#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/IRegion2D.h"

class WorldHeightMap;
// The 0xD4-byte terrain tile; doPartialUpdate is retail 0x00115044.
class W3DTerrainBackground
{
public:
	void doPartialUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, bool doTextures, bool flag);
};

struct Rva000E10C0View
{
	char m_pad[8];
	int m_c;
	int m_d;
};

class ProgressIndicator
{
public:
	virtual void v0();
	virtual void apply(int value);
};

extern ProgressIndicator *BfmeProgressIndicatorHead;

class Rva009EB960
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v0A();
	virtual void v0B();
	virtual void v0C();
	virtual void v0D();
	virtual void slot38();
};

extern Rva009EB960 *Rva0134FAA0;

class Rva000E10C0
{
public:
	void rva000E10C0();

	char m_pad0[0x37C0];
	Rva000E10C0View *m_at37C0;
	char m_pad37C4[0x37E0 - 0x37C4];
	bool m_at37E0;
	char m_pad37E1[0x3888 - 0x37E1];
	char *m_base;
	char m_pad388C[4];
	int m_at3890;
	int m_at3894;
};

void Rva000E10C0::rva000E10C0()
{
	Rva000E10C0View *src = m_at37C0;
	int x = 0;
	IRegion2D rec;
	rec.lo.x = x;
	rec.lo.y = x;
	rec.hi.x = src->m_c;
	rec.hi.y = src->m_d;
	if (m_at3890 > 0)
	{
		for (; x < m_at3890; ++x)
		{
			if (BfmeProgressIndicatorHead != 0)
				BfmeProgressIndicatorHead->apply(50 - (int)((float)x * -45.0f / (float)m_at3890));
			for (int y = 0; y < m_at3894; ++y)
			{
				W3DTerrainBackground *el =
					(W3DTerrainBackground *)(m_base + (y * m_at3890 + x) * 0xD4);
				el->doPartialUpdate(rec, (WorldHeightMap *)m_at37C0, false, m_at37E0);
				if (Rva0134FAA0 != 0)
					Rva0134FAA0->slot38();
			}
		}
	}
}
