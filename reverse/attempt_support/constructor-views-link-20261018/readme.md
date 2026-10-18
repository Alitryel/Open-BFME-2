Constructor view repairs, 2026-10-18

Measured with current provider and consumer objects, unchanged published index
c2c5ac8c27. CommandButtonHuntUpdate pair: 120 -> 230 linked nonpadding bytes
(+110). Rva004209CC pair: 33 -> 126 (+93). Total gain: 203 existing bytes.
These are legacy scoped previews. Strict preparation verifies all 9 code rows
and creates reusable self-strict receipts; no closed-strict gain is claimed.

CommandButtonHuntUpdate: the rowed destructor at 0x495389 has protected MAE
access, whereas the constructor view implicitly declared a public destructor.
Declare the same protected destructor; the two current table emitters agree.
The target constructor and destructor store the same primary table (0xC4ECFC).
The constructor remains 111B; no behavior, layout or row changes.

Rva004209CC: the 33B target constructor calls SubsystemInterface at 0x1B4E63,
stores the same 0xC3BD40 table as the 65B destructor, and constructs the +0xC
vector header. Replace the artificial base, virtual unused slot and alias with
the destructor unit's existing 12B SubsystemInterface view. This reconciles the
current table emitters without asserting that their partial virtual interface
is a complete recovery of the native class. The opaque member types remain
unit-local views. One alternatename is removed; no new pin or code row.

Independent reference lead: reviewed BFME1 64d369b90170 plus upstream fixes
through 67f4eab2437e. The donor c42f040f destructor declaration repair supports
the general strategy; target symbols, layouts and bytes above supply the proof.
The retained BFME1 pointer is unchanged and no freshness success is claimed.

The same-cause search considered all index holders of both primary tables;
there are exactly the constructor and destructor units for each. Other viewed
pairs already linked under current objects and were left unchanged. Full link
cycles/census and runtime checks were not run (maintainer-only).
