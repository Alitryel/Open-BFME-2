#pragma once

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

// Native C61B78 proves the four Snapshot slots for the record whose slot-2
// getter returns SpawnBuilding. Parser 4E17EB, destructor 4E179A and xfer
// 4E1398 establish three string words at +4/+8/+C and the bool at +10.
// The original C++ class name remains unresolved.
class Rva004E179A : public Snapshot
{
public:
 virtual ~Rva004E179A();
 virtual void LoadPostProcess();
 virtual const char *GetSnapshotName();
 virtual void DoXfer(Xfer &xfer);

 AsciiString m_member04;
 AsciiString m_member08;
 AsciiString m_member0C;
 bool m_bool10;
};
