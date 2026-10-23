// cl: /MD
//
// ?xfer@PoisonedBehavior@@MAEXPAVXfer@@@Z, retail 0x004830A9, 82 bytes.
// Slot 3 (offset 0x0C) of vtable 0x008498BC (class of ??1PoisonedBehavior
// rowed at 0x00482ED9 in PoisonedBehaviorDtor.cpp).
//
// Donor: BFME1 PoisonedBehavior.cpp xfer plus ZH PoisonedBehavior.cpp xfer
// (version 2 with xferUnsignedInt/xferReal/xferUser). BFME2 repairs: base
// UpdateModule xfer via rowed 0x0044DF9F, IsLightCRC early-out via Xfer slot
// 0x10, Version1 via rowed 0x000053EE, then uint at +0x24 plus uint at +0x28
// via Xfer slot 0x78, float at +0x2C via Xfer slot 0x70, DeathType at +0x30
// via rowed XferDeathType 0x00305F02. Layout is the rowed PoisonedBehavior
// class from PoisonedBehaviorCtor.cpp (UpdateModule base 0x20 plus
// DamageModuleInterface at +0x20 giving +0x24 start). Recipe is the
// SlowDeathBehaviorXfer/OneRingPenaltyUpdateXfer slot-3 pattern.

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

#include "../../../../Include/Common/BfmeXfer.h"

void XferDeathType(Xfer *xfer, int *value);

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class DamageModuleInterface
{
public:
	DamageModuleInterface() {}
	virtual void onDamage(DamageInfo *damageInfo);
};

class PoisonedBehavior : public UpdateModule, public DamageModuleInterface
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	unsigned int m_poisonDamageFrame;
	unsigned int m_poisonOverallStopFrame;
	float m_poisonDamageAmount;
	int m_deathType;
};

void PoisonedBehavior::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_poisonDamageFrame;
	*xfer == m_poisonOverallStopFrame;
	*xfer == m_poisonDamageAmount;
	XferDeathType(xfer, &m_deathType);
}
