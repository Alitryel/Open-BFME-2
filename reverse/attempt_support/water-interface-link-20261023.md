# Water virtual-base interface reconciliation, 2026-10-23

BFME2 input eb5738161c; published retail-truth-4 index 0393df10e2,
2026-10-23 19:47. Verified BFME1 remains 96c88c73; reviewed the existing
BFME1 linking/freshness handoffs, with no new donor source imported. The
applicable lead is the target-proven river repair documented in
astra-s1-river-vtordisp.md, already upstream.

Six water constructor/destructor units had the full seven-slot polygon
interface but named it VBase00C6EE28. That name also identifies a different
private virtual-destructor view in the planning-phase unit, producing a
competing table. Adopt the existing Rva00330C50Interface identity, as the
verified river constructor/destructor already do. Original semantic class
names remain unknown. This changes only the private interface spelling;
all seven signatures, class layouts, code, and native EH graphs stay exact.
No row, pin, alias, baseline, or new data owner is added.

Target evidence: native constructor/destructor stores identify the shared
C6EE28 interface, and Rva00330C50Ctor.cpp establishes its seven signatures.
The complete native table has seven __purecall entries (see
00778b4d-polygon-cleanup-20261019/identity-audit.md). The prior tiny-fold
admission/data-ownership limitation is not resolved by this repair; no
closed-strict or self-strict closure gain is claimed.

Paired current-object legacy link_check results, before -> after:

| Unit | Before | After |
|---|---:|---:|
| Rva0030902ECtor.cpp | 0 | 453 |
| Rva0030CAA9OwnerCtor.cpp | 0 | 409 |
| Rva0030902EDtor.cpp | 0 | 308 |
| Rva0030CAA9OwnerDtor.cpp | 0 | 194 |
| Rva0053805DBaseCtor.cpp | 0 | 149 |
| Rva0053805DBaseDtor.cpp | 0 | 179 |
| Total | 0 | 1692 |

The census already credited the last two units with 328 B, so its frozen
comparison is 328 -> 1692 (+1364 B), while the measured current pre-edit
improvement is +1692 B. Do not count either as newly authored C++ coverage.
The three related river/wave parser units already preview clean (2400 B)
and were not changed. Rva002E4049Dtor.cpp also already links (181 B);
no cleanup-only edit is claimed as a repair.

Acceptance: normal scoped byte gate 60/60, data row 1/1, literals and
imports pass; strict reusable receipt preparation passes all six sources;
new-variant check, frozen-definition check, check_csv and diff check pass.
No census, link cycle, nightly, boot runner or verifier edit was performed.
Scratch paired previews and acceptance output are build/link-seat-water-*.

Post-commit shadow identity diagnostic: allowed_symbols scans the stale literal
object-symbol=$L1420 on Unwind@00b79dae and reports a divergent call at
0x002E3E51. Exact parent EH mapping instead binds $L1419 to 0x00779DAE
and $L1420 to 0x00779DB9. The normal byte gate follows that verified mapping;
the shadow identity scanner currently reads ledger_object_symbol directly.
This is a label-renumbering scanner limitation, not evidence of a changed
cleanup call. Preserve this diagnostic for a separate verifier repair with
a regression test; no tool or baseline was modified.
