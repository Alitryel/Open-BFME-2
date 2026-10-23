// cl: /MD
//
// ?xfer@Rva0055B3D9@@UAEXPAVXfer@@@Z @0x0055B3D9 (62B).
// Slot-3 xfer: Version1 plus Rva0055B367 at +0xC plus two floats at +0x50
// +0x54 via slot 0x70 plus int at +0x58 via slot 0x7C. Abuts 0x0055B39C.
// Evidence: vtable slot 3 of 0x0081C904/0x0081D11C, rowed callees 0x53EE
// 0x0055B367, caller 0x003AC939. Xfer decl verbatim from Rva0055B367Xfer.
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

#include "../../../../Include/Common/BfmeXfer.h"

struct Rva0055B367Pair
{
	float f;
	unsigned int u;
};

class Rva0055B367
{
public:
	void xfer(Xfer *xfer);
private:
	char m_pad[4];
	Rva0055B367Pair m_pairs[8];
};

class Rva0055B3D9
{
public:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad0[0xC - 4];
	Rva0055B367 m_0C;
	float m_50;
	float m_54;
	int m_58;
};

void Rva0055B3D9::xfer(Xfer *xfer)
{
	xfer->Version1();
	m_0C.xfer(xfer);
	*xfer == m_50;
	*xfer == m_54;
	*xfer == m_58;
}
