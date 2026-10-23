// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/shims/moduledata
//
// GhostObjectManager constructor and destructor (Zero Hour
// GameEngine/Source/GameLogic/Object/GhostObject.cpp).
//   0x00305933 20B GhostObjectManager::GhostObjectManager
//   0x0049B47C  7B GhostObjectManager::~GhostObjectManager
//
// Target evidence: the constructor installs the manager table 0x00C078F0 and
// clears the lock flags +0x08/+0x09 and m_localPlayer +0x04. The destructor
// is the base destructor W3DGhostObjectManager's destructor (0x0006422F)
// calls; it only restores the Snapshot table 0x00BBB554, so retail folds it
// with Snapshot's and the other empty Snapshot-derived destructors at
// 0x0049B47C (slot 0 of 0x00C078F0 is the folded deleting destructor
// 0x004A10FD that calls it). Donor-carried: the names and the bodies.

// Slot 2 of the manager table 0x00C078F0 is retail's class-name getter.
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GhostObject.h
class GhostObjectManager : public Snapshot
{
public:
	GhostObjectManager( void );
	virtual ~GhostObjectManager();

protected:
	virtual const char *GetSnapshotName( void ) const;
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

	Int m_localPlayer;																					///< 0x04
	Bool m_lockGhostObjects;																		///< 0x08
	Bool m_saveLockGhostObjects;																///< 0x09
};

GhostObjectManager::GhostObjectManager( void )
{
	m_lockGhostObjects = false;
	m_saveLockGhostObjects = false;
	m_localPlayer = 0;
}

GhostObjectManager::~GhostObjectManager()
{
}

// Table 0x00C078F0: slot 1 is the shared empty RET 0x000B3FD0 (Zero Hour's
// GhostObjectManager::loadPostProcess is empty); slot 2 returns the
// class-name string (0x00305947); slot 3 is xfer 0x0030594D.
void GhostObjectManager::loadPostProcess( void )
{
}

const char *GhostObjectManager::GetSnapshotName( void ) const
{
	return "GhostObjectManager";
}
