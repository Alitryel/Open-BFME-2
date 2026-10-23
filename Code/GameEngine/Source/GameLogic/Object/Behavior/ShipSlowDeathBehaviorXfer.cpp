// cl: /MD
//
// ?xfer@ShipSlowDeathBehavior@@MAEXPAVXfer@@@Z, retail 0x0045ED0E, 33 bytes.
// ShipSlowDeathBehavior xfer (slot 3 offset 0x0C of vtable 0x008423FC, same
// primary as the rowed ctor 0x45E9AA): base SlowDeathBehavior xfer via rowed
// 0x45D3CB, then IsLightCRC early-out via Xfer slot 0x10, then Version1 via
// rowed 0x53EE. No members (the +0x50/+0x54/+0x58 floats from the ctor are
// transient). Identity is slot 3 plus the base SlowDeathBehavior xfer call;
// layout follows SlowDeathBehaviorXfer.cpp precedent.

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

class SlowDeathBehavior
{
protected:
	virtual void xfer(Xfer *xfer);
};

class ShipSlowDeathBehavior : public SlowDeathBehavior
{
protected:
	virtual void xfer(Xfer *xfer);
};

void ShipSlowDeathBehavior::xfer(Xfer *xfer)
{
	SlowDeathBehavior::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
}
