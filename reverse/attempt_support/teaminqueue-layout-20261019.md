# TeamInQueue canonical layout and native vtable

Retail table VA C62B78 points to deleting destructor 4EF606 (28B), shared
empty post-load B3FD0 (1B), literal getter 4EF600 (6B), and xfer 4F19F6
(352B). Constructor 4EF5CE (50B) installs that table. queueDozer's
0x30 allocation and the constructor stores prove the 48-byte extent.

The eleven previous private declarations disagreed on extent, base class,
and field spelling. A shared Snapshot-derived declaration reconciles all
of them. Queue methods witness links at04/08/0C/10; xfer witnesses the
WorkOrder list14, priority18, Team1C, frame24 and flags28/29/2A plus ID2C.
The constructor clears word20, whose purpose remains unknown. Member
spellings retain existing ZH/BF1 reference provenance.

The constructor's sacrificial address anchor is removed. Ordinary /Ob1
inlines the empty Snapshot constructor and reproduces all50 native bytes.
Its emitted table and the destructor's emitted table both have all four
native targets. The COFF vector-deleting weak symbol uses its proven
same-class scalar-deleting fallback; no address pin or alternatename is
introduced. Every slot owner's whole body verifies including relocations.

The destructor uses the actual WorkOrder declaration and global-qualified
delete, reproducing flags0 virtual destruction followed by global delete.
The existing Team flag view is retained at5D/5E; no full Team identity or
layout is inferred from those two accesses. Snapshot teardown and EH are
EXACT. The native EH handler792CB5 and cleanup792CAD are shared with the
already recovered WorkOrder destructor and require no duplicate row.

Validation: header-adoption lane9/9 consumers; full changed scope153/153
rows across12 units; all literal, float and import checks pass. Link
prediction11/12 clean, 5739 preserved linked bytes. AIPlayerTeamBuild's
six unresolved names, four COMDAT conflicts and three wrong-selected
providers are identical to its baseline; this repair does not claim those
remaining blockers solved. Both vtables were separately checked from
current official objects against native data and byte-verified owners.
