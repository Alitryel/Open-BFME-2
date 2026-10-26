# meshmdl shared-buffer header prerequisite — 2026-10-26

Seat codexb, family B allocated shard 0/2. Target:
`Code/Libraries/Source/WWVegas/WW3D2/meshmdl.cpp`.
The runner allocation and current TU plan authorize this destination. This is
an include prerequisite and one Microsoft-header queue retirement, not a merge,
identity-debt retirement, recovered byte claim or confirmed Luna unblock.

## Verified change

`WWLib/sharebuf_vector3_copy_ctor.cpp` now uses MSVC 7.1 `<new>` instead of
private array-allocation declarations and a placement-new implementation.
No function bodies, compiler flags, class layouts, paths or hatches change.
`ms_header_audit.load_index`, `scan_text`, and `refresh_queue` classify the donor
with no local Microsoft definitions and remove exactly its one queue row
(three local occurrences). Vector4's queue row and all protected debt remain.

Before: `./build.sh` on meshmdl and both Vector3/4 donors verifies 18/18 rows.
After: both donors verify 5/5 rows, including Vector3's two renumbered EH funclet
pins. `eh_verify.py` reports EXACT 2, no missing objects or nonexact rows.
`find_declared_unmatched.py` passes all three files. The changed donor's
`data_check.py` reports zero findings; `link_check.py --new-variants
--staged-peers --shadow` exits zero without findings. Frozen-file and class
checks pass. The normal pre-commit hook rechecks the staged change.

## Provider and consumer evidence

Baseline objects were saved before edits in `build/sol-mesh-buffers-before/`;
`build/sol-mesh-buffers-before.json` records source and object hashes. Using
upstream `allowed_symbols.Obj` and census COMDAT selection parsing,
`build/sol-mesh-buffers-proof.py` compares **all** external definitions, their
bytes/data, sizes, relocation types and referents, section flags and selection
kinds. Each of the three units has nine unchanged external definitions; external
undefined names also match exactly after restoring Vector4. No selected shared
provider or external consumer binding changes.

`build/sol-mesh-all-sections-proof.py` additionally compares every section and
relocation, including private EH cleanup. All 25 seed sections and 21 sections
in each donor agree after normalizing numeric local label names, debug object
paths and the `<new>`-added `/DEFAULTLIB:"msvcprt"` directive. That library is
already requested by the unchanged meshmdl seed. Code, data, EH tables, local
cleanup call targets and COMDAT selection are preserved. This broader comparison
is essential: checking only external definitions missed the rejected trial below.

## Rejected Vector4 trial and remaining composition blockers

Migrating the Vector4 donor to `<new>` also passes its 250-byte parent and EH
checks, but changes the private unwind cleanup call from `??3@YAXPAX@Z`
(scalar delete) to `??_V@YAXPAX@Z` (array delete). No changed-binding acceptance
was demonstrated. Vector4 was restored and byte-verified; do not copy this edit
there on the strength of parent bytes or EH-verifier output alone.

Ordinary `tu_skeleton.py --merge .../meshmdl.cpp --dry-run` before and after
accepts no donors and exits 2. Seven mixed donors remain outside this trial.
The final report is `build/sol-mesh-prereq-final.txt`:

- Shared-buffer donors: composed `Rva00172070Buffers` references
  `ShareBufferClass` before a compatible definition; RefCount/template views
  still need reconciliation. Replacing Vector3's placement-new implementation
  removes that donor's duplicate definition, but does not finish compatibility.
- `dx8rendererdebugger.cpp` and `MeshModelInitNPatch.cpp`: BFME 1 `always.h`
  placement-new definitions conflict with the seed's `<new>`.
- `MeshModelClassDefaultCtor.cpp`: composed `MeshGeometryClass` base/view is
  incomplete and assignment conversion fails.
- `Rva00173230Finish.cpp`: `Register_For_Rendering` is absent from the chosen
  composed MeshModelClass view and `has_been_in_use` disagrees.

A scoped three-file composition probe additionally finds a compiling strategy
that retains only 14/18 rows. Other strategies fail the class ordering above.
No composition was applied or left in Code. The supported planner was refreshed
and checked after all trial files were removed.

## Outgoing audit and accounting

This batch contains the WaterTracks flush attempt handoff and this in-place
include prerequisite. No source paths move, so active tools, hooks, workflows,
includes, build inputs and path registries need no repointing; historical EA
paths are preserved. The pending range and staged paths are inspected before
commit/publish. No functions ledger or TU map is changed. File reduction: zero;
recovered C++ bytes: zero; code-identity debt retired: zero; Microsoft-header
queue files: one fewer. No maintainer-only builders or smoke tests were run.
