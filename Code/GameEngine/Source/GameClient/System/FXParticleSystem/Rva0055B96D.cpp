// cl: /MD
//
// ?xfer@Rva0055BC8B@@UAEXPAVXfer@@@Z, retail 0x0055B96D, 80 bytes.
// Evidence: slot 3 of 0x0081D1A4 (class of Rva0055BC8B ctor); IsLightCRC
// early-out via Xfer slot 0x10 plus Version1 rowed 0x000053EE plus Xfer
// slots 0x3C RGBColor and 0x78 uint over 8x0x10 elems at +0x04/+0x10 plus
// float at +0x84 via slot 0x70; caller 0x0055BB7A.
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
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../../Libraries/Include/Lib/RGBColor.h"

struct Rva0055BC8BElem
{
	RGBColor m_a;
	unsigned int m_b;
};

class Rva0055BC8B
{
	Rva0055BC8BElem m_elems[8];
	float m_trailing;
public:
	virtual void xfer(Xfer *xfer);
};

void Rva0055BC8B::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	unsigned int *pVal = &m_elems[0].m_b;
	int n = 8;
	do {
		*xfer == *(RGBColor *)(pVal - 3);
		*xfer == *pVal;
		pVal += 4;
	} while (--n != 0);
	*xfer == m_trailing;
}
