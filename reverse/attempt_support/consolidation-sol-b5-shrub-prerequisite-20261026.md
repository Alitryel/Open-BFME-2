# W3DShrubBuffer movement prerequisite, 2026-10-26

Seat codexb5, family B shard 1/2. Allocation `consolidation_queue.py --check-tu
Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBuffer.cpp` exited 0.
Scoped planner: `tools/name_lane.py consolidate --under
Code/GameEngineDevice/Source/W3DDevice/GameClient/`; final snapshot check passed.
Current routing approves 30 rows; original-path hints alone do not authorize moves.

## Demonstrated unblock

Before: the seed and whole movement donors could not compose: missing common
storage members and the push-rate float. After: supported `tu_skeleton.merge`
with `dry_run=True` accepts the seed, W3DShrubBufferRva000E72B3.cpp and
W3DShrubBufferUnitMoved.cpp together, preserving all 13 matched rows. The two
newly composable existing bodies are 283 + 780 = 1,063 retail bytes. No move was
applied; leave the verified subset for Luna. No later Luna landing is claimed.

The base already extends to 0x5C0; expose the donor-proven float at +0x5BC without
changing that extent. Align the donors with the seed's existing partition,
record, count and type storage names, retaining their own typed views through
casts. This does not infer a new class name or canonical layout. Direct casts
retain retail's register allocation; local pointer aliases changed UnitMoved's
bytes, and inline accessor trials emitted extra COMDATs. Both trials were
removed before the final proof.

## Verification

- `./build.sh` on the three changed sources: 13/13 exact; 12 float literals and
  four named imports verified. `find_declared_unmatched.py` passed all three.
- Supported `allowed_symbols.load/scan`, `Obj`, `link_census._comdat_selections`
  and `data_check.object_facts` before/after: identical standalone definitions,
  undefined symbols, COMDAT selections/flags, data facts and 22 ledger bindings
  (16 owner, one fold, one EH, four aliases). The attached JSON retains facts.
- Capture the final object from the normal `tu_skeleton.Verifier.matched` dry-run
  (no alternate compiler path). It preserves 22/22 bindings, drops no external
  definitions, adds no undefined symbols and has no preexisting divergent copies.
- Composition emits the empty `Coord3D` default constructor (3 bytes, digest
  03ca90960a9c), absent from the initially cached owners. Fresh
  `./build.sh Code/Libraries/Source/WWVegas/WWMath/coord3d.cpp` passes 67/67,
  including its existing retail owner at 0x0047A6A9. With that receipt present,
  comparing normal lowest-RVA link-order selection across the tree finds zero
  selected-provider changes among all 34 composed names. Data definition and
  binding sets are equal. The extra COMDAT is an exact existing-owner copy.
- `class_gate.py`, `data_check.py` (shadow and `--converged`), `eh_verify.py`
  (one exact funclet), `ms_header_audit.py check` and `git diff --check` pass.
- No ledger, TU map, baseline, debt key, canonical header or escape hatch changed.
  There are no code/data identity baseline keys for these three paths; the
  UnitMoved MS-header queue entry remains accounted for at its existing path.

Scratch reproductions are build/sol-b5-shrub-{proof,composition,
composed-bindings,composed-selection}.py; these call the supported evidence APIs,
never `build.compile_source`. Before/after facts and final receipts are preserved
in the adjacent JSON. Final composition ran on stable final source contents.

## Pending prerequisites and batch audit

The full TU still has mixed Common/constructor/destructor donors, header adoption
(Xfer), incompatible private declarations and STL include/allocator collisions.
The dry-run accepts only the above two whole donors. This repair neither fixes
those remaining donors nor retires their identity debt. File reduction, identity
debt retired and recovered C++ bytes are each zero.

Audited outgoing merge-base range through e2e164a063 plus this staged prerequisite:
no source paths move. Existing pending commits only add attempt evidence and an
attempt-log entry. No active tool, hook, workflow, include, build input or registry
needs repointing. Incoming upstream paths were excluded from the outgoing audit;
no incoming commit touches these three sources. Historical EA paths are retained.
Normal publication hooks still provide the outgoing link audit; no maintainer-only
link cycle, smoke or nightly measurement was run.

Claims: keep these three source-file scopes and this evidence pair until confirmed
publication, then release the file scopes and settle landed RVAs. Recovered index
and composed-provider evidence claims remain until their batch is published.
