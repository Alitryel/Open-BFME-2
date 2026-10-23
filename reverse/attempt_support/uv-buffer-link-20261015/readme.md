# Remove the surplus UVBuffer constructor

Base: 6340a77388ed9a99906c9d7c0bdfcd8ce5be3922. Paired local index:
19a2565407, 2026-10-15 09:33; original census 5986a99448, 04:52.
The unchanged index hash and object hashes are in object-proof.json.
Tracked link_status.csv is queue evidence from a different measurement.

MeshMatDescInstallUVArray emitted a 41-byte UVBufferClass(int,const char*)
COMDAT differing from retail's 34-byte row at 0x000D1EF8, owned by
MatInfoUVBufferO1Inlines.cpp. Keep its existing body available for inlining
with dllimport/forceinline, suppressing only the surplus external definition.
No import is emitted. The parent still constructs the buffer inline using
its existing ShareBuffer base call, vtable binding and CRC initialization.
No type, layout, flags, shared header, pin, range or ledger ownership changed.
The identity and target adaptations remain those documented by the existing
413-byte Install_UV_Array recovery; this repair imports no donor code.

Acceptance:

- Before: strict preparation of the edited unit and retail constructor owner
  passes 8/8 rows; EH 1/1 EXACT; enforced data check has zero findings.
- After: strict preparation plus ordinary byte gates pass 9/9 rows across
  those two units and MeshMatDescGetUVArrayByIndex.cpp. Two string literals
  verified, zero skipped/baselined references, zero named imports.
- Object comparison removes exactly the competing 41-byte constructor.
  All 12 retained nondebug sections, their extents, defined symbols, raw
  bytes and normalized relocations are identical, including EH and directives.
  The owner's complete object is unchanged. Objects have strict reusable
  receipts. Saved sources, receipts, objects and proof scripts remain under
  build/uv-buffer-link-20261015/.
- Same-index paired in-memory preview refreshes the same edited unit and
  owner on each side: edited unit findings 1 -> 0, LINKED 0 -> 478 existing
  nonpadding bytes. Owner findings unchanged (ShareBuffer<Vector2> destructor
  loser and three wrong-selected destructor names); LINKED stays zero.
  The sibling out-of-line constructor consumer remains clean (125 bytes),
  with identical before/after findings. Ordinary link_check agrees: two of
  three units clean, aggregate LINKED 125 -> 603; exit 1 is the owner's debt.
- EH after: 2/2 EXACT, no baseline or missing object. Frozen definitions,
  class gate, new-variant admission, CSV and whitespace checks pass.
  Enforced data checks: three sources, zero findings. Converged data check:
  eight protected addresses, zero second names/unjudged rows.
- Placement resweep: zero bodies and zero pins. No new authored bytes.

This is self-strict owned-object evidence with a paired legacy local preview.
External providers retain index currency; no closed-strict gain, new census,
full link result or executable placement is claimed. No maintainer-only
verification runner or index/status/history publication was started.

Reference review: verified clean BFME1 gitlink/checkout remains
 a7c38d3b2597121f178ab5190b3062478823257d. Reviewed linking repairs de59a7e9
(shared inline convergence), d003077f (use matched provider instead of a
competing copy), and 4966496c (suppress surplus inline emission); the
ownership/emission principle applies, their layouts do not. Official master
was fetched at 121fc40f6a502481e19d1b9fa7964248edcefd97. Its queued-download
repair is unrelated to this UV-buffer fix. Reference freshness update remains
blocked by another worker's live file claim and outstanding old/new full-gate
comparison documented in ../unicode-comparator-link-20261014/readme.md.
No success stamp or pointer update is claimed.

The same-symbol census sweep finds this as the sole losing constructor copy;
MeshMatDescGetUVArrayByIndex already declares and calls the retail provider.
Other initially ranked candidates (AIIdleStateUpdate,
AIAttackApproachTargetStateOnExit, TerrainLogicWaypointLookups,
AptMpGameSetupRefreshMapList, W3DDisplayDrawSkirmishAIStats and
HordeTransportContainDamageCallback) already link in current objects and
receive no credit here. Remaining ShareBuffer ownership/closure work is a
separate repair, not evidence against the removed surplus constructor.
