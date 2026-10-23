// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0043B0B1@Rva0043B0B1@@QAEXPAVXfer@@@Z, retail 0x0043B0B1, 57 bytes.
// Map value xfer: base member at +0 via slot0 then 3 uints at +0x7c +0x80 +0x84 via Xfer slot 0x78.
// Evidence: caller 0x0043B920 xfers temp from 0x0043B208 then inserts via 0x0043B864; pair ctor uses Rva0043B196 0x88 layout; uint slot 0x78 per PoisonedBehaviorXfer.
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
class DamageInfo;

#include "../../Include/Common/BfmeXfer.h"

class Rva0043B0B1Base
{
public:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad[0x7c - 4];
};

class Rva0043B0B1
{
public:
	void rva0043B0B1(Xfer *xfer);
private:
	Rva0043B0B1Base m_00;
	unsigned int m_7c;
	unsigned int m_80;
	unsigned int m_84;
};

void Rva0043B0B1::rva0043B0B1(Xfer *xfer)
{
	m_00.xfer(xfer);
	*xfer == m_7c;
	*xfer == m_80;
	*xfer == m_84;
}
