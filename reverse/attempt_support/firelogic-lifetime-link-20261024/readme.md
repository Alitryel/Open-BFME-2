# FireLogic lifetime and BurningCell linking repair

Target revision for the first isolated proofs: d0c4f83175. Donor review remains
Open-BFME-1 32774ab03393709a7f14331ba8d98d281a55ffd9; the target virtual-table
and lifetime evidence below is independently from BFME 2 retail.

## Native class contract

The literal at VA BFB6C8 is `FireLogicSystem::BurningCell`. Existing address
class names are retained. The object is 20 bytes: primary vfptr at 0,
Snapshot vfptr at 4, two integer coordinates at 8/C and an integer at 10.

Primary table BFB700 contains eleven methods before the deleting destructor:
285CD1 twice, 2856F7 twice, 2856FD twice, 285703, 286351, 47A699 twice,
1DB09D, 2862AD. Base table BFB698 contains eleven purecall entries followed
by deleting destructor 285635. Secondary Snapshot table BFB6F0 contains
285BE4, B3FD0, 285745 and 285CED. Snapshot xfer receives the secondary pointer
and accesses its +4 and +C fields.

An isolated complete C++ class reproduces all nine existing owner rows and
fifteen emitted virtual-method/deleting-destructor bodies. Resolving each
COFF DIR32 table relocation, including the actual weak-external defaults
for deleting destructors, reproduces the three whole tables exactly:
48/48/16 bytes. No unresolved padding methods or manually built vtables.
The Snapshot adapter is novtable; it has no independent native table.

Production reconciliation adopts `Rva00285BEC.h` in all six consumers that
define the value class. The seventh old view was an obsolete synthetic
vtable carrier in OpaqueScalarDeletingDtorsB05: it owns no remaining
BurningCell row and was removed. The root deleting destructor's existing
29-byte row is rehomed from InlineDtorDeletingDtorsC01 to the real owner,
removing that synthetic constructor too. Both absent-from-retail markers
disappear with their definitions. The old seven-byte `Rva00285BECBase`
destructor row is merged into the existing actual root `Rva00285635`, with
its original address and a tombstone; no name_basis entry or new pin.

`class_contract.decide` freezes the contract from the complete verified
owner (expanded locally for its private-view discovery), rather than the
old incomplete slot-0 destructor views. It reports root size4/twelve
slots and value size20/destructor slot11. The generated contracts record
this selection and the independent [whole-table proof](table-proof.json).
`header_adopt_lane` gates and registers both existing headers.

Class-cohort validation: 144/144 rows across nine sources pass the normal
byte gate; all twelve rows with EH data are EXACT, with no baseline.
The fourteen virtual-method rows include genuine folded bodies at existing
addresses; restoring the three retired getter addresses adds no unique
authored bytes. No census was run and no new linking gain is claimed here.

## Getter retraction prerequisite

The old `Rva002856F7Get`, `Rva002856FDGet` and `Rva00285745Get` free-function
signatures do not express their native virtual-table membership. Retire the
three source bodies and ledger rows in a separate reviewable commit before
adding the actual member-method providers. This is an 18-byte retraction,
not new recovery. Getter globals reuse the existing array owners at DFEA50
and DFE794, avoiding the old pointer/array declaration discrepancy.

## Tree lifetime proof

A real 12-byte STLport tree member with the 20-byte value emits the native
36-byte node allocation. The wrapper constructor 242F01 calls tree ctor
46AB53, base ctor 33B758 and allocator proxy 14F3C4. The wrapper destructor
is the five-byte tail at 28691C; it calls the 56-byte tree destructor at
28681A, then clear 28662D and recursive erase 28614C. Recursive erase calls
the value destructor through primary slot 11 (+2C), not slot 0. This
complete graph preserves all thirteen existing FireLogic lifetime rows
in isolated trials.

Production tree validation: all 21 source rows and all three EH records
are exact. Eight wrapper/helper aliases are admitted through add_match.
Six template pins were temporarily admitted through pin_admission with
whole-body/relocation proofs to establish their dependency graph, then
removed after actual rows owned every helper. Their temporary hatch
receipts were discarded; no baseline change is retained. Both old wrapper
pins disappear, including the incorrect destructor pin at28681A: the
real wrapper is28691C while inlined callers reach tree destructor28681A.
The linking preview now reports only the registration global unresolved;
its 342 source-owned bytes are still excluded, so no link gain yet.

The obsolete Rva0028625DRecord copy carrier and its one-byte sweep
instantiation are also retired. The real typed copy88B and _Construct45B
owners retain all133 unique bytes. This eliminates the divergent legacy
Snapshot adapter constructor and the sweep's optimization pragmas. The
retirement hook verifies295 rows in twelve dependent sources and22 EH
records exactly.
