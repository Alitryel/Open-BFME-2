# HordeContain Coord3D::scale link repair

At BFME 2 base `8ef9c81eef23a21c9df79975987356f22416cf89`, opt
`HordeContainIface11CSlots.cpp` into the existing
`BFME_COORD3D_INLINE_SCALE_LINK` switch around its canonical companion header.
This preserves the inline multiplies and suppresses an unused, nonretail
out-of-line `?scale@Coord3D@@QAEXM@Z` COMDAT. No header, flags, provider, ledger,
layout, identity, pin or baseline changes are needed.

The consumer's removed 49-byte body has census digest `89f10a4f4b61`.
`Code/Libraries/Source/WWVegas/WWMath/region.cpp` still supplies the retail
49-byte body at RVA `0x000036D1`, digest `9707cccd2882`. Existing target rows and
the canonical header establish the relationship; this change introduces no
new donor identity or layout claim.

## Paired evidence

The frozen census is from `ac77c85054`, dated 2026-10-15 14:25 UTC, SHA256
`a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3`.
`proof.py` compares strict-current before/after objects against that same index
and unchanged current retail provider. The snapshots and context are under
ignored `build/horde-scale-link-20261015/`; `proof.json` records their hashes.

- Consumer findings: **43 -> 42**, exactly the wrong scale COMDAT removed.
  No new findings; all 633 retained COMDATs retain bytes, extent and relocations.
- Every retained nondebug section, relocation, linker directive and strong,
  undefined or weak binding is unchanged after normalization of COFF indexes.
  No nondebug relocation referenced the removed helper.
- The provider remains clean. Local legacy linked bytes remain **1,287 ->
  1,287**, entirely in the provider. Consumer linked bytes remain zero.
- No self-strict placement gain, closed-strict gain or authored C++ byte gain
  is claimed. This is a verified reduction in one link blocker.

## Acceptance checks

Commands below use the consumer and `region.cpp` together unless noted.

- `link_check.py --prepare-current`: before and after pass **190/190** byte
  checks, 12 string literals plus 2 empty-string references, 36 float literals;
  strict reusable receipts. Index/status remain unchanged.
- `link_check.py`: before/after previews retain exit 1 for remaining blockers;
  paired evidence proves only the scale finding disappears. The remaining 42
  comprise 10 unresolved, 1 duplicate, 24 COMDAT and 7 selected-provider findings.
- `eh_verify.py`: **11 EXACT**, no nonexact, baselined or missing handlers.
- `data_check.py --converged`: 8 protected addresses, no second names or
  unjudged rows.
- Diagnostic `data_check.py --enforce` refuses two existing wrong-name findings:
  `?$S1@?L@??rva00469967@HordeContain@@UAEXXZ@4IA` at `0x00A03674` and
  `?$S2@?BG@??rva004708BC@HordeContain@@UAEPAVObject@@PBVMatrix3D@@@Z@4IA`
  at `0x00A03684`. The paired object replay in `proof.py` proves both are
  identical before/after. The ordinary data gate remains in upstream shadow
  mode; no baseline was changed.
- Consumer `find_declared_unmatched.py --fail`, `class_gate.py` and
  `link_check.py --new-variants` pass. `place_bodies.py` finds no extra bodies
  or pins.

No census, full link cycle, nightly or boot runner was invoked. Captured command
logs accompany this record. The normal commit/push hooks also apply.

## Donor review and remaining work

Reviewed BFME 1 suppression repairs
`c1315665a1b22beb7e6d9279548fe5b1c26ed1f9` and
`66b19a8e95a4add525ef808fcea088e306798e2b`: their suppression technique is
applicable through BFME 2's already verified companion switch, introduced in
`23b475dc3c`. This session does not import donor code.

The frozen index's same-digest emitter cohort was checked against current
receipts. AIStates and AISpecialPowerPickers are already repaired; HordeContain
is the remaining emitter using this canonical companion. Bezier uses the BFME
1 coord header; DeliverPayload, Railroad, Dozer and Physics use different header
contexts; Spectre and Laser lack comparable strict receipts. Harvest remains
deferred on its previously recorded scalar-codegen difference. Further repairs
need independent evidence rather than another identical opt-in.

The overdue BFME 1 refresh belongs to another live file claimant. The clean
verified pointer stays `a7c38d3b2597121f178ab5190b3062478823257d`; fetching
official master found `f20d35ff4`. No pointer or successful-freshness stamp was
changed. Broader linking gains require the remaining HordeContain providers and
COMDAT repairs and an authorized measurement.
