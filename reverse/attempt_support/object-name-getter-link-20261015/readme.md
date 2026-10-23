# Object name accessor emission repair

At BFME 2 09891d13f0, ScriptConditions_evaluateTeamStateIs.cpp and
CastleMemberBehaviorRva00399165.cpp each emit an unused seven-byte
Object::getName COMDAT, digest 6447ac3bafe3. Their existing callers inline
the Object +0x88 address calculation. Marking only these two accessors
imported forceinline suppresses their conflicting external definitions.
There is no new import reference, layout, identity, ABI, compiler flag,
header, ledger, pin or baseline change.

Target basis is the existing matched NAMED_SELECTED dispatcher case 37
at 0x003E9B6A (209 bytes) and CastleMemberBehavior interface slot 45 at
0x00399165 (200 bytes), whose verified callers access the name at +0x88.
The original ledger records the source and target evidence separately.
The two other census copies, in AIUpdate and PhysicsUpdate, have a
different digest and are outside this repair. No assertion about their
target correctness is needed or made.

Discovery used repair_queue.py link, link_rank.py and current-object
screening. Several older-ranked getter conflicts are already fixed in the
current sources and were not retried. Both edited files were claimed
before editing and passed find_declared_unmatched.

## Paired measurement

index-meta.json records the unmodified index SHA256 and measurement
19a2565407, 2026-10-15 09:33, derived from census 5986a99448, 04:52.
Both directions refresh only the same two-object cohort in memory.
The independent CLI previews and object-proof.json agree:

| Consumer | Before findings | After findings | Existing nonpadding bytes |
| --- | --- | --- | --- |
| ScriptConditions | 6 | 5 | 9,907 |
| CastleMemberBehavior | 2 | 1 | 200 |

Exactly one getName COMDAT finding disappears per source. All other
findings are identical. ScriptConditions still needs TransportStatus's
destructor and ObjectTypes::prepForPlayerCounting, and retains the
ThingTemplate::isKindOf and BitFlags<116>::clear COMDAT/selection findings.
CastleMemberBehavior still needs TheKey_objectBaseName. These are separate
dependency repairs. Authored C++ growth and predicted linked-byte gain
are both zero; the verified improvement is two fewer link conflicts.

These are **legacy local previews** with **self-strict current receipts**
for the two edited units. External provider closure is not refreshed or
proven closed-strict. No actual linker placement or fresh census is claimed.

## Acceptance

- Bounded link_check.py --prepare-current before and after, and independent
  ./build.sh: 51/51 rows match, three string literals and six float literals
  verified, zero named imports, no skipped/baselined references.
- Exactly the two seven-byte helper COMDATs disappear. All 177 retained
  COMDATs and every retained nondebug section, byte, flag, definition and
  normalized relocation are unchanged, including EH tables and directives.
  No incoming nondebug relocation targets either removed helper, and no
  new COMDAT variant appears. object-proof.json contains the paired facts.
- EH 23/23 EXACT, no baseline or missing object. Class, frozen definitions,
  new-variants admission, CSV and whitespace checks pass. Placement resweep
  returns zero bodies and zero pins.
- Enforced converged-data check: two sources, eight addresses, zero second
  names or unjudged rows. All data-reference facts are identical before/after.
  The optional data_check.py --enforce probe still refuses two pre-existing,
  outside-baseline wrong-name guard references at 0x00A02E28/0x00A02E30.
  This shadow debt is reported, not suppressed or described as passing.

The comparison script, original sources, COFF objects and strict dependency
receipts remain in ignored build/object-name-getter-link-20261015. Reproduce
by preparing sources.json at the recorded checkout, snapshotting sources,
objects and .deps.json receipts into before/, applying this change,
preparing again and running proof.py. The script verifies index SHA256,
retained sections, data facts, and the exact paired finding difference.

## Reference review and broader limits

Verified BFME 1 checkout/gitlink remains
a7c38d3b2597121f178ab5190b3062478823257d. The previous dedicated donor
review is reused. Reviewed c1315665a1b22beb7e6d9279548fe5b1c26ed1f9
(DamageInfo) and newly fetched 66b19a8e95a4add525ef808fcea088e306798e2b
(Apt allocation) repairs: their imported-forceinline emission mechanism
applies, while their bodies, types and layouts are unrelated. No donor
inputs were imported.

Official master was fetched at 61be6c32. The reference directory has a
live foreign file claim; the prior old/new comparative full-gate blocker
documented in ../unicode-comparator-link-20261014/readme.md is still
outstanding. Preserve the verified pointer and write no freshness-success
stamp. No census build/measure/history, full link cycle, nightly, boot
runner or shadow publisher was started.
