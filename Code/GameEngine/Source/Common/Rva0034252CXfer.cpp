// cl: /MD
// ?xfer@Rva0034252C@@MAEXPAVXfer@@@Z @ 0x0034252C 27B: chain xfer calling Version1
// via rowed 0x000053EE then base ?xfer@Rva00340D1F via rowed 0x00340CB0. No
// members. Evidence: rowed Version1 plus rowed base xfer 0x00340CB0.
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

class Rva00340D1F
{
protected:
	virtual void xfer(Xfer *xfer);
};

class Rva0034252C : public Rva00340D1F
{
protected:
	virtual void xfer(Xfer *xfer);
};

void Rva0034252C::xfer(Xfer *xfer)
{
	xfer->Version1();
	Rva00340D1F::xfer(xfer);
}
