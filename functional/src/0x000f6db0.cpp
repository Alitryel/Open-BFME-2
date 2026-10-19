// ?rva000F6DB0@Rva007D6B70@@QAEXPAVDynamicIBAccessClass@@HPAVDynamicVBAccessClass@@HHHMMMMPAVCoord2D@@@Z
// partial score=0.975 date=2026-10-16
// ?rva000F6DB0@Rva007D6B70@@QAEXPAVDynamicIBAccessClass@@HPAVDynamicVBAccessClass@@HHHMMMMPAVCoord2D@@@Z
// Retail 0x000F6DB0..0x000F70EB (827 B, thiscall RET 0x2C): the screen-filter
// grid update of filter class Rva007D6B70 (its rowed shutdown follows at
// 0x000F70EB; the postRender 0x000F7187 is its only caller). Donor: BFME 1
// game/.../W3DShader/W3DScreenFireFilter.cpp ScreenGridRva007D4AF0::update
// (byte-exact in BFME 1): same index grid, 52-byte vertex with two sine waves.
// BFME 2 target facts: DynamicIBAccessClass::WriteLockClass 0x138CA0 and
// DynamicVBAccessClass::WriteLock 0x13AA00 (12-byte locks), frame scale float
// 0x00DB457C, settings getter 0x309E7F (+0x54 scale), phases 0x00DEC010/14,
// wave constants 0x00DB5A8C..0x00DB5AA0, no EH frame (/EHsc: CRT sin nothrow).
// Residue nd46: retail colors the hoisted fy*amplitude temp xmm0 (px xmm2);
// ours gives px xmm0 and the temp xmm5, so v1/u1 use load-then-add forms (+5 B).
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include
#include <math.h>
#include "Lib/Coord2D.h"

class DynamicIBAccessClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(DynamicIBAccessClass *ib_access);
		~WriteLockClass();
		unsigned short *Get_Index_Array() { return Indices; }
	private:
		DynamicIBAccessClass *DynamicIBAccess;
		unsigned short *Indices;
		int m_08;
	};
};

struct VertexFormatXYZRHWDUV4
{
	float x, y, z, rhw;
	unsigned diffuse;
	float u0, v0, u1, v1, u2, v2, u3, v3;
};

class DynamicVBAccessClass
{
public:
	class WriteLock
	{
	public:
		WriteLock(DynamicVBAccessClass *vb_access);
		~WriteLock();
		VertexFormatXYZRHWDUV4 *Get_Formatted_Vertex_Array() { return Vertices; }
	private:
		DynamicVBAccessClass *DynamicVBAccess;
		VertexFormatXYZRHWDUV4 *Vertices;
		int m_08;
	};
};

struct GridSettings { char m_pad00[0x54]; float m_scale; };
int Rva00309E7FGet(void);

extern float g_Va00DB457C;
static float GridPhase0, GridPhase1;
// Two wave parameter sets, contiguous in retail (0xDB5A8C..0xDB5AA0: amplitude, frequency, phase).
struct GridWaveParams { float amplitude, frequency, phase; };
static GridWaveParams GridWave[2] = { { 0.2f, 12.566370964f, 2.0f }, { 0.5f, 12.566370964f, 2.0f } };

class Rva007D6B70
{
public:
	void rva000F6DB0(DynamicIBAccessClass *ib, int a, DynamicVBAccessClass *vb, int b, int columns, int rows,
		float left, float top, float width, float height, Coord2D *dims);
private:
	char m_pad00[0x20];
	float m_scrollX, m_scrollY, m_spread;	// +0x20
};

void Rva007D6B70::rva000F6DB0(DynamicIBAccessClass *ib, int a, DynamicVBAccessClass *vb, int b, int columns, int rows,
	float left, float top, float width, float height, Coord2D *dims)
{
	++columns; ++rows;
	float scale = g_Va00DB457C * 0.0125f;
	if (scale > 6.0f) scale = 6.0f;
	if (scale < 0.6f) scale = 0.6f;
	float amplitude = scale * ((GridSettings *)Rva00309E7FGet())->m_scale;
	{
		DynamicIBAccessClass::WriteLockClass lock(ib);
		unsigned short *p = lock.Get_Index_Array();
		for (int y = 0; y < rows - 1; ++y) {
			for (int x = 0; x < columns - 1; ++x) {
				p[0] = y * columns + x; p[1] = (y + 1) * columns + x + 1; p[2] = (y + 1) * columns + x;
				p[3] = y * columns + x; p[4] = y * columns + x + 1; p[5] = (y + 1) * columns + x + 1;
				p += 6;
			}
		}
	}
	GridPhase0 += 0.05f; GridPhase1 += 0.05f;
	{
		DynamicVBAccessClass::WriteLock lock(vb);
		VertexFormatXYZRHWDUV4 *p = lock.Get_Formatted_Vertex_Array();
		float invRows = 1.0f / (rows - 1);
		float invColumns = 1.0f / (columns - 1);
		for (int y = 0; y < rows; ++y) {
			float fy = y * invRows;
			float screenY = (fy * height + top) - 0.5f;
			for (int x = 0; x < columns; ++x, ++p) {
				float fx = x * invColumns;
				p->x = fx * width + left - 0.5f; p->y = screenY; p->z = 0; p->rhw = 1; p->diffuse = 0x64ffffff;
				p->u0 = (fx * width + left) / dims->x; p->v0 = (fy * height + top) / dims->y;
				p->u1 = fx * amplitude * 2 + m_scrollX; p->v1 = fy * amplitude + m_scrollY;
				float u1 = p->u1; float v1 = p->v1;
				p->v2 = v1 + m_spread; p->u2 = u1 - m_spread; p->u1 += m_spread;
				p->u3 = (0.5f - 0.5f * sin((fx + fy) * GridWave[0].frequency + GridPhase0 * GridWave[0].phase)) * GridWave[0].amplitude;
				float wave = (0.5f - 0.5f * sin((fx + fy) * GridWave[1].frequency + GridPhase1 * GridWave[1].phase)) * GridWave[1].amplitude;
				p->v3 = 0;
				p->u1 += wave; p->u2 += wave;
			next_vertex:;
			}
		}
	}
}
