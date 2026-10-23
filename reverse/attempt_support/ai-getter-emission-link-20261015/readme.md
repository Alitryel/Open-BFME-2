# Suppress surplus Object AI getter emission

Source base: 5d592ff8d76197a1682eaa7e54b2ae743912e30a. Local index measurement:
19a2565407, 2026-10-15 09:33 (original census 5986a99448, 04:52).
object-proof.json records the unchanged index hash, paired findings and object
hashes. Committed link_status.csv is queue evidence, not this measurement.
No census, index, status, history, baseline, pin, layout, header or flags changed.

Eight listed units emitted competing seven-byte copies of
Object::getAIUpdateInterface. Each surviving retail caller inlines the +0x258
load. Adopt the existing BFME 2 sibling declaration pattern, dllimport plus
forceinline, to suppress only the surplus out-of-line definition. The getter
has no independently claimed retail body here. Existing identities and class
views are retained; this does not establish a complete Object layout.
No reference function body is imported.

Acceptance:

- Strict bounded byte preparation before and after: 16/16 rows in eight units,
  reusable dependency receipts; two strings and 17 float references verified,
  zero named imports, no skipped references or literal baselines. Final
  whitespace cleanup in SupplyTruck was separately prepared, 1/1 exact.
- Saved-before/current-after object proof removes exactly one seven-byte
  8b8158020000c3 COMDAT per unit. Every retained nondebug section, extent,
  binding and normalized relocation is identical, including EH/directives.
  Current objects are self-strict. Scratch proof.py and sections.py, source
  backups and old objects/receipts remain in build/ai-getter-emission-link-20261015/.
- Paired same-index in-memory local preview refreshes the same eight objects
  on each side. Findings 31 -> 23, exactly one getter finding removed per unit;
  all other findings unchanged. TurretAI goes 1 -> 0; clean cohort 0/8 -> 1/8,
  linked nonpadding bytes 0 -> 74. Ordinary link_check agrees (exit 1 for the
  seven still-blocked units). External providers retain legacy index currency;
  no closed-strict gain, executable placement or new census is claimed.
- EH 4/4 EXACT without baselines or missing objects. Frozen definitions,
  class gate, new COMDAT variants, CSV and whitespace checks pass. Converged
  data: eight sources, eight protected addresses, zero second names/unjudged.
  Explicit enforced shadow data check reports one existing SiegeDeploy
  wrong-name at 0x00A042A4; saved-before/current-after findings are identical
  (data-paired.json). This shadow debt is not fixed or baselined here.
- Placement resweep: zero bodies, zero pins. Authored/matched C++ growth zero.

Remaining local findings:

| Unit | Before | After | Independent blockers |
| --- | ---: | ---: | --- |
| TurretAI_friendCheckForIdleMoodTarget | 1 | 0 | none |
| AITNGuardReturnStateOnEnter | 3 | 2 | lookForInnerTarget unresolved; getContainedBy COMDAT |
| AIGroupGetCenter | 5 | 4 | FindGroundPath unresolved; getCenter duplicate; isKindOf/getNext COMDATs |
| QueueProductionExitUpdateExitObjectViaDoor | 6 | 5 | consume/rva00262FEB unresolved; Vector3 and locomotor COMDATs |
| SiegeDeployHordeInitiate | 3 | 2 | wrong selected vector-base destructor |
| ScriptActions_doTeamGarrisonNearestBuilding | 4 | 3 | STL out-of-range unresolved; isKindOf COMDATs |
| SupplyTruckStateMachineOnEnter | 4 | 3 | BitFlags constructor/clear and wrong selected clear |
| AIGroupScatter | 5 | 4 | iterator insert unresolved; getMinMaxAndCenter duplicate; aiMoveToPosition/isKindOf COMDATs |

Reference linking review: clean verified BFME 1 gitlink/checkout remains
 a7c38d3b2597121f178ab5190b3062478823257d. Reviewed donor repairs de59a7e9
(shared inline reconciliation) and 4966496c (surplus inline emission). Their
ownership/emission principle applies; donor Apt layouts do not. Official
origin/master is 9bbab7963c3dac0ef8da8c46860e972ecbafe29d after the fetch.
Reference update remains blocked by another worker's live file claim and
outstanding old/new full-gate comparison documented in
../unicode-comparator-link-20261014/readme.md. Verified inputs are retained;
no freshness-success stamp or pointer update is claimed.

Earlier audio-completion duplicate candidate was recorded blocked and its
claims released: its consumer file is held by claude-haiku-8. No source edit
was attempted there; bounded preparation passed 3/3. Several stale ranked
candidates already link in current objects and receive no credit:
Rva00500BF5TreeInsert, ScriptActions_doMoveUnitTowardsNearest,
ScriptActions_doMoveTeamTowardsNearest and Rva000C4069PristineQuery.
Still-deferred reconstruction trials were not repeated.

No maintainer-only link cycle, census build/measure/history, nightly, boot
runner or shadow publisher was started. Broader closure/placement verification
remains outstanding.
