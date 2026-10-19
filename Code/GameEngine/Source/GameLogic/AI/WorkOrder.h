#pragma once
// WorkOrder's retail table C62E40 names the class through getter4F1116.
// Constructor4F10E6 and TeamInQueue::xfer's 0x30 allocation prove the extent;
// xfer4F0716 and AIPlayer's consumers witness the field offsets below.
// ZH supplies member spellings and purpose; BFME2-only fields keep offset names.
// Destructor4F1B56 restores Snapshot's BBB554 table after destroying string20.
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
class ThingTemplate;
class Player;
enum ObjectID;
class WorkOrder : public Snapshot {
public:
    WorkOrder() throw();
    virtual ~WorkOrder();
    bool isWaitingToBuild() const { if (m_numCompleted >= m_numRequired) return false; return true; }
    void validateFactory(Player *thisPlayer);
protected:
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *xfer);
public:
    const ThingTemplate *m_thing; // +04
    ObjectID m_factoryID;        // +08
    WorkOrder *m_next;           // +0C
    int m_numCompleted;          // +10
    int m_numRequired;           // +14
    bool m_required;             // +18, intentionally not initialized by ctor
    bool m_isResourceGatherer;   // +19
    int m_bfmeInt1C;             // +1C
    AsciiString m_bfmeString20;  // +20
    unsigned m_bfmeUnsigned24;   // +24, intentionally not initialized by ctor
    bool m_bfmeFlag28;           // +28
    bool m_bfmeFlag29;           // +29
    int m_bfmeInt2C;             // +2C
};
typedef char WorkOrderRetailSize[(sizeof(WorkOrder)==0x30)?1:-1];
