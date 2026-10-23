# MathCoord2D copy-constructor emission repair

`AreaPolygonUpdateBounds.cpp` emitted an unused 19-byte external copy of
`MathCoord2D::MathCoord2D(const MathCoord2D&)` (digest `61b49965367b`). It lost
to the first indexed copy (`3535b3a86889`) in `PathfinderSidewaysAttack.cpp`.
Marking the existing inline implementation `__declspec(dllimport)
__forceinline` removes that surplus copy and preserves the member copies in
the native bounds-refresh body. No new constructor identity, address, layout,
pin, alias or global is asserted. The source file was claimed before editing.

## Measurement and preservation

Source base: `7052c4f1cf9e2b889ac1cf684bfee3941c853daa`.
Frozen runner index: clean census `ac77c85054`, 2026-10-15 14:25 UTC;
its full SHA256 is recorded in `proof.json`. The published-index fetch kept
this same local index. Separate in-memory copies of that index are refreshed
with the two before/after objects for the paired comparison; no census,
index, link-status or history file is written.

The consumer changes from one COMDAT conflict to no findings. Legacy local
LINKED bytes change from 0 to 478 existing retail bytes. Both objects have
self-strict reusable receipts; the saved before source, object, dependencies,
command and inventory are checked against their receipts and after inputs.
No closed-strict census or executable gain is measured. Authored C++ growth
is zero, and the committed link-status ledger is unchanged.

`proof.json` records the source/object/receipt hashes, paired link/data
findings and helper selection. The whole-object comparison verifies that
exactly the unused constructor section and its external definition disappear.
All 18 retained COMDATs and every retained nondebug section preserve bytes,
extent, flags and symbolic relocations, including EH/data sections. It
normalizes local symbol numbers and labels while checking their target
sections and offsets. Directives are identical. No nondebug relocation
references the removed function or section, and no imported call is emitted.
The selected provider object, helper digest and all its findings are unchanged.

## Acceptance and sweep

- Strict preparation byte gates: 5/5 rows across the consumer and unchanged
  provider; final preparation is in `prepare-after.txt`.
- `./build.sh Code/GameEngine/Source/Common/AreaPolygonUpdateBounds.cpp`:
  1/1 matched, with string/float/import checks (`byte-after.txt`).
- Prescribed consumer `link_check.py`: exit 0, LINKS, local 0 -> 478 bytes
  (`consumer-after.txt`). The paired provider/consumer CLI exits 1 solely for
  the unchanged provider findings (`link-after.txt`).
- EH: one EXACT, no nonexact or missing objects (`eh-after.txt`).
- Enforced data check on both units: zero findings. Consumer converged-data
  check: eight addresses, zero second names and zero unjudged rows.
- Consumer class gate, declared-definition check, new-variant admission,
  ledger check and diff check pass.
- Placement resweep: zero additional bodies or pins (`placements.txt`).
  Source search finds only these two MathCoord2D class definitions; the
  selected provider is the only remaining indexed copy after this repair.

The one-off proof script and before objects/receipts remain ignored under
`build/mathcoord-copy-link-20261015/`. Reproduce by strictly preparing and
saving the two sources' objects/receipts at the source base, applying this
patch, strictly preparing again, then comparing against the same frozen index.
Do not overwrite the shared object cache with raw compiler experiments.

## Remaining blockers and donor review

The unchanged provider still has three unresolved names, five duplicates,
six COMDAT conflicts and five wrong-selected findings, listed in `proof.json`.
That provider file is owned by another worker; it was read and byte-verified
without source edits. This repair makes no claim to resolve its blockers.
No maintainer-only verification runner was started.

BFME 1 clean checkout/committed pointer reviewed:
`a7c38d3b2597121f178ab5190b3062478823257d`. Reviewed donor repair
`c1315665a1b22beb7e6d9279548fe5b1c26ed1f9`, which suppresses unused nonretail
DamageInfo constructor copies using imported force-inline definitions.
That emission mechanism is applicable and adapted locally; donor layouts,
addresses and identities are not imported. BFME 2 byte gates, symbolic
relocations and object preservation independently establish this repair.

Freshness fetch found official BFME 1 master at
`95eeb3bef370a7cd730b0ad5f228c317c8756e72`. The submodule file claim remains
held by `codex-6bc6-20261008`; its retained verified inputs are preserved.
No freshness-success stamp was written. Its owner must finish the comparative
verification and pointer update.
