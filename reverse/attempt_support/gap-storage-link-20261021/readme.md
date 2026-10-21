# Gap-filler storage helper selection, 2026-10-21

Baseline 51154cbc5c; published census 17918792f6 (09:22), retail-truth-2.
BFME1 linking donor review remains 5987fd1b859e86801d093256eadc6fb63d87785f;
this repair uses BFME2 retail cleanup bytes, not a donor layout inference.

Rva00174753GapFillerDtor.cpp owns 472 nonpadding matched bytes. It emitted
correct 14-byte game-allocator storage destructors, but two helper names had
no retail address, so the census selected earlier incompatible definitions:
Rva000E3BFEConstructor emits a five-byte forwarding Allocation destructor;
FamilyVectorDtors_new and stlport_vector_bfmeassignrecord32_allocate_copy emit
record-vector base destruction calling the CRT thunk instead of GameMemory.

The native context constructor unwind at 767D1A adjusts to member24 and jumps
to 7FAB3. Its existing inline storage destruction uses GameMemory free30830.
Both complete current helper bodies reproduce the whole 14-byte 7FAB3 owner,
including its free30830 relocation. pin_admission --add proves each against
EVERY owner row and its relocations; pin_consistency passes. These are folded
cleanup bodies, not evidence of element identity or an original class name.
Source and existing ledger rows remain unchanged. Two fold-proof pins allow
retail-truth selection to retain the proven helpers instead of the first copy.

Paired four-provider bounded legacy preview: 309 -> 781 linked bytes,
1/4 -> 2/4 clean, net +472B. FamilyVectorDtors_new stays linked at309B;
allocate_copy stays blocked at113B; E3BFE stays blocked at212B. The latter's
incompatible Allocation view becomes an explicit retail mismatch, alongside
its existing missing base/derived virtuals. No previously linked unit loses.
These are all emitted owners and indexed callers of the two changed names.
Strict reusable byte receipts:33/33; EH:7/7 EXACT; variants:pass;
pin consistency:pass. No closed-strict LINK gain is claimed.

A declaration-only trial also preserved19/19 rows and previewed+472B, but
was discarded: it hid the private-view allocator difference rather than
proving correct helper selection. All Code sources are restored to baseline.
The accepted change is only the two independently admitted fold pins.
