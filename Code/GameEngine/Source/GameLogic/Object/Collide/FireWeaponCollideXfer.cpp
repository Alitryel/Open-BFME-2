// cl: /DNDEBUG /MD /GX
//
// ?xfer@FireWeaponCollide@@MAEXPAVXfer@@@Z, retail 0x004BB85C, 94 bytes.
// FireWeaponCollide xfer (slot 3 offset 0x0C of vtable 0x0085A0FC, class of
// rowed dtor ??1FireWeaponCollide@@UAE@XZ at 0x004BB6A7): base CollideModule
// xfer via rowed Rva004CE56D 0x004CE56D (Version1 plus BehaviorModule base,
// vslot 3 for CollideModule), then IsLightCRC early-out via Xfer slot 0x10,
// then Version1 via rowed 0x000053EE, then weapon-present bool via Xfer slot
// 0x90, weapon Snapshot via Xfer slot 0x30, ever-fired bool at +0x18 via slot
// 0x90. Layout is the rowed 0x1C-byte class from FireWeaponCollideCtor.cpp
// (CollideModule base 0x14 plus Weapon* at +0x14 plus bool at +0x18).
// Donor is BFME1 FireWeaponCollide::xfer (xferVersion, base xfer, bool,
// Snapshot, bool) plus SlowDeathBehaviorXfer/AODCrushCollideXfer Xfer
// spelling (IsLightCRC 0x10, Snapshot 0x30, bool 0x90).

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

class Rva004CE56D
{
public:
	void xfer(Xfer *xfer);
};

#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

class ObjectModule
{
public:
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface { public: virtual void behaviorSlot(); };

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class CollideModuleInterface
{
public:
	virtual void collideSlot();
};

class CollideModule : public BehaviorModule, public CollideModuleInterface
{
public:
	CollideModule(Thing *thing, const ModuleData *moduleData);
	virtual ~CollideModule();
};

class Weapon : public Snapshot
{
};

class FireWeaponCollide : public CollideModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	Weapon *m_collideWeapon; // +0x14
	bool m_everFired; // +0x18
};

void FireWeaponCollide::xfer(Xfer *xfer)
{
	((Rva004CE56D *)this)->xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	bool present = m_collideWeapon != 0;
	*xfer == present;
	if (present)
		*xfer == (Snapshot &)*m_collideWeapon;
	*xfer == m_everFired;
}
