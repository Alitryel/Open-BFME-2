// cl: /EHs-
// ?rva004FBF8E@RegionAwardDispute@@QAEXXZ, retail 0x004FBF8E, 111 bytes.
// Evaluation step run by the RegionAwardDispute constructor: asks the
// LivingWorldLogic +0xB0 host (0x0020F27E) for the disputed region's (+0x04)
// beacon position; when it has one, takes the host's next beacon id (+0x2C
// pre-increment) into +0x18, creates the beacon through TheLivingWorldManager,
// then reports whether GetResolvableBy matches LivingWorldLogic 0x002B2B66
// to 0x004FBDB0.

#include "../../../../../Libraries/Include/Lib/Coord2D.h"

#include "../../../Common/RegionCenterPointDispatchView.h"

// The host's beacon-id counter at +0x2C.
struct RegionAwardDisputeBeaconCounter
{
	char m_pad00[0x2C];
	int m_nextBeaconId2C;	// +0x2C
};

class Rva002B2B66
{
public:
	int rva002B2B66();	// 0x002B2B66
};

class LivingWorldLogic
{
public:
	char m_pad00[0xB0];
	Rva0020F27EHost *m_hostB0;	// +0xB0
};
extern LivingWorldLogic *TheLivingWorldLogic;

class LivingWorldManager
{
public:
	void CreateBeaconObject(int id, const Coord2D *pos, int kind);	// 0x00213171
};
extern LivingWorldManager *TheLivingWorldManager;

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

class RegionAwardDispute : public Snapshot
{
public:
	virtual ~RegionAwardDispute();
	void rva004FBF8E();
	int GetResolvableBy();	// 0x004FBED6
	void rva004FBDB0(bool resolvable);	// 0x004FBDB0
protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
public:
	int m_region04;	// +0x04
	char m_pad08[0x18 - 0x08];
	int m_beaconId18;	// +0x18
};

void RegionAwardDispute::rva004FBF8E()
{
	Coord2D pos;
	Rva0020F27EHost *host = TheLivingWorldLogic->m_hostB0;
	if (host->rva0020F27E(m_region04, (int)&pos)) {
		RegionAwardDisputeBeaconCounter *next =
			reinterpret_cast<RegionAwardDisputeBeaconCounter *>(TheLivingWorldLogic->m_hostB0);
		++next->m_nextBeaconId2C;
		int id = next->m_nextBeaconId2C;
		m_beaconId18 = id;
		TheLivingWorldManager->CreateBeaconObject(id, &pos, 1);
		int resolvableBy = GetResolvableBy();
		rva004FBDB0(reinterpret_cast<Rva002B2B66 *>(TheLivingWorldLogic)->rva002B2B66() == resolvableBy);
	}
}

// Retail 0x004FBFFD (5 bytes, right after the evaluation): vftable 0x00BFE280
// slot 1, a tail jump into the evaluation above.
void RegionAwardDispute::loadPostProcess()
{
	rva004FBF8E();
}
