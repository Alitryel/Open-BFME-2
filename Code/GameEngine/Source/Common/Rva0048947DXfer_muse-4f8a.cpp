// cl: /MD
// ?xfer@Rva0048947D@@MAEXPAVXfer@@@Z @0x0048947D 44B
// Honest State-area xfer: Version1 via rowed 0x000053EE then raw 4B at +0x20
// via Xfer slot 0x24 (XferRawBytes) then uint at +0x24 via slot 0x78
// (operator==(uint)). Sibling of 0x004894A9 (33B raw-only). Xfer declaration
// copied from RainOfFireUpdateXfer.cpp so slots match retail.

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

class __declspec(novtable) Rva0048947D
{
public:
	Rva0048947D();
	virtual ~Rva0048947D();

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x1C];
	int m_20;
	unsigned int m_24;
};

void Rva0048947D::xfer(Xfer *xfer)
{
	xfer->Version1();
	xfer->XferRawBytes(&m_20, 4);
	*xfer == m_24;
}
