# Link seat follow-up, 2026-10-23

Inputs: BFME2 52b92c7d3f; published index b711de3634, 2026-10-23
14:28, retail-truth-4; verified BFME1 96c88c73a5cd1a58fc2f8db691beea50acd996db.
No production source or ledger change was made. No authored C++, linked,
self-strict or closed-strict gain is claimed. No claims were acquired.

## New target evidence: delayed-event class views

Paired current-object legacy preview of Rva003FD3EFDtor.cpp,
Rva003FD4DADtor.cpp and Rva003FD3C7Ctor.cpp remains 0/289 nonpadding bytes.
Each is blocked by its class vtable COMDAT. The destructor units declare four
Snapshot slots, whereas the full audio constructor declares two BfmeBaseVNH
slots. Equating those private views would not reproduce the native tables.

Direct reads of game.dat establish these complete seven-slot tables (RVAs):

| Table | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 7FE024 | 2B30AE | B3FD0 | 2B30A8 | 3FD1FA | 3FD43B | 5CB9FF | 910FB |
| 7FE1B0 | 2B5972 | B3FD0 | 2B596C | 3FD219 | 3FD522 | 5CB9FF | 22C4CB |

The named literal getters independently identify DelayedAudioEventModule and
DelayedWorldTextEventModule; their original C++ record class names remain
unknown. Slot 3 providers are currently rowed under Rva003FD1FA/Rva003FD219,
and the audio slot 4 provider is rowed under Rva003FD3EF. Reconciliation must
include those owners and the real base lifetime, rather than adding aliases
or empty virtual implementations. LivingWorldLogicDelayedEventXfer.cpp has a
seven-slot structural view useful for comparison, not proof of every ABI.
The related world-text constructor 3FD498 and slot 4 body 3FD522 have live
foreign claims; their scope was left untouched. No source variant was built.

## Current previews and exclusions

- Rva00801CB0 remains 0/523 B with a Member2C vtable conflict. Target table
  CE0F20 contains the deleting destructor 663430, not the private `handle`
  slot. The earlier handoff's real-class/provider prerequisite still applies.
- MultiplayerSettingsCtor remains 0/159 B: nonvirtual SubsystemInterface
  destructor and unowned C191B8 table. Existing two failed initializer/lifetime
  trials and conflicting destructor identity evidence were reviewed, not rerun.
- ScreenBWFilterInit remains 0/101 B: missing screenBWFilter and DOT3 objects.
  Existing filter-root/table ownership evidence remains prerequisite.
- Rva003F86F9 constructor/parser has a concrete native table/class identity
  lead, but both target RVAs were claimed by another seat. No edits were made.
- AIUpgradeScienceBuilder constructor/destructor previews need the currently
  rowed Register/UnRegister/shutdown/597FC5 provider cohort. Provider renaming
  already exists upstream; refreshing it cannot be credited as a new repair.
- Current source already links ArmySummaryCopy (803 B), money-put string
  (2,825 B), FireLogicSystemObjects (5,463 B), W3DGhostObjectScene (3,864 B),
  AIStatCollector (362 B), FlightDeckInfoVectorInsertOverflow (441 B), and
  partitionmanager_impl (2,499 B). RegionConstructor plus its existing
  DynamicPortalLinkVector provider also links. These are inherited fixes.

## Checked lanes and limits

`check_csv.py` passed. Refetched the published index (22,772 objects).
Ran link_rank top30, near2, near1/top200 and near5/top80;
class_views --blockers; repair_queue link --limit12; current-object previews;
and reviewed the prior donor/linking handoffs at the unchanged verified BFME1
pointer. No unchanged blocked source trial was repeated.

`name_globals.py --dry-run` on eligible authored units proposed zero edits.
Read-only `rehome_rows.py --limit 8` searched the split-unit candidates; its
available census.log is dated October 12 and does not match the published
October 23 measurement. Placements from that log are leads only. No ledger
move or gain is claimed. No matching data-back measurement artifact was
available, so no data-back ranking was manufactured.

No full census, link cycle, nightly or boot runner ran. Existing untracked
assembly and reverse/zh_sweep preparation were preserved. Progress against
origin/master reports +0 for authored C++ and census-linked bytes. Resume
with a resolved provider/class prerequisite, newly released claimed work, or
a fresh matching measurement artifact; do not repeat the unchanged trials.
