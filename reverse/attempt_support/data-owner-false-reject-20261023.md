# Data-owner false reject (s6, 2026-10-23)

BFME 2 input: `7aae99cc67`; recorded case: `0x00017A40`, 85 bytes,
`reverse/attempt_support/link-seat-20261022/static-string-owner.patch`.
No game source, ownership row, baseline, or whitelist changes accompany this
verifier repair.

The committed heuristic `data_ledger.csv` chooses unowned `StaticEmpty`
aliases at RVAs `0x009DEEFC`, `0x009DEF08`, and `0x009DEF38`.
`data_rows.csv` already records the corresponding `g_Va` names as four-byte
owners in `Rva007AB8D0StringInits.cpp`. Feeding these actual ownership facts
(name, RVA, owning source, definition) to `data_check.findings` with the old
loaded index reports all three owners as `wrong-name`. This reproduces the
checker disagreement without relying on absent compiled objects. The original
handoff separately records the consumer's eight exact byte rows.

The repaired index loader and generator reconcile with the explicit ownership
ledger after its integrity check. The three reproduced findings disappear.
Aliases remain wrong names, another TU defining an owner remains a duplicate,
and ambiguous/unmatched ownership raises an error. Extents come from the
ownership ledger, not inferred distance to the next address. This does not
claim that the four-byte owner rows describe complete string objects.

Six regression tests initially failed (five assertions and a missing entry);
all pass after the repair. The combined data-sweep, exploit, converged-address,
and data-row suites passed 124 tests with one skip. The converged-address check
is unchanged, and the reconciled index conflicts with none of its names.
A full comparison found 227 heuristic-name disagreements resolved in favor of
existing explicit owners; this is not an address-specific exception.

The consumer repair had already landed separately in `f8005d0241`; no replay
is needed. Focused `./build.sh` now verifies all ten current rows of
`stlport_narrow_string_range_ctors.cpp`. The exploit-suite skip is its empty
optional audit-fixture parameter set; all 21 actual exploit tests pass.

Model: gpt-6-astra; seat: s6.
