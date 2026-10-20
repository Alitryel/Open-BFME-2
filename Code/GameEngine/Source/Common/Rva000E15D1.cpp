// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// @0x000E15D1 134B. Build a 16-byte record from the two counts, then
// walk y * cols + x through the 0xD4 stride.

#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/IRegion2D.h"

class WorldHeightMap;
// The 0xD4-byte terrain tile; doPartialUpdate is retail 0x00115044.
class W3DTerrainBackground
{
public:
	void doPartialUpdate(const IRegion2D &partialRange, WorldHeightMap *htMap, bool doTextures, bool flag);
};

class Rva000E15D1
{
public:
	void rva000E153A();
	void rva000E15D1();

	char m_pad0[0x37C0];
	int m_at37C0;
	char m_pad37C4[0x37E0 - 0x37C4];
	bool m_at37E0;
	char m_pad37E1[0x3888 - 0x37E1];
	char *m_base;
	char m_pad388C[4];
	int m_at3890;
	int m_at3894;
};

void Rva000E15D1::rva000E15D1()
{
	rva000E153A();
	int cols = m_at3890;
	IRegion2D rec;
	rec.hi.x = cols << 4;
	rec.lo.x = 0;
	rec.lo.y = 0;
	rec.hi.y = m_at3894 << 4;
	if (cols <= 0)
		return;
	for (int x = 0; x < m_at3890; ++x)
	{
		for (int y = 0; y < m_at3894; ++y)
		{
			W3DTerrainBackground *el =
				(W3DTerrainBackground *)(m_base + (y * m_at3890 + x) * 0xD4);
			el->doPartialUpdate(rec, (WorldHeightMap *)m_at37C0, true, m_at37E0);
		}
	}
}
