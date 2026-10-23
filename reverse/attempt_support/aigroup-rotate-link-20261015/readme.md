# AIGroup rotateOffset provider repair

BFME2 base: `9e8f8e57373a09e797374ae0a4d138810d12872a`.

Move the existing 129-byte AIGroup::rotateOffset row at 0x0036CBF9 from
AIGroupRotateOffset.cpp to the existing inline emitter in AIGroupMoveFormation.cpp.
Delete the now unowned split file. Its only defined external symbol is
rotateOffset; its complete body and relocation digest (`bfe4fad11f1b`) are
identical to the home copy, which passes the retail gate at this row's extent.
The existing WB identity and pin are retained. No name, layout, extent or alias
is introduced. Both files and the RVA were claimed before editing.

## Paired measurement

Frozen index: commit `ac77c85054`, 2026-10-15 14:25 UTC, SHA256
`a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3`.
Before snapshots and after objects carry strict reusable compilation receipts.
The entire retained home and explicit AIGroupSetPositionInFormation caller
objects, including all data, directives and relocations, are byte-identical.
For each phase, refresh these objects into an independent copy of the same
index. In the after phase, link_check.forget removes the deleted provider's
facts, using the same operation as the normal index-update path. No index,
census, receipt policy or committed link status is changed.

| Unit | Local findings before | After | Legacy predicted linked bytes |
| --- | ---: | ---: | ---: |
| AIGroupRotateOffset.cpp | 1 duplicate | removed | 0 -> removed |
| AIGroupMoveFormation.cpp | 9 | 8 | 0 -> 0 |
| AIGroupSetPositionInFormation.cpp | 0 | 0 | 178 -> 178 |

The rotateOffset duplicate disappears from the home unit. Every other finding
is identical. New authored C++ bytes and local legacy linked-byte gain are
both **zero**. Strict currency is proved for the individual retained objects;
no self-strict or closed-strict placement gain is claimed.

## Acceptance

- Before strict preparation: 4/4 ledger rows across three units. After explicit
  `link_check.py --prepare-current`: 4/4 rows across two units, four compiler
  floats, no strings or named-import discrepancies.
- Retail verification also compares the rehomed row's complete bytes and
  relocations against its existing retail extent.
- EH EXACT 1; no allowances, missing objects or failures.
- Enforced data: zero findings. Converged data: eight addresses, zero second
  names or unjudged rows. Removing the split object removes no data definition.
- New COMDAT variants, class gate, declared-definition check, CSV integrity and
  whitespace checks pass. Home placement rescan finds zero bodies and pins.

`proof.json` records paired findings and strict before/after hashes. `proof.py`
runs from the repository root with ignored snapshots in
`build/aigroup-rotate-link-20261015/{0,1,2}`. Ordinary link_check without forgetting
the deleted unit retains its obsolete census duplicate; the paired preview
explicitly removes that unit and preserves all other census facts.

## Donor review and remaining blockers

Reviewed BFME1 donor repairs `de59a7e9f8`, `d003077f0b` and `66b19a8e` for
converging duplicate definitions and reusing an existing provider. Only that
ownership principle is used; no donor code, target identity or ABI is imported.

The home unit still needs Pathfinder::adjustDestination; has duplicates for
Coord3D _Construct and AIGroup::getCenter; and has five independent COMDAT
findings involving AICommandInterface and STLport. These remain separate work.
No full census, link cycle, nightly or boot runner was started.

Official BFME1 master was fetched at
`8fd286029cee70cd91c8d0c2a860ce73d9f07df2`. Clean verified checkout/gitlink remains
`a7c38d3b2597121f178ab5190b3062478823257d`. The old-input full baseline remains
unfinished (prior 2982 stale TUs, interrupted after 21 minutes with 2806 left at
`e4dfd1e4d7`, attempt record 53899). This bounded repair does not repeat the
unchanged multi-hour baseline, advance the pointer or mark freshness successful.
