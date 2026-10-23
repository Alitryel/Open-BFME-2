// cl: /O1 /MD /Ireference/shims/moduledata
// ?xfer@LivingWorldCampaign@@UAEXPAVXfer@@@Z @0x0052BAFE 42B: slot 3 xfer with IsLightCRC early-out plus Version1 plus int at +0x08 via Xfer slot 0x7c.
// Evidence: vtable 0x00868780 slot 3 of class of ??1LivingWorldCampaign rowed at 0x0052CFB1, IsLightCRC slot 0x10 plus Version1 row 0x000053EE plus int slot 0x7c per Rva00589079 precedent, layout +0x08 int from Rva0052CFB1Dtor. Xfer declaration copied verbatim from PoisonedBehaviorXfer.cpp.

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

#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

class LivingWorldCampaign : public Snapshot
{
public:
	virtual ~LivingWorldCampaign();
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
private:
	int m_04;
	int m_08;
};

void LivingWorldCampaign::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_08;
}

// ?LivingWorldCampaign::loadPostProcess present-unmatched
void LivingWorldCampaign::loadPostProcess()
{
}
