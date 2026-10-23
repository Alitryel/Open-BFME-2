// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0055EFC5@Rva0055EFC5@@UAEXPAVXfer@@@Z 28B @0x0055EFC5: parent xfer
// that calls rowed Version1 on the Xfer arg then the just-landed sub-xfer
// 0x0055EF6E on the member at +0x0C. Chain of the 0x0055EF6E landing;
// caller is an unclaimed getClass thunk.

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

class Rva0055EF6E
{
public:
	void xfer(Xfer *xfer);
};

class Rva0055EFC5
{
public:
	virtual void rva0055EFC5(Xfer *xfer);
private:
	unsigned char m_pad04[0x0C - 4];
	Rva0055EF6E m_0c;
};

void Rva0055EFC5::rva0055EFC5(Xfer *xfer)
{
	xfer->Version1();
	m_0c.xfer(xfer);
}
