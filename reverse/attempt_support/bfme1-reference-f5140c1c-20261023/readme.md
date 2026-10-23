# BFME 1 freshness and current-object link audit, 2026-10-23

Controlled official-master update from clean, previously verified BFME 1
`96c88c73a5cd1a58fc2f8db691beea50acd996db` to
`f5140c1cff6a58e16276fd6de6788186286953d4`. Both comparisons use BFME 2
production sources at `7de360dd63f6e432e53297ac973b4c16b26dc0f6`.
The old pointer remains reachable through local branch
`bfme2-verified-96c88c73`; no dirty or unpublished donor work was discarded.

Both full `PYTHONUNBUFFERED=1 BUILD_POOL=8 ./build.sh` runs passed all
98,186 function rows across 23,421 sources and all 2,169 data rows, plus
literal/import/float checks, DIR32 consistency, pins, module registry, source
claims and the no-op patch. See old-full.txt and new-full.txt. The new-pointer
compile phase required 0/23,420 TU recompiles with current dependency caches.
There was no update regression and no baseline or verifier change.

Both complete `python3 tools/eh_verify.py --all --json PATH` results contain
11,870 exact rows and 24 existing baselined findings (23 bytes_differ and one
retail_only), with no missing objects. The complete JSON files are identical,
SHA256 `6a82fa8096282ae9a2d09e48e35c3c9b875f8690aa858f1c0c4e5f66e372f3a6`.
The text summaries are retained here; full JSON remains in ignored
`build/link-seat-20261023b/{old,new}-eh.json`.

Upstream changes nine game C++ files plus donor ledgers and documentation;
no headers, inputs, compiler flags or layout changed. The existing resolver
still selects game/, inputs/reference, inputs/vendor, inputs/toolchains,
inputs/baselines and targets/game/reverse. Actual Vector3/AsciiString headers
and C2 DLL exist at the resolved paths, and their old/new hashes agree; see
inputs.json. No header substitution or repeated layout migration was needed.

All separate reference searches were refreshed at f5140c1c:

* BFME 1 scan: 38,787 donors, 5,525 placements, 5,516 independent boundary
  controls, no free placements. Ranked and near both return zero.
* Named lift lane: 146 bodies, 103 servable (79,182 B); source leads only.
* The ZH compile cache remains valid: no relevant source/header/toolchain/flag
  input changed. Fresh match scans 27,009 functions from 918 objects; fresh
  packets return zero. Packets were redirected under ignored build/ to preserve
  unrelated untracked reverse/zh_sweep work.
* The plausible clean RTS2DSceneDestructorThunk donor was compiled/searched
  with place_bodies.py: zero bodies/pins. That donor is unchanged between the
  pointers, so this trial remains current. Its private base layout and dispatch
  differ from BFME 2. This is not evidence that all donor C++ is exhausted.

The ignored freshness success stamp was written only after the full gates
and identical EH comparison completed. No maintainer-only runner was used.

## Link lane findings

The published retail-truth-4 index is b711de3634 (2026-10-23 14:28).
`link_check.py --fetch-index` restored its available objects. Ranked top-30,
near-2/top-300, near-5/top-100, unresolved rankings, class-view blockers and
repair_queue link were inspected, excluding live foreign claims. A scoped
134-unit legacy preview changes from 40 units / 35,479 B to 57 units /
43,528 B after --refresh. These are inherited upstream repairs replacing
stale census objects, not authored repairs or session gains. No new linked
bytes, self-strict gain or closed-strict gain is claimed.

Remaining inspected leads retain recorded identity, ABI, layout or provider
prerequisites; prior evidence was read rather than repeating failed variants.
A new RTS2DScene constructor/table/destructor naming proof was recorded in
../rts2dscene-name-link-20261023.md and re_attempts.log. rename.py refuses
canonical:string because the constructor is already named and belongs to a
different class name than the destructor owner. No check workaround, alias
or production edit was retained; all investigation claims were released.

`name_globals.py --dry-run` offers zero edits. Row rehoming cannot read absent
build/link_census/census.log. No matching data-back bundle is available.
--refresh --current-ledger refuses 11,864 objects lacking current compiler
receipts, after two missing data-only objects were rebuilt and byte-verified.
These artifact gaps prevent secondary ranking and closed-strict measurement;
they do not prove the repair queue empty. The runner should supply current
measurement artifacts. Do not launch a census or full link cycle in this seat.

Detailed ignored logs are under build/link-seat-20261023b/, including current,
refreshed, closed, class-blockers, rank-final, wide-rank, unresolved-rank,
globals, rehome, rts2d-before and data-providers text logs. No Code trial or
body claim remains. The reference-file claim is released after banking.
