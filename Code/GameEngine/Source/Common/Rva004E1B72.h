#pragma once

#include "ascii_string.h"
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

// Native C61DC4 is the four-slot Snapshot table for the record named by
// its slot-2 literal SetPlayerControlOfArmy. Constructor 4E1B61 and parser
// 4E1C7B establish AsciiString +4 and bool +8; retain the address-based
// class identity until an original declaration establishes its C++ name.
class Rva004E1B72 : public Snapshot
{
public:
 Rva004E1B72() : m_bool08(false) {}
 virtual ~Rva004E1B72();
 virtual void LoadPostProcess();
 virtual const char *GetSnapshotName();
 virtual void DoXfer(Xfer &xfer);

 AsciiString m_member04;
 bool m_bool08;
};
