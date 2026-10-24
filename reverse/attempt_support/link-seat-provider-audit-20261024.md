# Link seat provider audit, 2026-10-24

Inputs: BFME2 23b7a47807, freshly fetched published census 11b3872700
(2026-10-23 23:06), committed BFME1 f5140c1c. No new recovery or linking
gain is claimed. All source trials were restored and all six acquired claims
released. This is a legacy scoped-preview audit, not closed-strict evidence.

## Vector trial and inherited fixes

ProductionPrerequisiteRecVectorCopy's earlier deferred worker at 4F5097
was free to claim. A declaration-only specialization of the record's
_Construct preserved all four byte rows and reference gates. However, a
sequential check after restoring the original source proved that upstream
25eca47756 already repaired this worker. The unchanged vector copy, parent
copy constructor and allocate-copy helper link 172 + 145 + 120 = 437 bytes.
The trial has zero incremental gain and was discarded. Do not reopen this
as a blocked conversion or claim those inherited bytes again.

Paired current-provider checking also resolves the apparent hero blockers:
CreateAHeroHero, Rva0040AA27, RvaTreeDtorFamily and FileSystem all link,
5359 + 217 + 4823 + 124 = 10523 bytes. FileSystem must be included to
replace its old conflicting bool-tree base destructor. These are the existing
repairs documented in hero-owner-link-20261024.md, not this seat's work.

Current objects also already link BuildListInfoCtor (369), BuildListInfoXfer
(305), Rva0032A186Finish (149), stlport_money_get (294), FormationTemplate
(917), ParticleSystemManagerDtor (525), Rva00600352 (184),
InGameHeroSelectInterfaceCtor (1024), and Rva006253F0Ctor (146).

## Remaining prerequisites

Read the existing banks before repeating these trials:

- Wide money formatting still has range-initializer and wide string-base
  destructor conflicts. Narrow/wide imbue retain the mutable assignment
  visibility problem; previous declaration-only trials either ICE VC7.1 or
  change native caller scheduling (link-seat-20261023c.md and 20261023d).
- DX8Skin still fails on DynamicVectorClass<Vector3>'s deleting destructor.
  Streak still needs its native destructor and both float vector deleting
  destructor providers; the established failed trials are in
  streak-float-wrapper-link-20261023/readme.md.
- BridgeBehaviorDtor, EvacuateDamagePoolKey and Rva003F8E20Destructor retain
  conflicting private virtual views. The latter's current attempt-log entry
  already records why neither competing view proves the native table.
- Rva005C4280 lacks the native base destructor and disagrees on the derived
  destructor. MultiplayerSettingsCtor needs its nonvirtual base destructor
  and typed table. StlSweepW4Rva00056BFE still has the allocator-proxy
  constructor conflict and wrong selected hashtable resize provider.
- AIPlayerTeamBuild_QueueUnits alone still reports unresolved queueSupplyTruck.
  That provider has now landed in AIPlayerQueueSupplyTruck.cpp, but the paired
  preview refuses because the provider unit is absent from census 11b3872700.
  This is a measurement prerequisite, not evidence the new provider is wrong.
- The shared int/AsciiString insertion cause includes PeerDefs, held by another
  seat. The BFME1 pointer is also foreign-claimed; leave those scopes alone.

## Lanes and acceptance checked

check_csv passes (98196 functions, 15765 symbols, 2175 data). Selection used
link_rank --top 30, --near 2 and wider near views, --owner-gaps,
class_views --blockers, and repair_queue link, followed by current-object
checks of the candidate/provider sets above. No measured incremental repair
survived; no new blocked verdict was attached to already-repaired bodies.

The BFME1 official master fetch reached 32774ab0. Reviewed donor geometry,
PeerDefs, locale and prerequisite-record linking changes; the applicable
geometry/record fixes are already inherited, PeerDefs is foreign-claimed,
and a pointer update belongs to its existing owner. No freshness success
stamp or submodule change was made.

name_globals.py --dry-run proposes zero files/edits. rehome_rows.py cannot
run because build/link_census/census.log is absent; this is an unavailable
fallback, not an empty queue. No matching data-back measurement artifact was
available. No census rebuild, full link cycle, nightly or boot runner ran.
Resume with changed provider/class evidence or a newer published measurement;
do not repeat the unchanged source variants solely because a seat restarted.
