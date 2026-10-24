# WW helper provider split and link-seat audit, 2026-10-24

Inputs: BFME2 38caacbb4f; BFME1 f5140c1cff6a58e16276fd6de6788186286953d4;
MSVC7.1 through build.sh, unchanged original unit flags and donor headers.
Legacy census 11b3872700 (2026-10-23 23:06, retail-truth-4). No incremental
linked-byte gain, closed-strict result, or new conversion is claimed. All
source/ledger trials were restored and all claims acquired here released.

## Byte-exact split, measurement prerequisite

The three .cpp.txt files preserve the tested providers (comment trailing
whitespace normalized); ledger.patch moves
five existing rows to them without changing names, ranges, notes or bytes.
They explicitly instantiate the same donor-header templates as their original
units. No identity/layout inference or new donor naming was needed.

- vector.cpp: ctor 1791F0 (71B), existing gen-alias dtor 17EA90 (45B).
  Original unit fails only on unclaimed BooleanVectorClass Get_Bit/Set_Bit.
- xsurface.cpp: swap<Point2D> 6259C0 (33B). Original unit fails on the
  unclaimed XSurface Bit_Blit implementation's unresolved helper.
- w3d_dep.cpp: narrow string operator== 7780 (47B), list<string>::begin
  204163 (13B). Original scanner needs a FileClass constructor while retail's
  rowed ChunkLoadClass constructor accepts BFMEChunkInput; the unit also
  emits imported STL dependencies. Do not merely change the pointer name:
  the native constructor's input slot and class layout differ.

All five rows passed build.sh together, including source claims and string,
float and import checks. Original units have 164 own nonpadding matched bytes
in total; the existing alias contributes no extra bytes. No original unmatched
implementation was deleted or changed in the trial.

link_check.py on the original units reports 0 -> 0 linked bytes. On the three
new provider units it refuses: "not in census 11b3872700, so not previewable
(the next census measures it)". This is a measurement boundary, not a false
reject or evidence that the providers link. A closed current-ledger receipt
set or a normal authorized subsequent census is required before claiming gain.
Do not keep live ledger moves based only on the five exact byte results.

## Wide money formatter independent attempt

Retail formatter DF20, 2610B, has ten exact rows but the current unit loses on
_String_base<wchar_t>'s standalone destructor: 82B with nine qualified phantom
destructor calls, versus retail 14B at 142D70. The phantom calls are existing
inlining-cost carriers; their removal changes the parent formatter's code.

Trials beyond existing evidence:
1. Add an explicit empty forceinline _MoneyPhantom destructor: 10/10 row bytes
   stay exact, but standalone base destructor remains 82B and link gain is zero.
2. Raise inline_depth to 255 around that emitter: same result.
3. Replace the nine calls with late-folding this==0/exit guards: parent loses
   byte identity (1/10 rows fail). Reverted immediately.

Remaining requirement is a cost carrier preserving parent inline choices and
emitting the retail standalone base body. Do not repeat these variants or pin
another identity to the wrong 82B copy. Final restored gate passed 15/15 rows
across this unit and the three original WW helper units.

## Other lane checks and inherited fixes

Ran link_rank --top 30, --near 2 and --owner-gaps; class_views --blockers;
repair_queue.py link --limit 10; narrow name_globals --dry-run on the three
address-getter units (zero edits); and rehome_rows.py discovery. The one exact
entry-constructor rehome lead already links, so moving it adds zero bytes.
No matching data-back measurement artifact is present; no provisional ranking
was substituted. No census rebuild, full link cycle, nightly or boot runner ran.

Current previews show many obsolete index blockers already repaired upstream:
MapCacheClearUnseenMaps, GeometryInfoCtor, BuildListInfoXfer, Rva0032A186Finish,
Rva005E3C90Ctor, ParticleSystemManagerDtor, StructureToppleUpdateCtor,
ScriptEngine_dtor (883B), and stlport_wide_ifstream (1783B). Their apparent
index-to-current gains are inherited, not this session's work. DeletionUpdate,
FireSpreadUpdate and AssistedTargetingUpdate need the already-landed name
getter providers reflected in the measurement; no new getter is needed.

Still blocked by recorded class/compiler/provider prerequisites: Vector3 and
StreakLine scalar-deleting destructors; int/AsciiString insertion identity;
wide append identity; narrow/wide ios member access specialization; private
ModuleData/Snapshot tables; EvacuateDamage, PartitionFilter, Debug and font
virtual contracts; map subscript destructor identity; shader/filter list
roots; LargeGroupAudio's converged typed storage; AIUpdateInterface's private
root and constructor provider; Rva005C4280's base/derived destructors. Relevant
existing banks remain preferable to redoing these trials. RenderableRiverArea
ctor's named destructor is already rowed in Rva00082EF5Ctor.cpp, so its stale
index unresolved report does not justify a new destructor definition.

Fetched official BFME1 master 32774ab03393709a7f14331ba8d98d281a55ffd9. Kept
committed f5140c1c inputs because the submodule is foreign-claimed; inspected
its recorded linking repairs and target blockers rather than advance the
pointer without paired verification. No freshness-success stamp was written.
Resume from this bank when measurement/provider/class evidence changes.
