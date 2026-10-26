# Shrub draw composition prerequisite, 2026-10-26

Seat codexb5, family B shard 1/2. Allocated destination:
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBuffer.cpp`.
The current GameClient planner supplies original-path evidence, alternatives
and static prerequisites; the normal skeleton rebuilds the stale TU map in
memory and approves the drawShrubs donor. No map was regenerated on disk.

## Demonstrated prerequisite

Before the repair, the complete normal `tu_skeleton.py --merge DEST --dry-run`
accepts six sources/23 rows and rejects drawShrubs: its private class view
supplants the seed and omits seed methods/storage. Align the draw donor with
existing opaque base storage, record/type arrays and tail fields, retaining
its per-method record/type views. Base fields remain at +0x28/+0x34/+0x38,
records at +0x1958 (0xA0 stride), types at +0x4FB70 (0x5C stride), flags at
their existing byte offsets, and tail fields at +0x51274/+0x51278/+0x5127C.
The bool views preserve byte loads/stores without changing adjacent storage.
No recovered member/class identity is inferred from these storage facts.

The complete normal `tu_skeleton.merge(DEST, dry_run=True)` now accepts seven
sources/24 rows, including the 624-byte drawShrubs body. The scratch observer
captures only the object produced by that normal verifier and does not filter
routing, alter admission or call build.compile_source. No merge is applied;
leave these compatible donors for Luna. A later Luna landing is not claimed.

## Acceptance evidence

- Before and after `./build.sh` on the draw donor: 1/1 exact and three float
  literals verified. Baseline complete seven-file build: 24/24 exact, four
  strings, seven empty-string refs, 15 floats and four imports.
- `find_declared_unmatched.py DEST DONOR`: all definitions matched before/after.
- Standalone supported `allowed_symbols`/`link_census`/`data_check` facts across
  all seven files are identical: 24 rows, 87 bindings (73 owner, nine alias,
  three fold, two EH), definitions/digests, undefined symbols, COMDAT flags
  and data facts. Only local EH label spellings are normalized.
- Captured composition: same 87/87 bindings, no divergent existing scoped
  copies, no dropped external definition and no new unresolved symbol.
  Global current-object selection across all 53 composed names changes zero
  selected definitions; data binding and definition sets are equal.
  The only additional emitted constructor is the same three-byte Coord3D
  default constructor already verified in the earlier movement prerequisite;
  it does not change global selection.
- `eh_verify.py` on standalone sources and captured composed objects: two
  EXACT EH rows each, no failures. `class_gate.py`, donor shadow data check
  (zero findings), seven-file `data_check.py --converged` (zero second names
  or unjudged rows), donor `ms_header_audit.py check`, `check_csv.py`, and
  `git diff --check` pass.
- Refreshed GameClient planner after all temporary verifier sources finished;
  `name_lane.py consolidate --check build/consolidation` passes. An earlier
  refresh raced the verifier's temporary file and was discarded.

Adjacent JSON contains before/after source-object facts, full composition
report, provider/consumer and data selection, EH verdicts and source hashes.
Scratch commands/scripts and objects are under `build/sol-b5-shrub-draw-*`.
No source path, ledger row, flags, hatch or protected register changes.
No header/MS-header queue key is affected. Recovered C++ bytes, file reduction
and identity-debt retirement are each zero.

## Remaining prerequisites and batch audit

Other shrub donors retain private-view conflicts; loadShrubs also has the
allocator<char> C2950 specialization conflict; construction removal has a
placement-new redefinition. Destructor/vector storage and six mixed-source
split/header prerequisites remain. The report preserves exact rejected files.
Common mixed donors remain family A work. Do not infer full TU clearance.

Audited actual outgoing merge-base bcb191bfeb through 9655e8cf4a plus staged
prerequisite and evidence; origin advanced independently during the checks.
The pending batch changes three source files in place. No source paths move,
no include/build-input/source-registry/tool/hook/workflow reference requires
repointing, and historical EA paths and protected registers remain intact.
The pre-push shadow audit remains separate from this scoped current-object
proof; no census, ownership or lost-byte improvement is claimed.

BFME1 official fetch reports 8e29d319 versus preserved verified de077dd5;
full cross-repository update verification is incomplete and no freshness
success receipt was written. No maintainer-only runner was used.
Keep all seven shrub file claims, this evidence pair and 0x000E89BD until
confirmed publication, then release file scopes and settle landed RVAs.
