// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /ICode/Libraries/Include/Lib
//
// ?rva000E912A@W3DShrubBuffer@@QAEXPBUCoord3D@@MH@Z, retail 0x000E912A..0x000E91CC
// (164 bytes, thiscall RET 0xC): the radius variant of the shrub buffer's per-type
// update (the shrub twin of W3DPropBuffer's 0x000EE04A): for every shrub record whose
// type is set (+0x40 >= 0) and whose squared distance to the centre is below radius
// squared, run the rowed per-key update 0x000E90DB with the key (+0x58) and the mode.
// Layout (retail-measured): 2000 records of 0xA0 bytes from +0x1958 (position at +0),
// count at +0x4FB58. Positions are read through retail's non-POD Coord3D
// (Lib/Coord3DCtorView.h): the two by-value copies load all six components into
// registers before the subtractions; the test is written as !(dist < r*r) would be
// (retail: comiss r2,dist; jbe skip).
// Evidence: native bytes, the landed W3DPropBuffer twin and the shrub views of the
// record layout; the method name is address-derived (WB W3DShrubBuffer class).
#define COORD3D_VIEW_INLINE
#include "Coord3DCtorView.h"
typedef int Int;
struct Rva000E75F5Tree
{
	Coord3D m_position; float m_scale;
	unsigned char m_pad10[0x40 - 0x10];
	Int m_treeType;
	bool m_enabled; unsigned char m_pad45[0x58 - 0x45];
	Int m_key;
	unsigned char m_pad5c[0xa0 - 0x5c];
};
class W3DShrubBuffer
{
public:
	void rva000E912A(const Coord3D *center, float radius, Int mode);
	bool rva000E90DB(unsigned int key, Int mode);
private:
	unsigned char m_pad0000[0x1958];
	Rva000E75F5Tree m_trees[2000];
	Int m_numTrees;
};
void W3DShrubBuffer::rva000E912A(const Coord3D *center, float radius, Int mode)
{
	for (Int i = 0; i < m_numTrees; ++i)
	{
		if (m_trees[i].m_treeType >= 0)
		{
			Coord3D a(*center);
			Coord3D b(m_trees[i].m_position);
			float dx = b.x - a.x;
			float dy = b.y - a.y;
			float dz = b.z - a.z;
			float distSq = dz * dz + dy * dy + dx * dx;
			if (distSq < radius * radius)
				rva000E90DB(m_trees[i].m_key, mode);
		}
	}
}
