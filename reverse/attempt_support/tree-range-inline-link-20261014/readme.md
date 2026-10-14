# Range-erase incidental COMDAT repair

Two `/O1` range-erase units emitted conflicting int/int iterator-copy and
`upper_bound` COMDATs although their callers already inline those vendor bodies.
Explicit TU-local `dllimport`/`forceinline` specializations retain the expressions
from `vendor/stlport/stl/_tree.h` and suppress the unused external copies.
They introduce no new retail identity, layout, pin or matched row.

| Unit | Matched rows/bytes | Legacy findings before/after | Legacy linked bytes before/after |
| --- | ---: | ---: | ---: |
| `Rva0043B35DErase.cpp` | 7 / 739 | 2 / 0 | 0 / 739 |
| `Rva0007300FErase.cpp` | 2 / 141 | 2 / 0 | 0 / 141 |

Base checkout: `e48b03777fb0477e5c06cd0ffc5804fda75dc428`. All previews use the
unchanged runner index at measurement commit `147cfae2cb`, dated
2026-10-14 07:27, SHA256
`690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a`.
The later committed `link_status.csv` was not used as an interchangeable
measurement. `comparison.json` asserts the same-index before/after findings.

`link_check.py --prepare-current` gates the two consumers, unchanged first-copy
provider `stlport_map_int_int.cpp`, and restored `Rva00500606EqualRange.cpp`:
30/30 matched rows, zero skipped string/import/float references, strict reusable
receipts. This is self-strict byte evidence; the legacy link preview establishes
880 newly linkable bytes. No closed-strict or full-link gain is claimed, and
authored C++ coverage grows by zero. The provider retains its same 19 findings;
the restored equal-range unit retains its same two findings. The combined local
link command exits 1 for these explicitly retained blockers (2/4 units clean).

The two object proofs compare strict-current before/after objects. They remove
only the 13-byte iterator-copy and 20-byte upper-bound sections, each with zero
incoming nondebug relocations. All 35 and 28 retained external COMDATs have equal
bytes, extents and relocation digests. All other nondebug sections and normalized
relocations are equal, including symbol bindings after COFF renumbering. Strong,
undefined and weak external lists are identical; no import indirection appears.
The upper-bound emitter's own outgoing relocation is removed with its section.
The explicit inline definitions have honest `present-unmatched` annotations;
they are not new address claims. The proof script uses preserved scratch objects
and receipts under `build/tree-range-link-20261014`; recorded object hashes bind
the comparisons. Reproduce by gating the base and changed source versions and
snapshotting their objects/receipts there.

Other checks: frozen-definition and class gates pass; EH verifier has zero
findings/missing objects; enforced data check has zero findings; converged data
check has zero second names or unjudged rows; new-variant check finds none;
`place_bodies.py` finds no additional bodies/pins. Ledger and whitespace checks
pass. No census, full link cycle, nightly or smoke runner was started.

The related-unit sweep found 43 indexed units touching these helpers. The other
short two-conflict unit, `Rva00500606EqualRange.cpp`, uses different compiler
settings. One careful specialization trial changed its 0x00500606 EH/frame/call
shape and failed the byte gate. The whole source attempt was restored, its two
rows reverified, a blocked verdict recorded, and its file claim released. Its
failure is in `equal-range-blocked.txt`; this compiler/EH dependency needs its own
repair. The many remaining units have independent blockers and are not credited.
Physics flight-path triage likewise retained the previously demonstrated EH
destructor blocker without repeating the failed trial; its file claim is released.

BFME 1 linking review: verified donor pointer remains
`a7c38d3b2597121f178ab5190b3062478823257d`; official master fetched to
`299467ec13d5322a9dc6b0cdc9f099fca50b3a35`. Reviewed donor repair
`de59a7e9f891b3ed2d4221d151ca881f4b75a583`, which reconciles incidental Apt
predicate COMDATs while preserving callers. Its diagnosis is applicable; its Apt
implementation and layouts are inapplicable to these trees. This repair instead
uses the established local STLport inline-only pattern, with independent BFME 2
object/byte proof. The previously cited donor `d2e21369067...` is unavailable in
this donor checkout and supplied no new evidence. Advancing the BFME 1 pointer
still requires the pending old/new comparative full verification; no pointer or
freshness-success stamp was changed during this bounded linking pass.
