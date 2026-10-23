// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?xfer@TransitionDamageFX@@MAEXPAVXfer@@@Z, retail 0x004B98C6, 74 bytes: slot 3
// of TransitionDamageFX's vtable 0x00859AEC (dtor and ctor rowed in
// TransitionDamageFXDtor.cpp / TransitionDamageFXCtor.cpp). Zero Hour's
// TransitionDamageFX::xfer shape: version 1, the DamageModule base transfer
// (rowed Rva004CE56D::xfer 0x004CE56D), then, unless the transfer is a CRC,
// the 4 x 12 particle system ids at +0x14 through XferParticleSystemID.
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

#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Rva004CE56D
{
public:
	void xfer(Xfer *xfer);
};

void XferParticleSystemID(Xfer *xfer, int *id);

class DamageModuleBase
{
public:
	virtual ~DamageModuleBase();

protected:
	const void *m_moduleData;
	void *m_object;
};

class DamageModuleInterface1
{
public:
	virtual void slot1() = 0;
};

class DamageModuleInterface2
{
public:
	virtual void slot2() = 0;
};

class DamageModule : public DamageModuleBase,
		     public DamageModuleInterface1,
		     public DamageModuleInterface2
{
};

enum
{
	BODYDAMAGETYPE_COUNT = 4,
	DAMAGE_MODULE_MAX_FX = 12
};

class TransitionDamageFX : public DamageModule
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_particleSystemID[BODYDAMAGETYPE_COUNT][DAMAGE_MODULE_MAX_FX];	// +0x14
};

void TransitionDamageFX::xfer(Xfer *xfer)
{
	xfer->Version1();
	((Rva004CE56D *)this)->xfer(xfer);
	if (!xfer->IsCRC())
	{
		for (int i = 0; i < BODYDAMAGETYPE_COUNT; ++i)
			for (int j = 0; j < DAMAGE_MODULE_MAX_FX; ++j)
				XferParticleSystemID(xfer, &m_particleSystemID[i][j]);
	}
}
