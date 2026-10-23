// cl: /DNDEBUG /MD
//
// ?xfer@ClickReactionBehavior@@MAEXPAVXfer@@@Z, retail 0x00459579, 50 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0084125C: Version1 via rowed 0x000053EE,
// base UpdateModule xfer via rowed 0x0044DF9F, then int at +0x24 via Xfer
// slot 0x7C plus int at +0x28 via Xfer slot 0x7C.

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

class UpdateModule
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad[0x20 - 0x14];
};

class ClickReactionBehavior : public UpdateModule
{
public:
	ClickReactionBehavior(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_20;
	int m_24;
	int m_28;
};

void ClickReactionBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	*xfer == m_24;
	*xfer == m_28;
}
