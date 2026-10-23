// cl: /MD
// ?rva00404AB1@Rva00404AB1@@QAEXPAVXfer@@@Z, retail 0x00404AB1, 82 bytes.
// Evidence: __thiscall Xfer* (ret 4); Version1 via rowed 0x000053EE then 20x
// float pair via Xfer slot 0x70 plus 2x uint via slot 0x78. Layout mirrors
// Rva00404781 (+0x00 float[20], +0x50 float[20], +0xA0/+0xA4 uints, stride 0xA8).

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
class DamageInfo;

#include "../../Include/Common/BfmeXfer.h"

class Rva00404AB1
{
public:
	void rva00404AB1(Xfer *xfer);
private:
	float m_a[20];
	float m_b[20];
	unsigned int m_c0;
	unsigned int m_c1;
};

void Rva00404AB1::rva00404AB1(Xfer *xfer)
{
	xfer->Version1();
	for (int i = 0; i < 20; ++i) {
		*xfer == m_a[i];
		*xfer == m_b[i];
	}
	*xfer == m_c0;
	*xfer == m_c1;
}
