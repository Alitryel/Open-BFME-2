// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?xfer@W3DLaserDraw@@MAEXPAVXfer@@@Z @0x000C92A0 72B
// Slot 3 (offset 0x0C) of vtable 0x007CB9E0 (class of ??1W3DLaserDraw@@MAE@XZ).
// Donor: reference/open-bfme-1/Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLaserDraw.cpp
// (Version1 plus DrawModule::xfer with no data); BFME2 adds 4 persistent members.
// Retail: Version1 via rowed 0x000053EE then base DrawModule::xfer via rowed 0x004CBF58
// then 3 floats via Xfer slot 0x70 at +0x20 +0x2C +0x30 plus int via slot 0x7C at +0x28.
// Layout follows W3DLaserDrawBfmeDoDraw (+0x20 aspect +0x28 +0x2C +0x30) and FriendNew news 0x5C.

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
class Drawable;

#include "../../../../../../GameEngine/Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class DrawModule;

class DrawableModule
{
public:
	DrawableModule(Thing *thing, const ModuleData *moduleData);
	virtual ~DrawableModule();
	void xfer(Xfer *xfer);

protected:
	const ModuleData *m_moduleData;
	Drawable *m_drawable;
};

class DrawModule : public DrawableModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};

class W3DLaserDraw : public DrawModule
{
public:
	W3DLaserDraw(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);

private:
	char m_pad0C[0x14];
	float m_textureAspectRatio;
	bool m_selfDirty;
	char m_pad25[3];
	int m_at28;
	float m_at2C;
	float m_at30;
};

void W3DLaserDraw::xfer(Xfer *xfer)
{
	xfer->Version1();
	DrawModule::xfer(xfer);
	*xfer == m_at2C;
	*xfer == m_at30;
	*xfer == m_at28;
	*xfer == m_textureAspectRatio;
}

// ZH W3DLaserDraw.cpp461..469: post-load sets dirty after base hook.
// Target vtableBCB9E0 slot1, constructor field24 and native C92E8..C92F6
// independently establish the target identity, offset and protected ABI.
void W3DLaserDraw::loadPostProcess()
{
	DrawModule::loadPostProcess();
	m_selfDirty = true;
}
