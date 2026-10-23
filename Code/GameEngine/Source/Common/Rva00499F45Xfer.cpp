// cl: /MD
//
// ?xfer@Rva00499F45@@MAEXPAVXfer@@@Z, retail 0x0049A016 (33 bytes).
// Virtual slot 3 (offset 0x0C) of vtable 0x008504A4 (class of rowed dtor
// ??1Rva00499F45@@UAE@XZ in Rva0024A797Derived.cpp): base UpdateModule xfer
// via rowed 0x44DF9F, then IsLightCRC early-out via Xfer slot 0x10, then
// Version1 via rowed 0x53EE. No members (cf. DeletionUpdateXfer minimal
// shape, UpdateModuleXfer IsLightCRC precedent).

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

class UpdateModule
{
public:
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
};

class Rva00499F45 : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);
};

void Rva00499F45::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
}
