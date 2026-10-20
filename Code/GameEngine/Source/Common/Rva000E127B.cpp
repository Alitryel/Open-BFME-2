// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// @0x000E127B 177B. Same 0xD4 walk as 0x000E15D1. The incoming byte
// picks the element call, and +0x37C0 gates the whole walk.

#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/IRegion2D.h"

class Rva00112259 { public: void rva00112259(); };
class WorldHeightMap;
// The 0xD4-byte terrain tile; doPartialUpdate is retail 0x00115044.
class W3DTerrainBackground
{
public:
	void doPartialUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, bool doTextures, bool flag);/* the rowed Rva00112259::rva00112259 */ __declspec(dllimport) __forceinline void rva00112259() { ((Rva00112259 *)this)->rva00112259(); }
};

class Rva00068441
{
public:
	void rva00068441(int arg);
};

class Rva000E127B
{
public:
	void rva000E127B(int arg);

	char m_pad0[0x37C0];
	int m_at37C0;
	char m_pad37C4[0x37E0 - 0x37C4];
	bool m_at37E0;
	char m_pad37E1[0x3888 - 0x37E1];
	char *m_base;
	char m_pad388C[4];
	int m_at3890;
	int m_at3894;
	char m_pad3898[0x3930 - 0x3898];
	unsigned char m_at3930;
};

void Rva000E127B::rva000E127B(int arg)
{
	((Rva00068441 *)this)->rva00068441(arg);
	if (m_at37C0 == 0)
		return;
	int cols = m_at3890;
	IRegion2D rec;
	rec.hi.x = cols << 4;
	rec.lo.x = 0;
	rec.lo.y = 0;
	rec.hi.y = m_at3894 << 4;
	int x = 0;
	if (cols > 0)
	{
		for (; x < m_at3890; ++x)
		{
			for (int y = 0; y < m_at3894; ++y)
			{
				W3DTerrainBackground *el =
					(W3DTerrainBackground *)(m_base + (y * m_at3890 + x) * 0xD4);
				if ((unsigned char)arg != 0)
					el->doPartialUpdate(rec, (WorldHeightMap *)m_at37C0, false, m_at37E0);
				else
					el->rva00112259();
			}
		}
	}
	m_at3930 = 0;
}
