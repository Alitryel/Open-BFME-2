# AptPalantir tree comparison link repair

Base: `c52874be8866bb3cc6923cd4cb5ca8631f328ea0`.
The constructor unit emitted an unused external STLport tree-base inequality
with a different body from the selected library copy. Use the existing
TU-local typed node comparison pattern. No game body, header, layout, ABI,
compiler flags, pin, data binding or function ledger row changes.

## Controlled evidence

The frozen runner index is `19a2565407` (2026-10-15 09:33), from census
`5986a99448` (04:52); its SHA-256 is in context.json. The committed status
queue measures `28269d8e8d` (09:31). No per-row data-back ranking is used.
Fetching the published index retained this newer local index and supplied
published objects. Neither index nor status was rewritten.

Original and changed objects both pass strict reusable receipt preparation.
link-proof.json refreshes only the owned consumer in independent copies of
the same index: **6 -> 5 findings**, removing exactly the comparison COMDAT
conflict. Every remaining finding is identical. Legacy local LINKED stays
**0 -> 0**, affecting 3,896 existing unique nonpadding authored bytes.
Authored coverage grows by zero. No self-strict placement, closed-strict
gain, full link cycle or new census is claimed.

object-proof.json proves all **135 retained COMDATs** have identical bytes,
extents and relocation digests. The only nondebug section change replaces
an unreferenced 18-byte external comparison with an unreferenced 12-byte
static typed comparison. Other normalized sections, relocations, bindings
and directives are identical. Local labels and .sxdata indices are compared
by their actual destinations. Provider objects are unchanged.

## Acceptance and remaining blockers

- Before/after `link_check.py --prepare-current`: **73/73** exact.
- `./build.sh`: **73/73**, 28 strings and all float/import checks pass.
- `eh_verify.py`: **3/3 EXACT**, no baseline or missing-object exceptions.
- Ordinary local `link_check.py`: expected exit 1, five remaining findings.
- `link_check.py --new-variants`, `class_gate.py`,
  `find_declared_unmatched.py`, `data_check.py --enforce` and
  `data_check.py --converged`: pass. Paired data facts/findings identical.
- `place_bodies.py`: zero bodies/pins; `check_csv.py` and diff check pass.

Identity shadow findings change **1 -> 2**. The existing MakeBinding
divergent definition remains. The additional diagnostic reads the literal
ledger label `$L7591` as if it still named the ctor funclet at `0x777776`.
The changed object uses that label for the dtor funclet at `0x7776E5`;
the byte gate explicitly reports this renumbering and verifies it through
the exact parent EH graph. The raw diagnostic is preserved in
identity-proof.json, rather than credited as fixed or suppressed. The
complete normalized object comparison independently shows no binding change.
No verifier code or baseline is edited.

Four duplicate definitions (AptPalantir constructor/destructor/init and
RadarWindowOverrideSource reset) and the selected Rva005248D0 constructor
still prevent this unit linking. Broader placement verification remains
outside this seat's authorization.

## Donor review and handoff

Reuse the dedicated donor review in tree-consumer-cohort-link-20261015 and
persistent-tree-link-20261015: BFME1 repair `de59a7e9f891b3ed2d4221d151ca881f4b75a583`
supports consistent incidental helper ownership; BFME2's typed iterator
implementation and direct object evidence support this change. Also reviewed
new donor repair `c1315665a1b22beb7e6d9279548fe5b1c26ed1f9`: its DamageInfo
constructor suppression is a separate dependency and is not imported here.

The clean donor checkout remains at verified pointer
`a7c38d3b2597121f178ab5190b3062478823257d`. Official master was fetched;
context.json records the observed revision. The reference scope remains
foreign claimed, and the previous stale/missing-input full-verification
blocker is unresolved. No pointer update or freshness-success stamp.

Proof scripts run from the repository root. Original objects and source
backup remain in `build/palantir-tree-link-20261015`; binaries are not committed.
