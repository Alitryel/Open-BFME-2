# Living World tooltip link repair

The tooltip unit's `/Oy-` setting emitted 21-byte, framed copies of
`UnicodeString`'s copy constructor and string append operator. Both lost to
the existing 18-byte retail wrappers. `/Oy` emits those retail wrappers and
preserves every tooltip body, but the unrelated 55-byte eligibility predicate
requires `/Oy-`.

Move that predicate, its existing structural view, and its two genuine STLport
search folds unchanged into `LivingWorldScenarioOwnershipSet.cpp`, beside its
retail building-spawn caller. That existing unit already requires `/Oy-`.
Keep the same static STLport library setting with the moved include. No new
unit, private class instance, ABI, pin, shared header, or escape hatch is added.
The original predicate name and four-byte key type remain uncertain; this
change adds no identity or layout claim.

## Paired evidence

Source base: `eef7933b0553bf30423b096d4b2bcdb64540dad8`.
The fetched local index identifies commit `825b86983f`, 2026-10-15 12:37;
its underlying census identifies `5986a99448`, 2026-10-15 04:52. Index SHA256:
`672f6ffe10798a1e82a1516e32c7d579bd787503faae7ee6beabb6e4cca2b93c`.
The committed status file's older measurement is used only for discovery.

`proof.py` refreshes the same index in memory with saved before objects or
the two current strict-receipt objects. It does not write an index or census.

| Existing unit | Before legacy preview | After legacy preview |
| --- | --- | --- |
| BuildingTemplateCommandPointBonus | 2 losing string wrappers; 0 LINKED bytes | clean; 356 LINKED bytes |
| ScenarioOwnershipSet | clean; 390 LINKED bytes | clean; 575 LINKED bytes |

Clean units: 1/2 -> 2/2. Local LINKED row bytes: 390 -> 931 (+541).
These are the checker's per-unit row-byte counts, including existing folded
search rows, not newly recovered unique bytes. Authored C++ coverage grows by
zero. No closed-strict, full-link, or published census gain is claimed.

The object proof asserts that all 18 retained COMDAT bodies, extents and
relocation targets are identical, including all three moved bodies. Across the
two objects, every other nondebug section and normalized relocation referent
is unchanged. Only the two string wrappers change from 21 to 18 bytes and
become retail copies. External definitions are unchanged; the caller no longer
needs an undefined `Check` because it now contains its unchanged definition.
The tooltip's alias and default-library requirements are unchanged; the moved
STLport include repeats existing cohort library requirements. No new library
or alternate name is introduced.

`object-proof.json` contains complete findings, body details and object/source
hashes. The repeatable proof uses scratch snapshots in
`build/lw-unicode-link-20261015/`; it refuses a different index or stale current
objects. Those scratch objects are not committed.

## Acceptance

- Original strict-current gates: tooltip 8/8 and OwnershipSet 3/3.
- Final `link_check.py --prepare-current` on both units: 11/11 exact bytes and
  relocations, 2 literals verified, no skipped or baselined references.
- `link_check.py` on both current units: 2/2 clean, 390 -> 931 LINKED bytes.
- `eh_verify.py`: 3/3 EXACT, no baseline or missing objects.
- `data_check.py --enforce`: zero findings; `--converged`: eight addresses,
  zero second names or unjudged rows.
- Class, frozen-source, CSV and staged-peer new-variant checks pass.
- `place_bodies.py` on both units: zero additional bodies or pins.

Normal commit and push hooks remain enabled. Maintainer-only verification
runners were not started; broader closure remains outstanding.

## Reference review and handoff

The BFME 1 checkout and committed pointer remain
`a7c38d3b2597121f178ab5190b3062478823257d`. Official master was fetched at
`2569a43d0087ffb2a880c099e0a944f4c2c64d93`. The required full freshness update
is blocked by another worker's live `file:reference/open-bfme-1` claim
(`codex-6bc6-20261008`); no pointer or success stamp was changed.
Donor repair commits `53d32d6b4b377317a3397971629ca3ad20b870e9` and
`66b19a8e95a4add525ef808fcea088e306798e2b` were reviewed for the canonical
wrapper/code-emission approach. No donor code, layout or address is imported;
the accepted change follows the target's existing string rows and byte gates.

Separate failed probes were restored and recorded in `re_attempts.log`:
ScopedCriticalSection cleanup suppression introduces an unresolved EH import;
the Vector3 filler needs an evidence-backed resize ABI/type reconciliation;
WeaponTemplateTargetPositions' random upper bound `0xBC614E` is a recorded
false-positive address finding. Their claims were released. The repeatedly
blocked string-record drawing cleanup was inspected without retrying it.
