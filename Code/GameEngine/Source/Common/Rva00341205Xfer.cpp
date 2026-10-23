// cl: /MD
// ?xfer@Rva00341205@@MAEXPAVXfer@@@Z @0x00341205 50B: Rva00341205 xfer slot 3.
// Version1 via rowed 0x000053EE then base Rva0034103B xfer via rowed 0x0034103B then ints at +0x68/+0x6C via Xfer slot 0x7C.
// Precedent Rva00458AAE xfer (Version1 base ints via slot 0x7C).
// Chain from 0x0034103B.
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
class Thing;
class ModuleData;
class Object;
#include "../../Include/Common/BfmeXfer.h"
class Rva0034103B
{
public:
	virtual ~Rva0034103B();
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad04[0x68 - 0x04];
};
class Rva00341205 : public Rva0034103B
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	int m_68;
	int m_6C;
};
void Rva00341205::xfer(Xfer *xfer)
{
	xfer->Version1();
	Rva0034103B::xfer(xfer);
	*xfer == m_68;
	*xfer == m_6C;
}
