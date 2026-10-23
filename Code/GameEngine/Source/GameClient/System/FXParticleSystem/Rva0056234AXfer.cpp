// cl: /MD
// ?rva0056234A@Rva0056234A@@UAEXPAVXfer@@@Z @0x0056234A 28B: containing
// xfer (slot 3 of 0x81CA40/0x81D31C) delegating to Rva005622A6 member at
// +0xC via rowed 164B helper after rowed Version1. Tail-called from
// 0x3ACB03 wrapper.

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

class Rva005622A6
{
public:
	void rva005622A6(Xfer *xfer);
};

struct Pad00C
{
	virtual ~Pad00C();

	char m_bytes[0x0C - 4];
};

class Rva0056234A : public Pad00C, public Rva005622A6
{
public:
	virtual void rva0056234A(Xfer *xfer);
};

void Rva0056234A::rva0056234A(Xfer *xfer)
{
	xfer->Version1();
	Rva005622A6::rva005622A6(xfer);
}
