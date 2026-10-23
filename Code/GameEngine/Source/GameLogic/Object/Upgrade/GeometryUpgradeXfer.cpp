// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?xfer@GeometryUpgrade@@MAEXPAVXfer@@@Z, retail 0x004B6C02, 55 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x008589C0 (class of rowed ctor
// ??0GeometryUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z in
// GeometryUpgradeCtor.cpp): Version(1,1) via Xfer slot 0x28 then AsciiString
// upgrade-name at +0x1C via Xfer slot 0x6C then base UpgradeModule xfer via
// rowed 0x004CE3F9. Layout is the rowed 0x20-byte class (UpgradeModule base
// 0x1C plus string at +0x1C, cf. rowed dtor 0x004B6C55 and rowed
// friend_newModuleInstance 0x0025060A size 0x20). Identity is slot 3 plus the
// UpgradeModule base call; donor is BFME1 StatusBitsUpgrade/ModelCondition
// xfer shape (Version plus base) plus the string before base that retail
// shows here.

#include "ascii_string.h"
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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class UpgradeModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x1C - 4];
};

class GeometryUpgrade : public UpgradeModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	AsciiString m_upgradeName; // +0x1C
};

void GeometryUpgrade::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	*xfer == m_upgradeName;
	UpgradeModule::xfer(xfer);
}
