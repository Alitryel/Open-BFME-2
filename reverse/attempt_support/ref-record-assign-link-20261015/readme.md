# Sort-record assignment ownership repair

Source base: 876974c82a. Actual local index: 19a2565407, 2026-10-15 09:33;
original census: 5986a99448, 2026-10-15 04:52. object-proof.json records the
unchanged index hash and both saved/current object hashes. The committed
link_status.csv is discovery evidence, not this local measurement artifact.
No census/index/status/history, pin, shared header, flags or baseline changed.

Rva004F6352Assign.cpp strongly defined the 35-byte assignment at 0x004F6352,
while stlport_rva004f6352_sort_entry.cpp already emitted its exact inline copy.
Both units failed the duplicate-symbol check. Move the existing row to that
inline owner through add_match --replace-existing and remove only the strong
body. Keep the 32-byte copy constructor and the assignment declaration in the
original unit. The sort needs its body visible so cl preserves register usage
across assignments in the insertion helpers.

Target evidence remains the complete 0x004F6352..0x004F6375 body, stride 12
in callers 0x004F6C32/0x004F6876, the first two word copies and +8 owned
TreeHintRef assignment through the matched 0x002174A4 provider. The address-
derived record name is unchanged; no semantic identity or complete class
layout is claimed. No donor body is imported.

Acceptance:

- Strict bounded preparation before and after: 9/9 rows exact in the two
  explicitly claimed units with reusable dependency receipts. add_match
  independently verifies the destination's eight rows. Zero strings/imports
  need exceptions or baselines.
- Object proof: the sort's complete nondebug section multiset is unchanged,
  including bytes, extents, bindings, directives and normalized relocations.
  The original object loses exactly one 35-byte assignment section and adds
  nothing. All retained nondebug sections match. Proof assertions run from
  build/ref-record-assign-link-20261015/proof.py against saved before objects.
- Paired same-index local preview refreshes the same two saved before objects
  and two strict-current after objects in memory. Both duplicates disappear,
  with no other findings before or after. Cohort 0/2 -> 2/2 clean; existing
  linked nonpadding retail bytes 0 -> 539 (32 constructor + 507 sort unit).
  Standalone link_check agrees. Compiler currency is self-strict for the
  explicit cohort; external providers retain legacy index currency. No
  closed-strict, actual executable placement or new census gain is claimed.
- EH: 2/2 EXACT, no missing objects or baseline entries. Frozen definitions,
  class gate, new COMDAT variants, converged data (eight addresses, no second
  names), enforced data, CSV and whitespace checks pass. Placement resweep
  finds zero bodies/pins. Authored/matched C++ byte growth is zero.

Reference linking review: verified clean BFME 1 gitlink/checkout
 a7c38d3b2597121f178ab5190b3062478823257d. Reviewed de59a7e9 (shared COMDAT
 reconciliation) and 4966496c (surplus inline emission); their ownership
 principle applies, while Apt layouts and target-specific expressions are
 inapplicable here. Official master fetched to 1c4d808dd6a0f2bd514f607f40e9e422db3ab91b.
 The reference pointer update remains held by another worker's live file
 claim and the outstanding old/new full-gate comparison documented in
 ../unicode-comparator-link-20261014/readme.md. Verified inputs are retained;
 no freshness-success stamp or gitlink update is claimed.

The independent getConstSlot duplicate trial was restored and logged as
blocked: inline/noinline secondary copies lose register-preservation analysis
and fail three of 37 callers. See ../gameinfo-slot-link-blocked-20261015/.
All its source edits were reverted and all 37 rows reverified; claims released.
Several older ranked blockers already link in current objects and are not
credited: Rva005810B6Sort, DebugStatisticsRecordTextureEnd,
AptMpGameSetupRefreshMapList, TerrainLogicWaypointLookups, AIIdleStateUpdate,
and AIAttackApproachTargetStateOnExit. No still-deferred body was retried.

No maintainer-only link cycle, census build/measure/history, nightly, boot
runner or shadow publisher was started. Broader closure/placement verification
remains outstanding. Scratch sources, before objects/receipts and proof.py
remain in build/ref-record-assign-link-20261015/.
