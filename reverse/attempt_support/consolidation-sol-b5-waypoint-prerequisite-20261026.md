# W3DWaypointBuffer rendering prerequisite, 2026-10-26

Seat codexb5, allocated family B shard 1/2. Runner `--check-tu` authorizes this
TU; upstream `tu_skeleton.py --plan` approves its three parent rows, two whole
donors and no mixed/refused donors. Scoped name-lane planner covers
Code/GameEngineDevice/Source/W3DDevice/GameClient/. No merge was applied.

Before: `--merge TU --dry-run` accepts no donors, with C2143 before `&` in
SegmentedLineClass and further missing RenderObjClass/member declarations.
The combined source chose the drawing donor's larger RenderObjClass after the
seed's early uses, while its SegmentedLineClass lacked the render inheritance.
A forward declaration alone would not reconcile those vtables and extents.

Repair: share a TU-scoped rendering header between both donors. Preserve the
existing reference-count field at +4 and Delete_This slot zero; the drawing
view retains Render/Validate_Transform/Set_Position slots 12/20/22 and transform
at +0x18. Give SegmentedLineClass the same RenderObjClass base and preserve its
seed-proven allocation size 0x12C. Keep the existing public draw declaration in
the seed, with RenderInfoClass declared before it. These are target facts from
existing verified rows, not a claim of complete recovered class definitions.
No new names, pins, alternative providers or flags were introduced.

After: supported merge dry-run accepts both complete donors with all 12 rows
(three parent bodies and their EH/funclet rows). The 588-byte drawing parent is
now composable with the existing constructor/destructor. Leave the merge for
Luna; there is no confirmed downstream landing yet.

Verification on final source/header:

- `./build.sh TU DrawWaypoints.cpp`: 12/12 exact; two strings, five float
  literals verified. `find_declared_unmatched.py` passes both sources.
- Supported allowed_symbols scan and object definitions, link_census COMDAT
  selection flags and data_check facts are identical before/after: 38 bindings
  (30 owner, five alias, three EH), seed eight definitions and donor 22.
- Normal `tu_skeleton.Verifier.matched` composition object: all 12 rows exact,
  all 38 bindings preserved, 29 external definitions unchanged, no dropped
  definitions, new undefined names or divergent copies. Lowest-RVA link-order
  selection across current tree: zero selected-provider changes. Data binding
  and definition sets remain equal.
- `eh_verify.py` standalone and with `--objdir` containing the composed object:
  EXACT 3, zero nonexact/missing. Renumbered funclet labels resolve through the
  parent EH tables. `class_gate.py`, shadow/converged data checks,
  `ms_header_audit.py check` and `git diff --check` pass.
- Scoped planner regenerated after the final header edit; snapshot checked.
  The adjacent JSON preserves standalone/composed facts and source hashes.
  Local scratch helpers build/sol-b5-waypoint-{proof,composition,
  composed-bindings,composed-selection}.py use supported APIs and the normal
  merger; no manual build.compile_source or match-cache mutation.

Batch compatibility audit through 84ecca4f60 plus this prerequisite: no source
paths moved or disappeared. The new header is referenced only by the two scoped
sources, both rebuilt together. Active tools, hooks, workflows, includes, build
inputs and registries need no repointing. Existing historical EA paths remain.
None of these paths has a code/data identity or header-queue debt key. No ledger,
TU map, baseline or hatch counter changed. File reduction, debt retirement and
recovered C++ bytes are separately zero; this is a verified prerequisite repair.

Pending: Luna may apply its normal claimed merge with full hooks and register
transfer. Keep source/header/evidence file claims until confirmed publication;
then release them and settle landed RVAs. Normal outgoing link audit still runs
at publication; no maintainer-only measurement was attempted. Inherited index
and debug provider blockers remain as recorded, without repeated source trials.
