# GameClient snapshot drawable getter emission repair

GameClientXfer.cpp emitted an unreferenced seven-byte const
Drawable::getObject COMDAT with a different body from the five other copies
in the runner index. Mark its existing inline definition imported forceinline,
following BFME1 repair 66b19a8e95a4add525ef808fcea088e306798e2b. The matched
snapshot caller retains its established field access; the external helper
copy disappears. No import reference, class layout, function identity, ABI,
compiler flags, pin, header, global or ledger row changes.

The target evidence remains the original 0x0023B509..0x0023BC17 snapshot body
(1806 bytes, RET4), its existing recovery notes and ledger provenance. The
donor supplies only an emission technique, not target identities or layouts.
The indexed peer inventory identifies this as the sole alternative digest in
the six-copy const getter family. The five peer objects are unavailable in
this checkout; their unchanged index entries are legacy evidence, not current
provider verification. No peer source was modified or claimed as verified.

## Paired result

Target base: d3dd12b6c00c16bdd57f0873201556524a0c7a96.
Runner index: a2839ea429, 2026-10-15 13:35; origin census
5986a99448, 2026-10-15 04:52. context.json records its SHA256.
The committed link-status queue is a separate older measurement used only for
selection. Neither status nor census/index/history was changed.

Strict bounded preparation passes before and after. proof.py refreshes the
saved original and repaired object independently into copies of the same
unchanged index. Local legacy findings fall 10 -> 9, precisely removing the
getter conflict. Every other finding is identical. All 72 retained COMDATs
keep their bytes and relocation digests; normalized nondebug sections,
external bindings, data references and directives remain identical. No retained
nondebug relocation targets the removed getter, and no new import or COMDAT
variant appears. object-proof.json includes both complete findings and hashes.
Original source/object/dependency receipt snapshots remain under
build/client-object-getter-link-20261015/before for reproduction.

This verifies one strict-current consumer and one fewer legacy local conflict.
Authored C++ growth and predicted LINKED gain are both zero. The unit still
has independent blockers, so no self-strict placement, closed-strict gain,
census gain or full executable link is claimed.

## Acceptance and remaining work

- Strict preparation before/after and independent ./build.sh: 1/1 row exact,
  two literal references verified, no baselined or skipped references/imports.
- EH: 1/1 EXACT before and after, no missing or baselined rows.
- Paired data facts identical; data enforce reports zero findings. Converged
  admission checks eight addresses, zero second names or unjudged rows.
- Frozen-definition, class, CSV, whitespace and new-variant checks pass.
- place_bodies.py resweep: zero bodies, zero pins.
- Ordinary local link_check exits 1 for the nine remaining findings, as
  expected: duplicate snapshot/audio-setter definitions; max and record
  construct/overflow COMDATs; selected snapshot, xferNoName and record helpers.
  See link-after.txt. These require separate ownership/provider repairs.

BFME1 verified checkout/gitlink stays a7c38d3b2597121f178ab5190b3062478823257d.
Official master fetch reports 776c8123 at this pass. The reference update is
held by another seat's live file claim, so no moved inputs were substituted,
no comparative full-gate retry was started and no freshness-success stamp
was written. The existing donor review of 66b19a8e was reused and its commit
was inspected directly. Full link cycles, census rebuilding, nightlies and
boot operations were not run.
