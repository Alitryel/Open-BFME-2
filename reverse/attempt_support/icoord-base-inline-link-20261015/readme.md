# Coordinate-view inline link repair

Two consumers of `ICoord2DBase.h` emitted an unused five-byte external
`asBase(ICoord2D&)` COMDAT (`341dc3ec187f`), differing from the selected eight-byte
copy (`93e56a5b52f2`). A TU-local `dllimport` / `__forceinline` declaration before
the shared header preserves its inline implementation while suppressing the
unreferenced external copies. The shared header and providers are unchanged.
No native address or new identity is asserted for this helper.

## Measurement

- Source base: `bf74c4dd5aa5977e1ab450c9a03a3c5a2c76f0a4`.
- Published index: clean measurement `ac77c85054`, 2026-10-15 14:25;
  SHA256 `a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3`.
- Both phases use copies of that same frozen index, refreshed with the four
  strictly current objects listed in `proof.json`.
- Clean consumers: 0/2 before, 2/2 after. Legacy local linked bytes: 0 -> 654
  (77 in `Rva00366AE3Add.cpp`, 577 across four `HordeMeleeAmoeba.cpp` rows).
- Authored C++ byte gain: zero. No closed-strict census or executable gain was
  measured; the global link-status ledger is unchanged.

`proof.json` records object/source/receipt hashes, before/after findings,
provider selection, and data findings. The object comparison normalizes COFF
symbol indices and local labels, compares every nondebug section byte, flag and
relocation, compares external/weak bindings and directives, and checks that no
nondebug relocation refers to the removed helper or its section. Only the two
unused five-byte sections and their definitions disappear. All nine retained
consumer COMDATs are identical. Both provider objects and their findings are
identical between phases; the selected helper copy stays unchanged.

Before objects and the one-off comparison script remain in the ignored
`build/icoord-base-link-20261015/` directory. For reproduction, compile the source
base and this repair under identical inputs, save each phase's strict-current
objects/receipts, and refresh separate copies of the named index with all four
objects before comparing `link_check.check_object` results. Do not overwrite
the shared object cache with raw compiler experiments.

## Acceptance

- `./build.sh` on both consumers: 5/5 rows pass (`byte-after.txt`).
- `link_check.py --prepare-current` on both consumers and both providers:
  16/16 gates in each phase, strict reusable receipts (`prepare-*.txt`).
- `link_check.py` on the two consumers: exit 0, 2/2 clean, local LINKED 0 -> 654.
  The four-unit check in `link-after.txt` exits 1 solely for unchanged provider
  findings listed below.
- `eh_verify.py` on all four: one EXACT, zero nonexact or missing
  (`eh-after.json`). `data_check.py --enforce` on all four: no findings.
- `data_check.py --converged` on both consumers: eight converged addresses,
  zero second names, zero unjudged. `link_check.py --new-variants`,
  `class_gate.py`, `find_declared_unmatched.py`, `check_csv.py` and
  `git diff --check` pass.
- `place_bodies.py` on both consumers: no additional bodies or pins
  (`placements.txt`). Header-user sweep (`sweep.json`): four strict-current
  units, two missing/stale units skipped. The only remaining current helper
  emitters are the two unchanged eight-byte provider twins. No indexed losing
  copy remains.

## Remaining blockers and donor review

`PathfinderPosGoalManager.cpp` still has two duplicate definitions and three
`LandLocalPoint` set/sub COMDAT conflicts. `PathfinderSameCellRva002EE49B.cpp`
still selects a nonretail `Rva002E7875WorldToCell` provider. These findings are
unchanged, not repaired or credited here. Broader link cycles were not run.

BFME 1 checkout/committed pointer reviewed:
`a7c38d3b2597121f178ab5190b3062478823257d`.
Donor `de59a7e9` demonstrates inline predicate reconciliation; donor
`c1315665a1b22beb7e6d9279548fe5b1c26ed1f9` suppresses an unused nonretail
constructor using the imported-forceinline mechanism. The latter mechanism is
applicable here and was adapted locally. Neither donor layout nor helper
identity is imported as target evidence; the target object comparisons and
retail byte gates establish this repair's preservation claims.

Freshness fetch found upstream BFME 1 at
`95eeb3bef370a7cd730b0ad5f228c317c8756e72`. Its submodule file claim is held by
`codex-6bc6-20261008`; the checkout/pointer is preserved, with no freshness
success stamp written. The owning seat must complete the verified update.
