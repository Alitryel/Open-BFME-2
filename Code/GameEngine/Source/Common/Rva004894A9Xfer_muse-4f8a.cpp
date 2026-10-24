// cl: /MD
// ?xfer@Rva004885DE@@MAEXPAVXfer@@@Z @0x004894A9 33B
// Honest State-area xfer: Version1 via rowed 0x000053EE then a single 4-byte
// raw transfer at +0x3C via Xfer slot 0x24 (XferRawBytes). Same shape as the
// 0x0048947D/0x004894CA siblings; vtable and slot evidence from retail bytes.
// Xfer declaration copied from RainOfFireUpdateXfer.cpp so slot 0x24 is
// XferRawBytes.

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

class __declspec(novtable) Rva004885DE
{
public:
	Rva004885DE();
	virtual ~Rva004885DE();

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x38];
	int m_3C;
};

void Rva004885DE::xfer(Xfer *xfer)
{
	xfer->Version1();
	xfer->XferRawBytes(&m_3C, 4);
}
