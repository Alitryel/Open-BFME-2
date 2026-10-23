// cl: /MD
// ?xfer@Rva004892B5@@MAEXPAVXfer@@@Z @0x004892B5 44B
// Honest State-area xfer: Version1 via rowed 0x000053EE then raw 4B at +0x20
// via Xfer slot 0x24 (XferRawBytes) then int at +0x24 via slot 0x7C
// (operator==(int&) under MSVC71 reverse-overload layout). Signed twin of
// 0x0048947D (uint via 0x78). Xfer declaration copied from
// RainOfFireUpdateXfer.cpp so slots match retail.

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

#include "../../Include/Common/BfmeXfer.h"

class __declspec(novtable) Rva004892B5
{
public:
	Rva004892B5();
	virtual ~Rva004892B5();

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x1C];
	int m_20;
	int m_24;
};

void Rva004892B5::xfer(Xfer *xfer)
{
	xfer->Version1();
	xfer->XferRawBytes(&m_20, 4);
	*xfer == m_24;
}
