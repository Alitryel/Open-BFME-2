# Thing position matrix setter link repair

Publication reconciliation: upstream commit `11559f8d90` landed the equivalent
`m_transform[1].W = pos->y` repair concurrently. Rebased onto that commit and
kept its source implementation. This commit retains an independent
verification of the equivalent `[1][3]` spelling and final checks of the
upstream spelling; it claims no additional source change or additive link gain.

Base checkout: `6dfde03620a9ad7d1c2ff0c1002404a53c974c83`.
Runner index: `147cfae2cb`, 2026-10-14 07:27, SHA256
`690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a`.
The committed status queue at `67e1365aa9` is discovery evidence only.
No census, status, history, baseline or data-back artifact changed.

Claimed the ThingSetPosition.cpp file before editing. Its sole remaining
finding is the surplus Set_Y_Translation COMDAT, digest `13b6d4eed837`,
classified wrong against the first provider Thing.obj, digest `cd81b093086e`,
classified retail. The previous matrix-copy repair left this finding open.

The existing matrix header defines the setter as `Row[1][3] = y` and the
public accessor as `return Row[i]`. Spell that assignment through the public
accessor at the one call site. This removes the wrong setter without changing
the header, class layout, provider or calling convention. The accessor copy
emitted instead is the complete, relocation-free 12-byte retail body at
0x0007DE8E, identical to all 21 indexed copies (digest `6484505ef93b`).
No pin, alias, global or new identity was introduced.

The full existing Thing::setPosition row remains byte-exact at
0x0030AA80..0x0030AB9D, extent 285. Its existing target identity and donor
layout qualifications remain unchanged. This repair makes no new layout claim.

The upstream-final logs reverify the retained `.W` spelling after the rebase.

## Acceptance

- Before and final after `link_check.py --prepare-current` pass the sole
  matched row with strict reusable receipts. Final saved objects independently
  hash to the object identities recorded in their receipts. The normal
  `./build.sh` gate passes 1/1, with zero skipped or baselined references.
- Object comparison removes only the wrong setter and adds only the exact
  retail accessor. All nine retained COMDATs preserve whole bytes, extents,
  relocation facts and digests. Undefined externals and weak bindings are
  unchanged. Both existing first providers are untouched.
- Same-index ordinary legacy preview changes from one COMDAT finding to clean:
  0/1 to 1/1 units, LINKED 0 to 284 existing authored bytes. The preview's byte
  accounting differs from the ledger's 285-byte full row extent. The only
  affected current consumer is ThingSetPosition.cpp; the same-cause index scan
  finds no other unit with this setter finding.
- New-variant admission, class, declared-definition, shadow data, converged
  data, EH, CSV and whitespace checks pass. Converged data has zero second names
  and zero unjudged rows across eight addresses. No EH rows apply.
- Placement resweep reports zero bodies and zero pins.

An intermediate cache object failed the converged checker because its full
hash differed from its recorded receipt. Preserved it locally, removed only
this unit's object and sidecar, and regenerated through prepare-current and
the ordinary byte gate. Final receipt/hash and converged checks pass. No
checker was weakened or bypassed.

This proves self-strict object currency and a legacy local preview improvement
with zero new authored C++ bytes. Closed-strict dependency closure, actual
link.exe placement and fresh census gains remain unmeasured. No maintainer-only
verification runner was started. Logs and the object comparison accompany this
record; source/object backups and the proof script remain under
build/thing-y-link-20261014/.

## Donor review and remaining prerequisites

Reviewed BFME 1 repair `de59a7e9f891b3ed2d4221d151ca881f4b75a583`:
it reconciles surplus inlined predicates while preserving callers. That
principle applies, but its Apt classes and layouts do not; no donor code or
layout was imported here. The setter/accessor semantics come from the already
used matrix header, while retail bytes independently verify both emitted
target bodies.

The clean verified BFME 1 pointer remains
`23b143233b5a8664a3bdf8572df6d905c310a5a1`. Official master was fetched to
`a7c38d3b2597121f178ab5190b3062478823257d`. Its previously recorded freshness
blocker is unchanged: thousands of stale TUs need a full old-input baseline
before controlled comparative verification. Kept verified inputs, did not
write a success stamp, and did not repeat that unchanged blocked work.
