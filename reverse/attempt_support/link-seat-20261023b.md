# Link-provider triage, 2026-10-23

Seat: yasinschroeder-codex, gpt-6.1-sol. Initial tree 5d9a8982ea;
refreshed to 2bf722e90d before recording this handoff. No C++ changes or
new linked-byte gains. All claims released. This supplements, rather than
replaces, link-seat-20261023/final-triage.md and its preserved trials.

## Inputs and checks

The published index is retail-truth-4 at 0fa62a2841 (2026-10-22 23:07).
link_check --fetch-index retained that index and downloaded its objects.
check_csv passed, including after the final pull: 98,087 functions, 15,851
symbols, 2,138 data rows. No census, full link cycle, nightly or boot runner
was started. All results below are legacy per-file previews; there is no
self-strict or closed-strict gain claim.

Reviewed link_rank --top 30, unresolved/near-2 rankings, class_views
--blockers and repair_queue link. Explicit current-object previews covered
70 near units (27 already link) and another 100 (10 already link). Their
apparent 33,835 B and 20,429 B gains against the census precede any edit and
belong to inherited work. Do not credit them again.

Pairing current providers also proves these inherited results:

- HordeContainIface11CSlots.cpp links 23,871 B with current Thing.cpp;
  the first-copy isKindOf blocker in a caller-only preview is stale.
- OpenContainModuleDataConstructor.cpp and its current FamilyDeletingDtors
  provider already link. The old private ModuleData table was removed.
- MapUtilLoadMap.cpp links 613 B with the existing map-dimension data owner,
  MapUtil_unk_YA_NAAVDataChunkInput_PAUDataChunkInfo_PAX_Z.cpp (164 B).
- W3DView_Rva0008BB27.cpp and View.cpp already link 17 + 802 B. Moving the
  getter row home releases no bytes.

name_globals --dry-run proposed zero files/edits. rehome_rows was checked
without --apply; the EntryCtor and GenP12pod leads have the unchanged
zero-gain findings in final-triage.md. The View getter lead is also zero-gain.
No data-back ranking was invented without a matching measurement artifact.

BFME 1 stays at verified f890413e75e671748215ba2ef3304aa7953993e9.
The paired full-gate receipt in bfme1-freshness-20261022-f890/readme.md is
under 24 hours old. Official master was fetched at c5880f3ba20e597757d5bc83e25a0a1c15298cfa;
its later three-emitter linking repair has no corresponding BFME 2 units.
The pointer was not advanced without the required paired verification.

## Concrete prerequisites

### LivingWorld observer contracts

The paired ScoreKeeper preview leaves LivingWorldScoreKeeper.cpp linked at
1,510 B and LivingWorldScoreKeeper_Unresolved.cpp blocked at 902 B by the
BuildingObserver, RegionObserver and PlayerObserver tables. class_contract
--class LivingWorldBuildingObserver compiled all five views read-only. Its
four suggested callback signatures are majority names, not retail identity
proof; the views disagree about virtual destruction and overrides.

Native BuildingObserver table C77F44 has four slots, three folded at
47A69C and the last at 50B238. Planning's secondary table C75148 instead
has 47A69C, 5CE125, 5CE130, 50B238. The base's 7-byte destructor restores
its table. Thus novtable is not an evidence-backed local fix: teardown
still needs that store. Reconcile the callback owner/override contract and
the Region/Player bases together before adopting a header. The generic
header generator alone does not express this virtual contract. No header,
contract or source was changed, and no false-reject is asserted.

### PingThread helper identity/ABI

Thread_Function's 410 B still have just one undefined symbol:
?rva0054F99E@PingThreadClass@@AAEHIH@Z. Its 234-byte native target is rowed
as the global stdcall ?MeasureIcmpPing@@YGHIH@Z in PingThread.cpp. The
caller passes ECX=this; the helper never reads ECX, explaining why the
global spelling byte-matches while failing to provide the member symbol.

Zero Hour's PingThread.cpp:419 calls it PingThreadClass::doPing. However,
the committed sweep cache grades that donor as no-placement (272 B,
8 relocations), not the unique whole-body placement required for
canonical:zh. docs/naming.md also disallows hand-renaming a real name on
that hint, and rename.py cannot express the signature change. A supported
identity/ABI correction is the prerequisite; no alias or second pin was
added. The older partial at re_attempts.log's Thread_Function entry already
describes this exact missing owner. Do not restart its conversion.

### DynamicVectorClass<Vector3>

DX8SkinClearVisibleList.cpp's 1,618 B now have only the differing dynamic
vector table and scalar-deleting destructor. The first copies come from
FXShaderRendererSkin.cpp. Its private DynamicVectorClass declares only
Resize and a destructor, whereas the donor header used by DX8Skin also
overrides Clear and both ID overloads. Both inherit six base slots.

The rowed dynamic constructor F1C7A stores BCEFDC. Reading retail's six
entries gives RVAs F28A7, F1C16, F0CF9, F1C0D, F1CA6, F1CA1; base table
BCEFAC contains F1CF7, F1C16, F0BF1, F0CD4, F0DC5, F0E20. Thus merely
suppressing DX8Skin's table would bind it to an incomplete private view.
The native slot F1CA6 is currently rowed under a TCBClass instantiation,
so fold/owner relationships also need examination before assigning new
identities. Reconcile the full vector contract and its providers, rather
than masking the conflict. No source trial or byte-gate failure occurred.

## Other deferred causes

The E16 destruction, wide range-initialize identity, narrow string helper,
Eva duplicate, hero/translator/hotkey virtual owner, FlightDeck and local
player data constructor issues retain their previously recorded concrete
blockers. Their failed source variants were not repeated. New upstream
Snapshot/simple-scene destructor repairs were reviewed after pulling;
their four already-fixed units are not new work for this seat.

Resume when provider identity evidence, a class contract or a missing body
changes. Current-object previews must include the affected provider as
well as its consumer before measuring a new improvement.
