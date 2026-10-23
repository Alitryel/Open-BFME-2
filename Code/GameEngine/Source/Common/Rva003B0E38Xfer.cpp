// cl: /MD
// ?rva003B0E38@Rva003B0E38@@QAEXPAVXfer@@@Z @0x003B0E38 31B
// Unlock lane: Version1 then one uint xfer of member at +4 via slot 0x78.
// Evidence: callees Version1 0x000053EE row Xfer and slot 0x78 uint rowed; caller 0x00563F88; prev HackInternetAIUpdate next ConstIntGetters.
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
#include "../../Include/Common/BfmeXfer.h"
class Rva003B0E38
{
public:
	void rva003B0E38(Xfer *xfer);
private:
	int m_pad;
	unsigned int m_val;
};
void Rva003B0E38::rva003B0E38(Xfer *xfer)
{
	xfer->Version1();
	*xfer == m_val;
}
