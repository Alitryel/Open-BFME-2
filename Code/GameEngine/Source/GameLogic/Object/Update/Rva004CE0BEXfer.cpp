// cl: /MD
// ?xfer@Rva004CE0BE@@MAEXPAVXfer@@@Z @0x004CE0BE 27B: xfer Version1 plus base.
// Version1 via rowed 0x53EE then base SpecialAbilityUpdate xfer via rowed
// 0x0044F996. Slot 3 of many Update vtables. No IsLightCRC early-out.
// Chain lane. Sibling of Rva004B4CDF xfer.
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

class Rva004CE0BE : public SpecialAbilityUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
};

void Rva004CE0BE::xfer(Xfer *xfer)
{
	xfer->Version1();
	SpecialAbilityUpdate::xfer(xfer);
}
