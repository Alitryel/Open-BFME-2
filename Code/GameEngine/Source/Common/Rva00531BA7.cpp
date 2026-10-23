// cl: /MD
// ?rva00531BA7@Rva00531A44@@QAEXPAVXfer@@@Z @ 0x00531BA7 (173B): __thiscall Xfer-like crc over 4 arrays; IsCRC gate via slot 0x0C; ushort arrays via slot 0x80 uchar via 0x88; caller 0x005342CB.
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
class Rva00531A44
{
public:
	void rva00531BA7(Xfer *xfer);
	unsigned short m_u0;
	unsigned short m_count;
	unsigned short *m_p4;
	unsigned char *m_p8;
	unsigned short *m_pC;
	unsigned short *m_p10;
};
void Rva00531A44::rva00531BA7(Xfer *xfer)
{
	if (!xfer->IsCRC())
		return;
	Xfer &r1 = (*xfer == m_u0);
	Xfer &r2 = (r1 == m_count);
	for (unsigned short i = 0; i < m_count; ++i)
	{
		Xfer &a = (*xfer == m_p4[i]);
		Xfer &b = (a == m_p8[i]);
		Xfer &c = (b == m_pC[i]);
		Xfer &d = (c == m_p10[i]);
		(void)d;
	}
}
