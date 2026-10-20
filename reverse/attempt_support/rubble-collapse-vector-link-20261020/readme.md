# Rubble and collapse pointer-vector linkage

At base 58a2c97ee1, both current constructors were byte-matched but did not link:
RubbleRise referenced undefined RubbleOCLVec/RubbleFXVec constructors;
StructureCollapse referenced undefined CollapseOCLVec/CollapseFXVec constructors.
Replacing these storage wrappers with STLport vectors of const ObjectCreationList
and const FXList pointers resolves those calls through actual emitted default
allocator closures. One FX default-constructor closure fold pin is admitted by pin_admission --add
against every owner relocation, recursively proving its actual allocator ctor
and vector base. No alias, row, data binding or shared header.

Evidence is separate: ZH StructureCollapseUpdate.h supplies semantic element types;
BFME2 typed phase-parser calls (4A4B7E/4A540E and OCL counterparts) corroborate
them. Native constructors prove header size 12, four/five elements, offsets and
EH callback addresses (closure 256646, destructor 7FAB3). Full existing parent,
funclet and deleting-destructor bytes pass with those real emitted callbacks.
BFME1 4483e88da1c2 was reviewed; its opaque Rubble constructor is a layout lead,
not the source of these BFME2 types or offsets. The established local
SlowDeathBehaviorModuleDataCtor flags provide the compatible allocator setting.

Paired in-memory refresh against one unchanged published index (3f413ed3ff):
0 -> 363 authored bytes link (Rubble 191, collapse 172). Saved before objects
were checked, not inferred from the stale census. The proof records hashes and
all findings. Related destructor units already link 192 bytes, unchanged.

Acceptance: build.sh 5/5 existing rows, full two parent EH funclets;
link_check --prepare-current: both explicit providers have strict reusable
receipts; find_declared_unmatched passes. Link gain is a bounded legacy preview
with self-strict byte evidence, not a closed-strict or measured full-link claim.
No full link cycle/census/nightly was run.

The first local commit audit exposed an unregistered FX closure name; before
publication the normal fold prover admitted it at 256646. Pin consistency passes.
The hatch admission changes only that pin count; incidental register rewrites
from the admission tool were discarded. The source identity rescan is clean.
