# Direct delete dependency repair

BFME2 source base: bb73a88a30. Four existing consumer units call the
rowed scalar and array delete providers in WWLib/mem_ops.cpp directly,
removing five invented callee names, five linker aliases and five pins.
The seven affected hatch-baseline keys only shrink, by ten counts total.
No function rows, implementation behavior, compiler flags or extents change.

Consumer evidence from native retail REL32 operands:

| Consumer | Row RVA | Size | Operand offset | Native target |
| --- | --- | --- | --- | --- |
| BfmeConv583 | 0x0073B220 | 38 | 29 | 0x0002FD60 scalar delete |
| BfmeConv730 | 0x006C0D20 | 77 | 41, 63 | 0x0002FD80 array, 0x0002FD60 scalar |
| BfmeConv1325 TWB | 0x006634E0 | 68 | 55 | 0x0002FD60 scalar delete |
| BfmeThreeHundredFiftyFive | 0x000F1CF7 | 34 | 23 | 0x0002FD60 scalar delete |

Existing provider rows are `??3@YAXPAX@Z` at 0x0002FD60 and
`??_V@YAXPAX@Z` at 0x0002FD80. This does not recover new consumer identities
or layouts; the opaque names and existing provenance remain unchanged.
MSVC 7.1 requires an explicit array-delete declaration in BfmeConv730.
The other seven mem_ops aliases and unrelated consumer dependencies remain.

Acceptance:

- Before and after bounded `link_check.py --prepare-current` verify all
  nine matched rows in the five units with current strict reusable receipts.
  The independent normal byte gate passes 9/9; no string, float or import
  references are skipped or baselined. The first compile found the missing
  array-delete declaration; the corrected source passes without byte drift.
- object-proof.json compares complete non-debug/non-directive sections,
  bytes, flags, sizes, relocations, external definitions and canonical
  undefined references. They are identical after substituting exactly the
  five aliases with their established targets. Native call operands above
  verify independently. Directives are identical except those five removals.
  The scratch proof and original source/object snapshots remain under
  build/direct-delete-link-20261014; no verifier code is changed.
- Data checking: zero findings. Enforced converged-data checking: eight
  addresses, zero second names or unjudged rows. EH: no applicable tables,
  non-exact rows or missing objects. Class and declared-definition checks
  pass, with mem_ops retaining its existing unpinned emission helper marker.
  Pin consistency passes with no baselined/new/stale conflicts; placement
  rescan finds zero bodies or pins. check_csv and diff whitespace checks pass.
- Both local link previews use the supplied index at cb660e4d97,
  2026-10-13 04:02 UTC, and refresh this cohort in memory. Its SHA256 is in
  object-proof.json. The committed status at 67e1365aa9 is discovery evidence
  only. BfmeConv583, BfmeConv730 and mem_ops link in the legacy preview;
  BfmeConv1325 and BfmeThreeHundredFiftyFive remain blocked, respectively on
  `?g_bfmeVftCTWA@@3PAPAXA` and `_bfmeVftUD`. The expected preview exit is 1
  for those unchanged blockers. Cohort legacy linked bytes: **195 -> 195**.
- Verified improvement: **five fewer aliases and five fewer pins**.
  New authored C++ bytes: zero. Current strict receipts prove byte identity,
  not self-strict or closed-strict LINK closure; no closure gain is claimed.
  No census rebuild, full link cycle, nightly or smoke runner was started;
  census/status/history are unchanged. Global hatch report still shows
  unrelated standing debt; no growth is admitted by these baseline removals.

Donor review: official BFME1 master fetched to
30c4ca7346c098cc8755f7fd685a11f2d01f67fb. Reviewed its linking repair
e0c623620c077cc216eb49c8e74c16e6349a9a7d, replacing invented free stand-ins
with direct operator delete and removing their pins. That principle is
applicable; no donor bytes, ABI, layout or addresses are imported. Target
call operands and object/provider evidence above establish this repair.
Also reviewed d003077f0b7ce97622adb7a53f1fe76653433c5c's inline buffered
stream declaration repair; it is not needed here. The clean verified
checkout/gitlink remains cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
The overdue full-byte old/new freshness comparison remains outstanding
after the earlier 5882-stale-TU/shared-compiler blocker; no pointer update
or success stamp is made.

Discovery: repair_queue.py link, link_rank.py help/top/near and alias/data
rankings, current sources and prior repair evidence. Already-repaired
concatenation blockers and still-deferred peers were not retried. All five
files and all nine retail rows were claimed before editing. This is one
compatible dependency repair; existing vtable blockers are a separate task.
