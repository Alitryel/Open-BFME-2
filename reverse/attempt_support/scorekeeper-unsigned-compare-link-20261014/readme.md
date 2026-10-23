# ScoreKeeper unsigned comparator ownership repair

Base checkout: 5c8289f28b11be4df871f78824d6aae8a5ca416e. The runner index
measures 147cfae2cb, 2026-10-14 07:27; its SHA256 is recorded in
object-proof.json. The newer committed link_status queue is discovery only.
The index, census, status and history remain unchanged.

Rva0039D0FBMethod.cpp emits a losing external STLport less<unsigned int>
operator under /O1. Its three matched ScoreKeeper callers already inline
unsigned comparison. The matched owner is stlport_hash_map_int.cpp at retail
0x00758C50, with a 19-byte retail body. Apply the established TU-local
specialization with dllimport and forceinline to suppress the incidental
external copy while preserving the inline operation. No header, ABI, layout,
compiler flags, global, alias, pin or ledger row changes.

Target evidence and acceptance:

- Before and after link_check.py --prepare-current verifies all three native
  rows with strict reusable receipts. Final ./build.sh passes 3/3 byte matches
  (117, 392 and 86 retail bytes), with no string, float or import references.
- A further bounded --prepare-current on the edited unit and unchanged
  stlport_hash_map_int.cpp verifies 30/30 matched rows with strict receipts.
  The comparator owner remains a 19-byte retail copy.
- Refreshing those objects in memory against the same measurement index gives
  edited-unit findings 1 -> 0. The shared owner's six independent findings
  remain 6 -> 6. The local legacy LINKED preview gains 594 existing matched
  bytes (padding excluded); new authored C++ byte growth is zero.
- All 21 retained external COMDAT bodies have identical bytes, extents,
  digests and normalized relocation targets. No COMDAT is added. Only the
  losing comparator is removed; strong, undefined and weak bindings remain
  unchanged. There was no nondebug call relocation to that removed name.
- The commit hook reports a shadow divergent GameLogic::isScoringEnabled
  definition. This is among the 21 unchanged retained copies in object-proof;
  its prior local declaration and code are untouched. It remains independent
  code-identity debt, beyond the bounded local link result.
- Frozen definitions, class gate, new-variant/staged-peer admission, CSV,
  whitespace and EH checks pass. EH has zero applicable/missing/baselined
  rows. Enforced converged-data checks protect eight addresses, with zero
  second names or unjudged rows. Placement resweep finds zero bodies/pins.
- The shadow data check retains exactly its two pre-existing wrong-name
  findings: _scoringBuildingDestroyMask at 0x00A02868 and _scoringBuildingMask
  at 0x00A0284C. Historical and repaired object data facts compare equal.

A declaration-only trial changed register allocation in addObjectLost and
failed its byte gate; it was discarded. The final inline specialization is
byte-exact, following the already verified ScriptEngineRva00206255.cpp pattern.
This is self-strict byte verification plus a bounded legacy link preview.
Closed-strict closure, actual link placement and a new census gain remain
unmeasured. No maintainer-only runner was started.

Reproduction: ./build.sh on sources.txt's path; link_check.py --prepare-current
on that path and Code/Libraries/Source/WWVegas/WWLib/stlport_hash_map_int.cpp;
ordinary link_check.py on those two paths. Committed JSON records paired
findings, body/relocation comparison and source/object/index hashes. Original
objects, receipts and comparison scripts remain in build/link-seat-20261014b.

Related-cause sweep: Rva00171128Lookup.cpp, Rva00079B41UniqueSearch.cpp and
Rva002F0E5EUniqueSearch.cpp already link locally (124, 134 and 134 bytes).
LivingWorldCampaignAct.cpp and WeaponXfer.cpp also already link locally;
no obsolete queue entry was retried. Larger multiblocker families require
separate supported repairs. The unchanged STLport owner's six findings and
these two shadow data findings are outstanding beyond this repair.

Donor review: retained verified BFME 1 gitlink
 a7c38d3b2597121f178ab5190b3062478823257d. Reviewed linking repair
 d2e21369067f2f2c762c1c7ec2792c75f1ecf53d: removing incidental per-unit
emitters in favor of existing retail providers applies as an ownership
principle. No donor names, layouts or source were imported; target bytes prove
applicability independently. Official upstream fetch found
58ab850fd1f734e310048b2e19c1ecb7ba112a3f ahead of that verified gitlink.
Prior old-input baseline preparation remains blocked by compiler stalls and
thousands of stale units (count-tree-ai-link-20261014 evidence). The same
unchanged full-gate prerequisite was not repeated or marked successful;
verified inputs and the freshness timestamp are preserved.
