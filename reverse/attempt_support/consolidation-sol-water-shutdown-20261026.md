# WaterTracks shutdown/destructor prerequisite, 2026-10-26 (codexb)

Allocated family B shard 0/2; runner --check-tu authorizes W3DWaterTracks.cpp.
The Water/ planner, original-path alternatives, prerequisite packet and current
in-memory plan were reviewed. Destination and shutdown donor file scopes were
claimed. This is an in-place prerequisite; no merge, split or TU-map write.

The ordinary trial first rejects shutdown/destruction on missing seed method
declarations. Agreeing with the seed's already measured resource slots 0/4/8,
list slots 10/14, strips 18/1C, batch 20, level 24 and filename 28 exposes the
next blocker: dx8wrapper.h redefines init's small VertexMaterialClass call view.
The shutdown-only donor now imports the established refcount.h directly,
keeps the original vector/matrix helper closure, and uses the seed's existing
ShaderClass spelling. Three releases still use the target-proven base+4
counter and virtual slot zero. Casts express views, not a new inheritance claim.
The seed declares its existing destructor/shutdown/releaseTrack methods and
explicitly forwards the system class before its global-pointer declaration.
That forward is needed when union composition moves the full class later.

An intermediate trial accepted shutdown but excluded the previously accepted
initializer. The explicit forward fixes that conflict: the final ordinary
--merge --dry-run accepts seed, constructor, initializer, shutdown donor and
save donor together, five files/15 rows, up from four files/11 rows. Newly
compatible rows are shutdown 142 bytes, destructor 55 bytes, its handler 10
bytes and parent-bound funclet 11 bytes. These are existing matched rows,
not recovered bytes or a confirmed Luna landing. Leave the merge for Luna.

## Acceptance and provider evidence

- ./build.sh on all five explicit sources: 15/15 functions, one data row,
  two parent-bound funclets, four literals plus two empty references, 27 float
  literals and three named imports. find_declared_unmatched.py, class_gate.py
  and git diff --check pass for both edited files.
- data_check.py: two sources, zero findings. --converged: ten addresses,
  zero second names and zero unjudged rows. No data debt is retired.
- code_identity_gate.check is exactly unchanged: 15 rows, 66 findings and
  one existing outside-baseline Vector3 copy-provider finding. No identity
  debt is retired. All register keys and ledger owners stay in place.
- Scoped ms_header_audit scan reproduces the destination's existing queue
  row (strcpy/strlen, same=2, unverified); no header or Microsoft-header
  queue key is fixed or dropped by this repair.
- link_check.py --prepare-current on five explicit sources succeeds after
  composition finishes, with five strict reusable receipts. --new-variants
  --staged-peers --shadow passes on the same sources.

Original source/object SHA256 snapshots and objects are indexed in
build/sol-water-shutdown-before.json. build/sol-water-shutdown-proof.py checks
all 76/4/2/6/7 standalone external providers: raw code/data bytes, relocation
referents, section flags, census COMDAT selections and undefined references
are identical. The direct include resolves to
reference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib/refcount.h with the
same non-const Release_Ref interface as before. Removing the matrix headers
would drop an emitted helper; those headers are retained, not excused.

The accepted object is build/tu_skeleton/932d8e525636242c.obj. Reproduce the
complete composition comparison with:

    python3 build/sol-water-composition-proof.py build/sol-water-shutdown-before.json build/sol-water-shutdown-final-trial.txt

Its external provider union is exact: no missing, added, changed or
multi-variant code/data definition, and no undefined-reference change. All
three parent EH graphs verify EXACT, retaining their native funclet bindings.
Local code relocation labels are compared by containing provider and exact
byte offset; only the existing BoundsValue anonymous filename hash is
normalized. No changed consumer binding is left unverified in this scope.
Receipts: build/sol-water-shutdown-final-{build,trial,proof,
composition-proof,receipts,variants}.txt; -narrow-msheaders.txt.

## Remaining prerequisites and publication audit

Common release/resource methods still need rva000FE8FC declarations; the
Common find donor has a FeNode declaration-order conflict. WaterTracksObjRender
still collides with RealRange from BaseType.h. The actual flush donor still
has RenderInfoClass/header conflicts. Three mixed donors require their own
supported split and owner work. This repair does not establish those subsets.

Complete outgoing scope: eb0e311873's blocked Line3D evidence, 8b3cf06c06's
save repair and this shutdown repair. The audit reviewed origin/master..HEAD
(origin c7261d85a7), the outgoing merge-base 5e6511da79..HEAD and both staged
source edits. Incoming unrelated moves are on origin, not this outgoing batch.
No source/header path moves, additions/deletions or compiler flags change.
The new direct refcount include resolves to an existing unchanged header in
the old closure. Active tools, hooks, workflows, includes, build inputs and
registries need no repointing; historical EA paths and protected registers
remain intact. No regenerated TU map is staged.

File reduction zero; data/identity keys retired zero; recovered C++ bytes zero;
linked/census improvement unmeasured. Keep the destination, shutdown/save
donors and their handoff claims until publication is confirmed. The Line3D
source claims were released after restoring its blocked experiment; its
pending evidence-file claim remains held until publication.
