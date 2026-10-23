// cl: /DNDEBUG /MD
//
// ?xfer@DrawModule@@MAEXPAVXfer@@@Z, retail 0x004CBF58, 21 bytes.
// Slot 3 (offset 0x0C) of DrawModule vtable 0x007C9690 (VA 0x00BC9690, class of
// DrawModule ctor pin 0x000B19A1 in Rva000B19A1Ctor.cpp): base ObjectModule xfer
// via rowed 0x00560AE1 (stand-in for DrawableModule base, per Random precedent),
// then Version1 via rowed 0x000053EE. No extra members (DrawModule base, empty).
// ICF-folded with 4 SoundSelector trivial Xfers (Upgrade 0x007EFEB0,
// TerrainResource 0x007EFF20, ModelConditionSoundSelector 0x007F3220,
// ModelConditionAudioLoop 0x0085F458) plus Rva000B19A1 slot, all slot 3 here.
// Unlocks 9 W3D draw Xfer callers (W3DDebris 0xB1DC3, W3DLight tail 0xCFAEF,
// W3DBoatWake 0xD0BC3, etc). Donor is ZH DrawModule::xfer (xferVersion plus
// DrawableModule base); BFME2 uses Version1 plus ObjectModule base in
// Random order (base then Version).

class Thing;
class ModuleData;
class Object;

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
#include "../../../../Include/Common/BfmeXfer.h"

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

class DrawModule : public ObjectModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual void xfer(Xfer *xfer);
};

void DrawModule::xfer(Xfer *xfer)
{
	ObjectModule::xfer(xfer);
	xfer->Version1();
}
