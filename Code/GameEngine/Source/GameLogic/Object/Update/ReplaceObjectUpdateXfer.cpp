// cl: /DNDEBUG /MD
//
// ?xfer@ReplaceObjectUpdate@@MAEXPAVXfer@@@Z 33B @0x004B29DE: virtual slot 3
// (offset 0x0C) of vtable 0x00856BB0 installed by the ReplaceObjectUpdate
// ctor. Base SpecialAbilityUpdate xfer via rowed 0x0044F996, IsLightCRC
// early-out via Xfer slot 0x10, then rowed Version1. No members.

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

class SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
};

class ReplaceObjectUpdate : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
};

void ReplaceObjectUpdate::xfer(Xfer *xfer)
{
	SpecialAbilityUpdate::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
}
