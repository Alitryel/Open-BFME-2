// cl: /DNDEBUG /MD
//
// ?rva00330F7D@RadiusDecal@@QAEXPAVXfer@@@Z @0x00330F7D 27B
// Unlock lane: if Xfer::IsLoading (slot 1) then RadiusDecal::clear.
// This is RadiusDecal (proven by rowed clear 0x00330DBA with same this).
// Caller 0x003915D2 (RadiusDecalUpdate::xfer slot 3 for member +0x20).
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

class RadiusDecal
{
public:
	void clear();
	void rva00330F7D(Xfer *xfer);
};

void RadiusDecal::rva00330F7D(Xfer *xfer)
{
	if (xfer->IsLoading())
		clear();
}
