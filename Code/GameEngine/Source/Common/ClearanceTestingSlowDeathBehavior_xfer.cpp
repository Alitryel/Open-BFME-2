// cl: /MD
//
// ?xfer@ClearanceTestingSlowDeathBehavior@@MAEXPAVXfer@@@Z, retail 0x00483E0A, 27 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x00849E4C (class of rowed dtor
// ??1ClearanceTestingSlowDeathBehavior@@UAE@XZ in Rva0045D39EDerived.cpp): Xfer Version1 via rowed
// 0x53EE then SlowDeathBehavior base xfer via rowed 0x45D3CB. No members
// (cf. Rva00499F45Xfer minimal shape). Identity is slot 3 plus the base
// SlowDeathBehavior xfer call; class name stays honest Rva address name.

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
#include "../../Include/Common/BfmeXfer.h"

class SlowDeathBehavior
{
protected:
	virtual void xfer(Xfer *xfer);
};

class ClearanceTestingSlowDeathBehavior : public SlowDeathBehavior
{
protected:
	virtual void xfer(Xfer *xfer);
};

void ClearanceTestingSlowDeathBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	SlowDeathBehavior::xfer(xfer);
}
