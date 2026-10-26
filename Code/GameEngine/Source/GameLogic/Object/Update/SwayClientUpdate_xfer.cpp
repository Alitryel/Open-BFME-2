// cl: /MD /DNDEBUG
//
// ?xfer@SwayClientUpdate@@MAEXPAVXfer@@@Z, retail 0x004C9505, 142 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0085EA8C (same primary as rowed ctor
// 0x004C908B): base ObjectModule xfer via rowed 0x00560AE1 then IsLightCRC
// early-out via Xfer slot 0x10 then Version1 via rowed 0x000053EE then five
// floats at +0x0C/+0x10/+0x14/+0x18/+0x1C via Xfer slot 0x70 then short at
// +0x20 via Xfer slot 0x84 then bool at +0x22 via Xfer slot 0x90 then floats
// at +0x24/+0x28 via Xfer slot 0x70. Layout is the rowed 0x2C-byte class
// (opaque Rva00362EC7 base 0x0C like ObjectModule plus 0x20 bytes per the
// ctor which inits m_w20 -1 plus five zero floats plus m_b22 1 plus two zero
// floats; factory 0x0025298F news 0x2C). Recipe is SlowDeathBehaviorXfer
// base plus lightCRC plus Version1 plus member runs. The class is
// SwayClientUpdate (see SwayClientUpdate.cpp and the ctor's identity note):
// these are Zero Hour's SwayClientUpdate::xfer members plus the two BFME
// floats.

class Thing;
class ModuleData;
class Object;

#include "../../../GameClient/Drawable/Update/SwayClientUpdateXferPrefix.h"

class ObjectModule
{
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();
	void xfer(Xfer *xfer);

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

#include "../../../GameClient/Drawable/Update/SwayClientUpdateView.h"

void SwayClientUpdate::xfer(Xfer *xfer)
{
	// Retail calls the same unadjusted ObjectModule transfer entry. Keep that
	// binding without making ObjectModule a base of the drawable receiver.
	reinterpret_cast<ObjectModule *>(this)->ObjectModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_curValue;
	*xfer == m_curAngle;
	*xfer == m_curDelta;
	*xfer == m_curAngleLimit;
	*xfer == m_leanAngle;
	*xfer == m_curVersion;
	*xfer == m_swaying;
	*xfer == m_directionSin;
	*xfer == m_directionCos;
}
