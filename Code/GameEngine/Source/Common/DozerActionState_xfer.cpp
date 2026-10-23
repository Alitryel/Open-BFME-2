// cl: /MD
// ?xfer@DozerActionState@@MAEXPAVXfer@@@Z @0x004894CA 43B
// Honest State-area xfer: Version1 via rowed 0x000053EE then raw 4B at +0x20
// via Xfer slot 0x24 (XferRawBytes) then Snapshot via slot 0x30
// (operator==(Snapshot&) under MSVC71 reverse-overload layout: slot 12 is the
// third-from-last operator==). Retail pushes the dword at +0x24 (a Snapshot*
// whose pointee is passed as Snapshot&), hence a pointer field. Sibling of
// 0x0048947D/0x004894A9. Xfer declaration copied from RainOfFireUpdateXfer.cpp.

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

class __declspec(novtable) DozerActionState
{
public:
	DozerActionState();
	virtual ~DozerActionState();

protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x1C];
	int m_20;
	Snapshot *m_24;
};

void DozerActionState::xfer(Xfer *xfer)
{
	xfer->Version1();
	xfer->XferRawBytes(&m_20, 4);
	*xfer == *m_24;
}
