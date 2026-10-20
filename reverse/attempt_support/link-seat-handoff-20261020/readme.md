# Link repair seat handoff, 2026-10-20

Model: gpt-6.1-sol. Four verified repair commits:

| Commit | Cause | Incremental legacy linked bytes |
| --- | --- | ---: |
| af6283cbd3 | AsciiString tree insertion caller specializations | 564 |
| c870797b04 | Screen material inline helper ownership | 448 |
| d890271bae | Shared POD-map allocator and destructor ownership | 1,201 |
| e8050c749a | TeamFactory constructor virtual slots and map destructor | 119 |

The combined current-object preview against published census b73720bed9
(2026-10-20 05:34) reports eight of eight units clean, 0 -> 2,332 bytes;
see final-preview.txt. Individual before/after, byte gates and strict self
receipts are in the sibling int-ascii-insert-link-20261020,
screen-material-link-20261020, pod-map-link-20261020 and
team-factory-ctor-link-20261020 evidence directories. Frozen-definition,
new-variant and CSV checks pass. This measures the legacy predictor;
self-strict receipts do not establish closed-strict closure or an actual
full link/census improvement. No census, link cycle, nightly or smoke runner
was started. No authored C++ coverage was added.

The POD allocator provider's whole 36-byte masked body agrees with the
existing 0x0023E863 pin, but its alloc-proxy call at 0x0014F3C4 has no known
address. Removing a conflicting 33-byte copy changes the shadow binding
classification to wrong/unknown. Existing divergent helper definitions and
extent debt remain. No pin or baseline waiver was added; do not claim
identity closure from the legacy gain.

Three final blocked trials were reverted and recorded with re_log.py:

* CreateAHeroDataAssign, 0x00409359: declaring the pair destructor still
  emits its competing COMDAT; importing its inline body preserves seven
  rows but changes the erase provider to an import dependency. Both link
  previews stay at zero. Needs coherent pair/erase ownership reconciliation.
* AITeamBuilder::checkIdleTeams, 0x0059AA37: forcing vector<Object*>::push_back
  inline overruns the 402-byte parent; ordinary imported inline emits an
  IAT call in place of the native direct call. Both byte gates refuse.
* MilesAudioManager::loadPostProcess, 0x000587C6: declaring either
  AudioTriggerArea push_back or its overflow changes the native EH shape;
  a displacement at +253 needs 257 bytes versus the proven 254-byte row.
  The competing overflow holds out the E8 provider's 352 bytes. Its existing
  fold-proof lives in that provider, so removing its correct copy is invalid.

Restored source verification passes all 7, 2 and 314 rows respectively.
These were short ownership probes; no near-matching reconstruction remains
in Code/. Claims for the failed probes were released.

Current probes also establish that the farm update unit already links
(819 bytes) and Rva0009B510CameraTransform already links (729 bytes), so
stale rankings must not be counted as repair gains. AerialPathfinder's
2,130 bytes still show sin/cos blockers, and LivingWorld DefendHomeTerritory's
341 bytes show vector push_back; their file/RVA claims belong to other seats.
The larger class, parser, vtable and missing-callee prerequisites remain in
existing evidence. The session stops at its context limit after several
repairs; this is not a claim that all eligible queues are exhausted.
