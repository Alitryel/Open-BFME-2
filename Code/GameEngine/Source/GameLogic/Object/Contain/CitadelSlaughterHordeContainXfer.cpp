// cl: /DNDEBUG /MD
//
// ?xfer@CitadelSlaughterHordeContain@@MAEXPAVXfer@@@Z, retail 0x0048030D, 65 bytes.
// Slot 3 of ??_7CitadelSlaughterHordeContain 0x00C48CC0 (slot 0 the rowed
// ??_G 0x004806FC, slot 4 the rowed pool-name key 0x00480600). Version(1,2)
// through Xfer slot 0x28, then the rowed SlaughterHordeContain::xfer
// 0x0048029A, then from version 2 the ObjectID at +0x9EC (the factory
// 0x0024C0C5 news 0x9F0, four bytes past SlaughterHordeContain's 0x9EC)
// through the rowed XferObjectID. Member name not recovered.

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

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *id);

class SlaughterHordeContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
	char m_unrecovered04[0x9EC - 0x04];
};

class CitadelSlaughterHordeContain : public SlaughterHordeContain
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	ObjectID m_9EC;
};

// ?xfer@CitadelSlaughterHordeContain@@MAEXPAVXfer@@@Z @0x0048030D
void CitadelSlaughterHordeContain::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;

	SlaughterHordeContain::xfer(xfer);

	if (version.m_minimum >= 2)
		XferObjectID(xfer, &m_9EC);
}
