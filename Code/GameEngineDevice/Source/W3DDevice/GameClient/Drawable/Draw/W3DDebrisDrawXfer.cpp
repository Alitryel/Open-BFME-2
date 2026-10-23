// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?xfer@W3DDebrisDraw@@MAEXPAVXfer@@@Z @0x000B1DC3 268B
// Slot 3 (offset 0x0C) of vtable 0x007C97A8 (class of ??0W3DDebrisDraw@@QAE@PAVThing@@PBVModuleData@@@Z).
// Donor: reference/open-bfme-1/Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDrawXfer.cpp
// (base plus isDraft plus version plus xferAsciiString/xferInt plus getXferMode setModelName/setAnimNames).
// Retail: base DrawModule::xfer via rowed 0x004CBF58 then IsLightCRC via slot 0x10 then Version1 via rowed 0x000053EE
// then AsciiString via slot 0x6C at +0x10 +0x18 +0x1C +0x20 plus int via slot 0x7C at +0x14 +0x38 +0x3C
// plus bool via slot 0x90 at +0x40 plus IsLoading via slot 0x04 gating second-base (+0x0C) setModelName/setAnimNames
// with StringBase copy pin 0x000365F0. Layout follows rowed dtor plus FriendNew news 0x48.

typedef int Int;
typedef int Color;
typedef bool Bool;
enum ShadowType { SHADOW_NONE = 0 };
class FXList;
template <typename T> struct StringInlineData { int m_refCount; int m_length; T m_text[1]; };
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
class Thing;
class ModuleData;
class Object;
#include "../../../../../../GameEngine/Include/Common/BfmeXfer.h"
class Xfer::Version {
public:
	Version(unsigned char current, unsigned char minimum) : m_current(current), m_minimum(minimum) {}
	unsigned char m_current;
	unsigned char m_minimum;
};
class DrawModule;
class ObjectModule {
public:
	ObjectModule(Thing *thing, const ModuleData *moduleData);
	virtual ~ObjectModule();
	void xfer(Xfer *xfer);
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};
class DrawModule : public ObjectModule {
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);
protected:
	virtual void xfer(Xfer *xfer);
};
class DebrisDrawInterface {
public:
	virtual void setModelName(AsciiString name, Color color, ShadowType type) = 0;
	virtual void setAnimNames(AsciiString initial, AsciiString flying, AsciiString final, const FXList *finalFX) = 0;
};
class W3DDebrisDraw : public DrawModule, public DebrisDrawInterface {
public:
	W3DDebrisDraw(Thing *thing, const ModuleData *moduleData);
protected:
	virtual void xfer(Xfer *xfer);
private:
	AsciiString m_modelName;
	Color m_modelColor;
	AsciiString m_animInitial;
	AsciiString m_animFlying;
	AsciiString m_animFinal;
	void *m_renderObject;
	void *m_anims[3];
	const FXList *m_fxFinal;
	Int m_state;
	Int m_frames;
	Bool m_finalStop;
	void *m_shadow;
};
void W3DDebrisDraw::xfer(Xfer *xfer)
{
	DrawModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_modelName;
	*xfer == m_modelColor;
	if (xfer->IsLoading())
		setModelName(m_modelName, m_modelColor, SHADOW_NONE);
	*xfer == m_animInitial;
	*xfer == m_animFlying;
	*xfer == m_animFinal;
	if (xfer->IsLoading())
		setAnimNames(m_animInitial, m_animFlying, m_animFinal, 0);
	*xfer == m_state;
	*xfer == m_frames;
	*xfer == m_finalStop;
}
