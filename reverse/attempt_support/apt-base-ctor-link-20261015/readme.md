# Apt registry constructor emission repair, 2026-10-15

## Result and scope

`OpaqueScalarDeletingDtorsB11.cpp` and `OpaqueScalarDeletingDtorsB12.cpp`
previously emitted 9-byte implicit `Rva005248D0` constructors from destructor-only
private views. Both copies are proven wrong by the ledger-owned 106-byte
constructor at RVA `0x002D2C34`, in `Rva005248D0Ctor.cpp`.
Declare that constructor in both views. The vtable-emitting helper constructors
now reference the existing provider. B11 also declares `GameWindow()` as B12
already does, using `GameWindow_DefaultConstructor.cpp` at RVA `0x003145F0`.
This prevents an incomplete GameWindow vtable from being emitted when the
registry-construction call acquires exception cleanup.

The matched destructors, adjusting thunks and funclets retain their full retail
bytes. No layouts, flags, ledger rows, symbol pins or shared headers changed.
There are **two fewer wrong constructor copies and two fewer local COMDAT
loser findings**, with no added local findings. Authored bytes and newly
link-clean bytes both grow by zero. This is a dependency repair, not a new
function recovery or a closed-strict gain.

## Evidence and measurement

Work started at BFME 2 `2f90b52cc0`. Both source files were claimed before editing.
`object-proof.json` records strict receipt/current-object hashes, the two removed
bodies and their relocations, and paired before/after local link findings.
The same frozen index was used for both sides:

- index commit `19a2565407`, date `2026-10-15 09:33`;
- underlying census commit `5986a99448`, date `2026-10-15 04:52`;
- the exact index SHA-256 is included in the proof.

The two unchanged constructor providers were refreshed in memory on both sides.
Both repaired sources lose exactly the constructor's `retail/wrong` COMDAT
finding; their unresolved, duplicate, address and wrong-selected findings remain
identical. The providers' findings are identical too. No census, index, status
ledger or measurement artifact was rewritten.

Self-strict: all four involved objects have strict reusable current receipts;
55/55 rows in the two edited units byte-match. Both unchanged constructor
providers also pass the normal byte gate (one row each). This supports the local
object and emission claims. The paired link preview uses legacy census closure;
other providers are not collectively proven current, so no closed-strict gain
is claimed. A full link cycle was not run (maintainer-only).

## Acceptance checks

- `python3 tools/check_csv.py`: pass.
- `python3 tools/link_check.py --prepare-current` on both edited sources and
  the two providers: normal byte gate passes, strict receipts current.
- `python3 tools/eh_verify.py` on B11/B12: EXACT 4/4, zero baseline entries.
- `python3 tools/data_check.py` on B11/B12: zero findings.
- `python3 tools/data_check.py --converged` on B11/B12: eight addresses,
  zero second names or unjudged rows.
- `python3 tools/find_declared_unmatched.py` on B11/B12: pass.
- `python3 tools/class_gate.py` on B11/B12: pass.
- `python3 tools/link_check.py --new-variants` on B11/B12: pass.
- `python3 tools/link_check.py` on all four: GameWindow provider remains clean
  at 155 non-padding bytes; the other three retain existing blockers (exit 1).
- Paired proof asserts removal of both wrong copies and both local loser
  findings, no new findings, and unchanged provider results.

## Donor review and remaining blockers

Reviewed BFME 1 verified pointer `a7c38d3b2597121f178ab5190b3062478823257d`
and donor repair `d3f9000fe08615a100e844adfff57fa4a39cd615` (TileData implicit
constructor suppression). The declaration-only technique applies; no donor
layout or body was imported. BFME 2's existing registry and GameWindow providers
establish the actual target identities and byte gates establish their bodies.
The destructor-only view sizes are preserved, not inferred from the donor.
The earlier BFME 2 registry repair is recorded in
`../apt-registry-link-20261014/readme.md`.

The remaining wrong registry constructor copies belong to
`AptRowListCallbacks.cpp` and `AptPalantirUpdate.cpp`. The former's prior attempt
was blocked by a separate 528-byte nonretail `Rva005105D7` constructor emission;
it was not retried here. These copies keep wrong-selected findings alive in
B11/B12 and a duplicate/wrong-selected finding in the full constructor provider.
B11 also retains seven unresolved methods and one unrelated vtable loser;
B12 retains three unresolved destructors and one unrelated vtable loser, all
listed exactly in the proof.

The FP guard constructor repair was already claimed by another worker and was
not edited. BFME 1 upstream was fetched as `c02ec78ac`; freshness migration is
held by another worker's `file:reference/open-bfme-1` claim. The verified gitlink
and stale check timestamp were preserved; no update was marked successful.
