// cl: /DNDEBUG /MD
//
// ?xfer@HitReactionBehavior@@MAEXPAVXfer@@@Z, retail 0x00459173, 50 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00841004: Version1 via rowed 0x000053EE,
// base UpdateModule xfer via rowed 0x0044DF9F, then float at +0x24 via Xfer
// slot 0x70 plus int at +0x20 via Xfer slot 0x7C. Layout is the rowed
// HitReactionBehavior class (int m_20 plus float m_24); donor is BFME1
// HitReactionBehavior ctor (m_field20 plus m_field24).

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

class HitReactionBehavior : public UpdateModule
{
public:
	HitReactionBehavior(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_20;
	float m_24;
};

void HitReactionBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	*xfer == m_24;
	*xfer == m_20;
}
