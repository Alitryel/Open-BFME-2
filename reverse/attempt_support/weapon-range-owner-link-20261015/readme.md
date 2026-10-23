# Weapon range provider reconciliation

At BFME 2 f8972ac66b871f26d85c0cb3450d257f3039f5b5, Weapon.cpp still emitted a 136-byte unrowed Zero Hour
Weapon::isSourceObjectWithGoalPositionWithinAttackRange definition. Its
COMDAT digest 222158c6d64b is proven wrong. The separately recovered
139-byte BFME 2 body at 0x002CB2D1, in WeaponRva002CB2D1Range.cpp, is the
ledger owner and has digest 4665b7de1f23. Remove the obsolete definition
and its present-unmatched marker, retaining the existing class declaration.
No provider body, header, flags, ledger row, pin, alias or baseline changes.

The existing provider preserves the target name from WorldBuilder, its
victim/position distance helpers, height-sensitive range calculation and
minimum-range access. Its const signature is carried from the ZH donor;
this repair makes no new target identity or layout claim. Both caller and
provider retain their previously verified complete bodies and relocations.

## Verification and measurement

Discovery used repair_queue.py link, link_rank.py, a current-object preview
of high-ranked unresolved blockers, and the current weapon-lock consumer's
selected-wrong diagnostic. The edited file was claimed and passed the
frozen-definition check before editing. Searching all Code sources found
only this obsolete definition, the recovered provider, WeaponSet.cpp and
WeaponSetSetWeaponLock.cpp as definitions or callers of this spelling;
all four are checked together.

The frozen index has measurement 825b86983f, 2026-10-15 12:37, based on
census 5986a99448 at 04:52. context.json records its SHA256. Fetching the
published index retained this same local index and restored 22,881 compiled
objects to the store. proof.json uses that same unchanged index for each
side and refreshes only the same four strictly prepared objects in memory.

The paired current-object baseline has seven more findings than the final
objects: Weapon.cpp loses a duplicate, COMDAT loser and selected-wrong
finding; the recovered range provider loses duplicate and selected-wrong;
the weapon-lock consumer and WeaponSet.cpp each lose selected-wrong.
None is added. The range provider and weapon-lock consumer become clean,
for a legacy prediction of 0 -> 3,479 existing nonpadding matched bytes
(707 + 2,772). Weapon.cpp and WeaponSet.cpp retain their unrelated debt,
listed completely in proof.json. The ordinary CLI reports 707 -> 3,479
because its left column is the stored census, not the current-object baseline.

- Before/after bounded link_check.py --prepare-current and separate build.sh:
  18/18 rows across four units, three float literals, no string baselines,
  skips or named imports. Each object has a strict reusable compiler receipt.
- Weapon.cpp drops precisely the obsolete 136-byte COMDAT. Of its 1,068
  retained COMDATs, 1,067 are identical. The remaining unrowed donor
  privateFireWeapon body retains the same 1,014-byte extent and every
  relocation; only its GameLogicRandomValue source-line argument changes
  from 2157 to 2129, exactly following the deletion of 28 source lines.
  The proof asserts the PUSH opcode, offset, and actual line in each source.
  It then compares every retained nondebug section, flags, raw bytes,
  definitions and symbolic relocations, allowing only that immediate.
  The three other objects and their 705 COMDATs are unchanged.
- No incoming nondebug relocation references the removed definition.
  All matched-row data-reference facts are unchanged; data_check finds zero
  findings and converged-data checks eight addresses with no second name or
  unjudged row. EH has zero applicable rows, zero missing objects/nonexact.
- Frozen definitions, class gate and new-variants admission pass. Hatch use
  decreases by one present-unmatched marker. Placement resweep finds zero
  additional bodies and pins. CSV and normal commit hooks are also required.

These are self-strict compiler witnesses and local legacy predictions.
There is zero authored C++ growth; no closed-strict closure, fresh census,
actual executable placement or runtime gain is claimed. No census/index/status
or measurement-history file was rewritten. No full link cycle, nightly,
boot or scheduler runner was invoked.

Original sources, objects and strict receipts remain under ignored
build/weapon-range-owner-link-20261015/before. Its proof.py reproduces
section comparisons, paired link findings and matched-row data facts against
the unchanged index; proof.json preserves results and input hashes.

## Donor review and remaining work

The verified BFME 1 checkout/gitlink remains
a7c38d3b2597121f178ab5190b3062478823257d. Reviewed donor repair
262d3e9507d68409d7cf86e730f4c75eefa58ccd: it removes a stale ZH definition
beside a recovered retail owner, then checks owner and consumers together.
That ownership principle applies here. No donor bytes, layouts, flags or
new identities were imported. Fresh official master was fetched at
2569a43d0087ffb2a880c099e0a944f4c2c64d93; newer donor history was reviewed.
Another worker holds file:reference/open-bfme-1 and the prior comparative
full-baseline freshness blocker remains unresolved. No reference advancement
or successful freshness stamp is claimed.

Weapon.cpp still has 60 legacy findings (27 unresolved, one other duplicate,
21 losing COMDATs and 11 selected-wrong dependencies). WeaponSet.cpp still
has 22 (seven unresolved, ten losing COMDATs and five selected-wrong).
Their broad dependency/class reconciliations are separate work. Previously
recorded setDisabledUntil and binary-patched Version trust-check blockers
were not retried. This repair closes only the supported range-owner conflict.

Model: gpt-6.1-sol.
