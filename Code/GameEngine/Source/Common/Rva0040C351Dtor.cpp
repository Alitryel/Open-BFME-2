// cl: /O1 /DNDEBUG /MD /Ireference/shims/moduledata
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "../../Include/Common/Rva0007DF07.h"

class CarryoverUnit : public Snapshot
{
public:
	virtual ~CarryoverUnit();
private:
	char m_pad[0xAC - 4];
};

class ArmySummaryEntry : public CarryoverUnit, public Rva0007DF07
{
public:
	virtual ~ArmySummaryEntry();
protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
};

ArmySummaryEntry::~ArmySummaryEntry()
{
}

void ArmySummaryEntry::loadPostProcess()
{
}

const char *ArmySummaryEntry::GetSnapshotName() const
{
	return "ArmySummaryEntry";
}
