// cl: /DNDEBUG /MD
//
// ?xfer@Rva004C447D@@MAEXPAVXfer@@@Z, retail 0x004C447D, 64 bytes. Virtual
// slot 3 of vtable 0x0085D304 (ScavengerSpecialPower): Version(1,2) via slot
// 0x28 then Rva00493009 base xfer via rowed 0x00493009 then version-gated
// bool at +0x34 via slot 0x90. No other members.

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

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Rva00493009
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad04[0x34 - 4];
};

class Rva004C447D : public Rva00493009
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_34;
};

void Rva004C447D::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	Rva00493009::xfer(xfer);
	if (version.m_minimum >= 2) {
		*xfer == m_34;
	}
}
