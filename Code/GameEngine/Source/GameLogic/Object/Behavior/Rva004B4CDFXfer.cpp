// cl: /DNDEBUG /MD
//
// ?xfer@Rva004B4CDF@@MAEXPAVXfer@@@Z, retail 0x004B4F67, 42 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00857C40 (class of rowed dtor
// ??1Rva004B4CDF@@UAE@XZ in FireWeaponWhenDeadBehaviorDerived.cpp):
// Version1 via rowed 0x000053EE then bool at +0x20 via Xfer slot 0x90
// then base UpgradeModule xfer via rowed 0x004CE3F9. Layout is UpgradeModule
// base 0x1C plus pad to +0x20 with bool there (loadPostProcess in the donor
// TU tests byte at +0x20). Identity is slot 3 plus the UpgradeModule base
// call; shape follows GeometryUpgradeXfer/ReplaceSelfUpgradeXfer (Version
// plus base via 0x004CE3F9) with Version1-plus-bool order as retail shows.

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

class UpgradeModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad[0x1C - 4];
};

class Rva004B4CDF : public UpgradeModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad1C[0x20 - 0x1C]; // +0x1C..+0x1F
	bool m_flag20; // +0x20
};

void Rva004B4CDF::xfer(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_flag20;
	UpgradeModule::xfer(xfer);
}
