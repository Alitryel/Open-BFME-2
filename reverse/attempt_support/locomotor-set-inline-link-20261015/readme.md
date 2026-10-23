# Locomotor-set inline-emitter link repair

Base tree: c2aa1eaa2401c3727bb1eef57217d82cdcd5c286.
Measurement: legacy census 28269d8e8d, 2026-10-15 09:31 UTC.
Index SHA256: 6128e4df8c49e7783f07dcf447831cfd3c9850b9bf46249d968878411907b551.

## Change and evidence

Eight available consumers emitted the same unused seven-byte
?getLocomotorSet@AIUpdateInterface@@QBEABVLocomotorSet@@XZ COMDAT
(digest 1e3de62314d1). It loses to the first copy in this census,
PartitionManager (c9e4fc94143d). Mark the private view method
__declspec(dllimport) __forceinline to retain its inlined address calculation
without emitting a competing outline. All bodies, layouts, flags, globals,
headers, pins and ledger rows keep their existing definitions. No import call,
undefined name or weak external is introduced.

The existing byte-exact BFME2 callers prove their +0x1CC LocomotorSet address
calculation. The helper has no proven retail address; neither its standalone
identity nor the census winner's layout is established by this repair.
Normalized retained object bytes and symbolic relocation bindings compare
exactly. There is no incoming nondebug relocation to any removed getter.
The ninth losing consumer, HordeContainIface11CSlots.cpp, is held by another
worker and was excluded before claiming and editing.

## Donor review

Verified BFME1 pointer: a7c38d3b2597121f178ab5190b3062478823257d.
Official master fetched at 61be6c32 during this session. Reviewed linking
repairs c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 (DamageInfo ctor) and
66b19a8e95a4add525ef808fcea088e306798e2b (Apt allocation copies).
The imported inline emission technique applies; their types, target addresses,
layouts and gains are not carried into BFME2. The established BFME2 precise-Z
repair provides a locally verified sibling technique.

BFME1 freshness advancement remains blocked by the live foreign claim on
file:reference/open-bfme-1 (codex-6bc6-20261008). Preserve the clean verified
checkout/gitlink. No successful-check stamp was written. Comparative full
verification remains required before a pointer update.

## Acceptance and result

Before and after, bounded link_check.py --prepare-current verifies 98/98
matched rows across the eight owned sources with strict reusable receipts.
Explicit ./build.sh also passes 98/98; 77 string literals plus four empty
references and 53 floats pass, none skipped/baselined; zero named imports.
EH: 18/18 EXACT, zero missing objects or baseline debt. Existing funclet labels
renumber naturally and are verified through unchanged parent EH data.
Frozen-file and class gates pass. Converged data enforcement: eight addresses,
zero second names or unjudged rows. Shadow data: five existing baselined
wrong-name findings, unchanged in the paired proof. No new variant finding is
introduced (13 pre-existing findings remain). Placement rescan: zero bodies,
zero pins. check_csv.py and git diff --check pass.

proof.py uses ignored before-source/object/receipt snapshots under
build/locomotor-set-inline-link-20261015/before/. It checks strict object
currency, exactly one removed getter per object, all 610 retained COMDATs,
complete retained nondebug section bytes/flags/extents/definitions and symbolic
relocations, external/weak bindings and data facts. It compares paired previews
against the same index, refreshed only in memory, and checks that the winner
and all other existing selection decisions remain unchanged. Hashes, detailed
before/after findings and data debts are in object-proof.json. To reproduce,
compile the parent and changed sources under identical inputs, save the parent
objects/receipts in the documented scratch directory and run proof.py from
the repository root with the recorded index. Stored evidence is a paired local
result, not a census or closure receipt.

| Consumer | Before findings | After findings |
| --- | ---: | ---: |
| AIFollowPathStateMethods.cpp | 2 | 1 |
| AIStatesDerivedOnExit.cpp | 9 | 8 |
| AIGuardRetaliateStates.cpp | 5 | 4 |
| AIStatesBfmeOnExit.cpp | 8 | 7 |
| AIPlayerTeamBuild.cpp | 20 | 19 |
| AIGroupMoveFormation.cpp | 13 | 12 |
| WallUpgradeUpdateScan.cpp | 3 | 2 |
| QueueProductionExitUpdateExitObjectViaDoor.cpp | 5 | 4 |

Eight COMDAT conflicts disappear; every other finding is unchanged. The
consumers own 27,361 existing nonpadding row bytes. All eight still have
independent blockers, so legacy local LINKED remains 0 -> 0 bytes. New authored
C++ bytes: 0. Self-strict receipts are current; closed-strict closure and gains
are unmeasured. No census/index/status/history is rewritten, and no full link
cycle, nightly or boot runner was started.

The smallest remaining dependency is AIFollowPathStateMethods.cpp's
AIStateMachine::getGoalPathPosition(int) const. Other unresolved dependencies
and duplicate/COMDAT/selected conflicts are listed in link-after.txt and the
paired JSON. They need separate supported repairs.
