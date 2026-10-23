# Rejected auto-resolve entry-constructor rehome

BFME 2 checkout: e4d6909581. Restored local census: cb660e4d97,
2026-10-13 04:02 UTC; index SHA-256
4bc4fd38c27a025c8545b51f02fd25445391b93e51e964dfb8077a45aea9244e.
Committed link status measures 67e1365aa9 and was used for discovery only.
No index, status, pins, baselines or retained game source changed.

The read-only rehome_rows scan found one exact candidate before unrelated
failures: Rva004F6318EntryCtor.cpp into LivingWorldAutoResolveBattle.cpp.
The complete native constructor at 0x004F6318 is 29 bytes; both objects
contain identical whole body bytes and the same REL32 at offset19 to
Rva004F6093Holder's copy constructor (constructor-copies.json).
Existing caller4F6A2B and destructor/EH lifetime4F69C3/4F9C8E support the
entry identity. Existing target/donor provenance remains unchanged.

The trial used add_match --replace-existing to move only this row, and
removed the split file. Strict preparation passed30/30 before (two sources)
and30/30 after (one source), with one string literal and two float literals,
no baselined or skipped references. The retained owner object did not need
source edits. Private entry views fell8->7 and layouts7->6; Holder views
fell30->29. These trial reductions are NOT landed improvements.

## Why the trial was rejected

The current split unit already links. The current home does not: the legacy
preview still lists an unresolved armor helper, seven duplicate names,
COMDAT losers and wrong-selected copies. Rehoming would move29 currently
usable matched bytes into that nonlinking unit. Before preview: one of two
sources clean,29 bytes. Trial owner preview: zero of one clean,0 bytes.
Neither preview is maintained census or closed-strict evidence; both exit1.
No positive linking gain or new authored coverage is claimed.

All trial ledger/source changes and the generated landed attempt were
reverted. The restored ordinary gate passes30/30 across the original two
sources; the attached final byte transcript records this. Only this rejected
attempt's evidence and blocked record are committed. All three file/RVA
claims were released. Revisit after the owner can link, rather than repeating
an unchanged body/copy trial.

## Other link-lane probes and handoff

repair_queue link served6269 unlinked sources. link_rank U/D/L and its near
lists were checked against current source and prior verdicts. High-ranked
NetPacket, radar global, commudp callee, concat specialization, Quaternion,
PoolRef, OpenContain and vector-assignment copies already contain repairs
newer than the restored index. Previous PlayerList/GameInfo coalescing,
RvaF6Ret collision and deleting-destructor emission failures were not retried.
name_globals --dry-run on GapBodiesGE29, W3DSceneUpdateFixedLightEnvironments
and ConstIntGettersAddr found zero supported rewrites.

Two remaining old ControlBar call views have a newly matched processCommandUI
provider, but both callers (Rva0043D1C9Destructor and
AptInGameSpellBookInterface) are claimed by yasinschroeder-claude3.
The provider ControlBarCommandProcessing.cpp is absent from this census:
local link_check correctly refuses to preview it. No edits/claims were taken.
This lane is not declared exhausted; a restored census including the newly
matched providers should make the next ranking substantially more useful.

BFME1 donor d3f9000fe08615a100e844adfff57fa4a39cd615 was reviewed: retire
an extra constructor emission while retaining the proven owner. That general
principle applies, but its TileData class/address/body do not establish this
BFME2 entry's identity or link readiness and were not imported. Donor
6ffd3f498c98872efbb0ad242c3afea4640e4ef5 (StringBase call specialization),
3d83042a6cabae08e002a9f5a88c1c60f55a51d3 (canonical IME pointer), and
02480023624f5fc99518c10874e8e8e5c678ac4f (iterator destructor pin) were
also reviewed; relevant supported local principles are already applied or
need an actual target provider, not just a pin.

Freshness fetch reached official BFME1 master
ef090c9ed943ce407c69e0c202be172d24eb1916. Clean checkout/gitlink retained
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. The previously documented
comparative full gate was interrupted at the shared compiler lock; this
session did not retry the same outstanding large baseline verification or
silently substitute unverified headers. Pointer migration/update, comparative
full gates and changed donor sweeps remain outstanding; the previous
last-success stamp was preserved and freshness was not marked successful.
No maintainer-only verification runner was started.
