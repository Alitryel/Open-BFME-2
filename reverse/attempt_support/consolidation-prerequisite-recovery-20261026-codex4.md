# Prerequisite batch recovery, 2026-10-26, codex4

This session inherits four unpublished commits: 5769f08ef3 (Lifetime module-data
view), 6268c522d3 (Lifetime fields/diagnostic value), ae55e15569 (LargeGroup random
declaration ordering), and 4f7dc8ab01 (canonical GameLogic Hulk accessor adoption).
All remain preserved. The unrelated untracked reverse/zh_sweep directory and
preparation backups remain untouched. No new trial target is taken before this
batch's publication recovery. The allocated queue still assigns both target
TUs to family A repair shard 1/2; held/cross-family work is not taken.

## Current verification and demonstrated downstream scope

At outgoing base aa404c29b6, check_csv.py passes (98,272 function rows).
The six relevant sources pass ./build.sh: 19/19 functions, two literal checks,
no float/import failures. find_declared_unmatched passes the changed sources
and canonical header; the previously documented inline-anchor marker remains.
header_dependents.py --range origin/master HEAD still finds 1,137 sources.
The complete closure is reverified, with its result recorded below.

Fresh normal tu_skeleton.py --merge TU --dry-run checks retain both unblocks:

- LifetimeUpdate.cpp: seed, calcSleepDelay and module-data constructor accepted,
  six rows / 329 existing retail bytes. Actual composed object
  build/tu_skeleton/12399f8d70f7c89f.obj retains ten code-definition fingerprints
  and COMDAT selections, except the previously inspected absent-from-retail
  anchor's constructor inlining (nine to 28 bytes). Eleven unresolved names
  equal the standalone union after internal resolution. Data references remain
  TheGameLogic, the original diagnostic path and existing vtable alias.
- LargeGroupAudioUpdate.cpp: seed and random donor accepted, ten rows / 155
  existing bytes. Actual composed object
  build/tu_skeleton/e4f5f59f2cbbefd4.obj retains all fifteen code definitions and
  COMDAT selections. Nine unresolved names equal the standalone union after
  internal resolution; data references remain the existing vtable and diagnostic
  path. No anchor exception is needed for this composition.

These are demonstrated compatible donors, not confirmed downstream Luna
landings. No merge, split, row repoint or regenerated TU map is applied.
Lifetime constructor/Xfer still lack the shared UpdateModule/setWakeFrame
contract; pool key lacks its receiver method. LargeGroup's remaining donors
need constructor/destructor/pool/Xfer/update declarations and Object fields.
The earlier ModelCondition vtable-growth blocker remains recorded and reverted.
No unchanged blocker is retried as a source edit.

## Binding evidence and measurement limits

The inherited handoffs retain the pre/post-edit standalone and composition
proofs. Their canonical-header closure comparison covered 7,186 rows and found
only an inspected compiler-private anonymous namespace discriminator change.
Recovery rechecks the current 1,137-source closure snapshot and getter provider
inventory. getFrame still has exactly 393 identical providers, first selected
FiringTrackerXfer; the forced-inline Hulk accessor has no provider/reference.
The provider inventory equals the inherited after snapshot.

The current ledger contains 7,241 rows in that closure, versus 7,186 before the
inherited publisher's upstream rebase. Six source-definition snapshots differ
from the historical after snapshot, with concrete upstream changes:
Rva0037BCC4DeferredCtorCRC (fb93f24f78, FXList identity), AptSaveLoadCallbacks
(d831bc2403, data identity), AIStatesBfmeOnExit (38777f70d4, random log binding),
BridgeScaffoldBehavior (546ba17cad, remove unrowed loadPostProcess), RadarUpdate
(c60f6ffe5a, donor consolidation), and ScriptEngine appendMessage forwarder
(c7261d85a7, canonical AsciiString). Do not describe the entire historical and
current snapshots as identical; unchanged provider inventory and fresh byte
checks are separate evidence.

link_check.py --fetch-index succeeds but still supplies 47e030bafc (2026-10-26
08:28). The supported full-closure link_batch_audit.py --base origin/master
--tip HEAD --sources-from build/codex4-recovery-sources.nul reports an
inconclusive baseline and 1,137 objects without current strict link receipts.
This is not a newly verified lost-provider finding or link clearance. LINK-017
records the exact pending scope; census confirmation remains for the normal
maintainer measurement. No maintainer-only runner is invoked.

## Publication audit and measurements

Audited all pending origin/master..HEAD paths plus the recovery documentation:
no source moves/deletions/renames; no ledger repoints. Combined old/current path
and basename search covers active tools, hooks, workflows, source includes,
build inputs, registries and docs. The new LifetimeUpdateModuleDataView.h has
exactly two intended consumers, verified together. Existing canonical-header
consumers remain at their paths; active consumers need no repointing. Historical
EA path literals and evidence remain preserved. No protected identity/data key
is dropped; the single inherited header key was retired through its owner.
The current audit is build/codex4-recovery-path-audit-current.txt.

Recovered C++ bytes: zero. Net source-file reduction: zero. One private header
added by the inherited batch. Header debt retired: one (inherited acceptance).
Code/data identity debt retired: zero. No new linked-byte or ownership claim.
Keep file/class claims until a confirmed push; if the account slot is occupied,
hand off this audited batch and release claims after the runner lands it.

## Preparation recovery follow-up: shared-header adoption withdrawn

The runner completed the rebase before this recovery turn: HEAD b13188e6e0 on
0cd6b45068, four unpublished commits, no rebase state or conflict index. Applied
resyncStash c2010a7b9dc699865982061a23ed526a1e1897df with --index. Its obstacle
note and this evidence file are retained in the recovery commit. Its five
unrelated reverse/zh_sweep/packets files are restored untracked and untouched.
The original stash and refs/runner/preparation/1793021279769444774 are preserved.

The required git push --dry-run origin HEAD:master reproduced the recorded
failure: PlaceEventTranslator::translateGameMessage 0x0043218A swaps the build
and builder local stack homes (-0x1c/-0x20). The preceding hook group passed
1,524/1,524 functions; the next group failed 1/1,580. This is a real byte failure,
not a false reject or a reason to weaken verification.

Withdrew b13188e6e0's shared-header extension in a new commit,
restoring the header queue entry. The original adoption evidence remains banked,
and re_log.py records the blocked prerequisite. ./build.sh
Code/GameEngine/Source/GameClient/MessageStream/PlaceEventTranslator.cpp
Code/GameEngine/Source/GameLogic/Object/Update/LifetimeUpdateCtor.cpp passes
7/7, four literals, one float and no import failures after that withdrawal.
Restoring the original private GameLogic class was refused by class_gate.py;
that trial was not committed. The accepted repair instead retains the canonical
GameLogic declaration and casts TheGameLogic to a TU-local field-only
GameLogicHulkLifetimeView for the proven +0xA0 read. No new inline provider is
introduced. The constructor and dependent still pass 7/7 with the final view;
find_declared_unmatched.py and class_gate.py both pass. PlaceEventTranslator's
file/RVA claim belongs to another worker; no edit was made there.
The three local module-data/field/random-order prerequisite commits are retained.
Earlier claims of one retired header key and canonical-header clearance in this
note and the inherited adoption packet are superseded: header debt retired is
now zero. No source move, recovered byte, identity retirement or file reduction.

The outgoing path audit still finds no moves/deletions or ledger repoints.
The one added private header has exactly its two intended consumers, both in
the retained scoped prerequisite evidence. Strict full-closure link receipts
remain inconclusive as documented above; no selected-provider clearance or
census improvement is claimed. No maintainer-only runner was invoked.
