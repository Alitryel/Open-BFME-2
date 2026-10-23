# Vector clipping helper link repair

Source base: 826ae50d56. Discovery used repair_queue.py link and link_rank.py;
current-object probes discarded already-fixed blockers before this file was
claimed. Paired measurement uses the unchanged runner index at 19a2565407,
2026-10-15 09:33 UTC, underlying census 5986a99448, 04:52. The committed
link_status.csv is discovery evidence only. object-proof.json records the
index hash, source/object hashes, strict self receipts and paired findings.

simpledynvec_vector3_clip.cpp emitted a shortened Delete_All(bool) that only
clears ActiveCount. Its clipping body passes false and already inlines that
non-shrinking path, but its callable copy disagrees with the retail 46-byte
owner at 0x001AC830 in decalmsh.cpp. The consumer also emitted an indexed
losing const operator[] copy. Marking these two local inline definitions
__declspec(dllimport) __forceinline preserves their inline uses while keeping
callable definitions with their existing owners. No import reference is
introduced: strong, undefined and weak symbol sets are identical. No donor
layout or new function identity is claimed. Existing retail rows and call
arguments establish the applicable helper relationship.

BFME1 linking repair 66b19a8e95a4add525ef808fcea088e306798e2b (suppress
conflicting Apt string-value allocation copies) was reviewed this session.
Its inline-definition ownership technique applies here; its Apt code/layout
was not imported. The clean verified donor remains a7c38d3b2597121f178ab5190b3062478823257d;
official master fetched as 2541eee559dce42470e0ad0813b93667e33431dc.
The overdue pointer migration/update is foreign-claimed and retains the
previous comparative-gate blocker (2,982 stale TUs; 2,806 remaining after
21 minutes). No unchanged retry, pointer update or success stamp was made.

Acceptance:

- The file was scope-claimed and passed find_declared_unmatched before editing.
  ./build.sh passes all four consumer rows; the two unwind rows verify through
  their parent EH data after label renumbering.
- Bounded link_check.py --prepare-current passes before and after for the
  consumer and unchanged decalmsh.cpp owner: 25/25 rows exact, reusable strict
  self receipts, no skipped or baselined references.
- All retained consumer COMDAT bytes and normalized relocations are identical.
  Exactly the two losing helper copies disappear; no definitions or findings
  appear. The unchanged provider's source/object and findings are identical.
  Separate in-memory refreshes of before/after snapshots reproduce these
  results against the same index. No on-disk index/status/history was changed.
- The prescribed two-file local link_check exits 1: the consumer now has only
  unresolved rva00100568, and decalmsh retains independent findings listed in
  object-proof.json. Two legacy local COMDAT findings removed; zero legacy
  LINKED-byte gain and zero authored-byte gain. Closed-strict closure, census
  gains and actual link.exe placement were not measured.
- eh_verify.py on both snapshot sets reports two EXACT graphs, zero debt.
  New-variant, frozen-definition, class, data and CSV checks pass. The affected
  source's place_bodies rescan finds zero bodies and zero pins. Normal hooks
  perform staged admission and publication checks.

The index's other Delete_All emitters already have retail truth; no further
shortened helper source was found. The accessor's other indexed copies have
no independent retail truth, so their correctness is not inferred from this
repair. The missing post-pass at 0x00100568 remains reconstruction work; this
link-repair change does not retry it. No full census, link cycle, nightly,
boot or scheduler was run. Scratch snapshots and proof script remain under
build/vector-clip-link-20261015. Unrelated untracked work is preserved.
