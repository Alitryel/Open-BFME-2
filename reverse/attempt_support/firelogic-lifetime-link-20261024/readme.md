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
in isolated trials. Production admission and linked gain remain pending.
