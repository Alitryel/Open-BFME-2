# Ranked link-repair audit, 2026-10-23

Parent: adbad512aa. Verified BFME1 pointer: 96c88c73a5cd1a58fc2f8db691beea50acd996db.
Published census: 0393df10e2, 2026-10-23 19:47, fetched with link_check --fetch-index.
No source change or incremental linked-byte gain is retained. No full census,
link cycle, nightly or boot runner was started.

## Water base trial and restoration

Ranked sole blocker VBase00C6EE28 served Rva0030902ECtor.cpp and
Rva0030CAA9OwnerCtor.cpp. Claimed both files and their 31 ledger RVAs.
Marking their base novtable removes required native initial purecall-vptr
stores and changes native EH states. The byte/EH gate refused the trial;
this is a real mismatch, not a false reject. All source edits were reverted.
The restored units pass --prepare-current: 31/31 rows, all auxiliary checks,
and reusable strict receipts. All 33 claims were released.

More importantly, the unchanged six-provider baseline already links 1,565 B:
Rva002E4049Dtor.cpp, Rva0030902ECtor.cpp, Rva0030CAA9OwnerCtor.cpp,
Rva0030CAA9OwnerDtor.cpp, Rva0053805DBaseCtor.cpp, Rva0053805DBaseDtor.cpp.
The isolated ranked refusal was an old selected-copy result. No gain is credited.
Local diagnostics: build/water-vbase-prepare.log,
build/water-vbase-restored-prepare.log, build/water-all-before.log.

## Queue review

Ran link_rank --top 30 and --top 100 --near 1, class_views --blockers,
repair_queue link, and paired current-object previews for the first 30 and
90 further ranked units. These are legacy in-memory predictions, not a new
census or closed-strict result. Many apparent opportunities are already fixed:
Hashable providers (see hashable-header-link-20261023.md), water bases,
Rva005E9F3F/B17, the two StlSweepR3 allocator units, and the transition cohort.
The unchanged five-unit transition baseline is 5/5 clean, 1,852 B:
FamilyTailDtors1DBAC3.cpp, Rva0035FF76Ctor.cpp, Rva0035FF76Init.cpp,
Rva0035FF76Update.cpp, Rva0035FF76FamilyInitDraw.cpp. Do not retry its
pure/concrete declaration discrepancy solely from the old census.

Reviewed actual unresolved leads and prior evidence before declining retries:
DX8SkinClearVisibleList needs the native deleting-dtor compiler shape;
FormationTemplate is claimed and depends on the CameraMarker vector owner;
AIStatCollector has a verified bank awaiting current provider/index closure
(ai-countmap-native-lifecycle-seat2-20261023.md); FireLogicSystemObjects needs
native set lifecycle and registration ownership; narrow-string initializers
need the recorded type/name ownership reconciliation. queueSupplyTruck remains
an independently deferred compiler reconstruction, not a missing declaration.
MapCache clearUnseenMaps pair cleanup and FireSpreadUpdate's DisabledMask/CRC
ownership were already tried; no new evidence warrants repeating those trials.
PeerThreadOpaqueConstructor now needs the native PeerThreadClass destructor,
not its obsolete intermediate-base alias. Its table entry is 38ADC6 and native
complete destructor 38ADE2; recovery, not another base alias, is required.

name_globals.py --dry-run reports zero files/edits. rehome_rows.py could not run
because build/link_census/census.log is absent; this tool failure is not an empty
queue. No matching link-cycle data-back measurement artifact was available, so
no provisional data-back ranking was manufactured.

BFME1 official master is f5140c1cff6a58e16276fd6de6788186286953d4; retain the
verified pointer. The submodule is claimed by another worker, and the existing
freshness comparison records the same FireWeaponWhenDeadBehavior DIR32 conflict
under old/new inputs (link-reference-freshness-20261023.md). No freshness success
was recorded. Reviewed donor linking work remains as recorded there; no new
supported transferable repair was found.

Resume from a changed provider/owner, released relevant claim, current closure,
or a fresh measured index. This audit must not be counted as C++ or linked-byte
progress. The diagnostic logs are disposable local reproductions; the key
verdicts and failed hypothesis are recorded above.
