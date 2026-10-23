# Link seat follow-up, 2026-10-23

Target checkout 798d0969f9, published census b711de3634 (14:28 UTC).
This session makes no C++ or linked-byte gain. All trials are reverted and
all claims released. These are legacy per-unit previews; no closed-strict
or full-link result is claimed.

## Trials

* Narrow/wide `basic_ios::imbue`: baseline 0/325 and 0/238 bytes,
  respectively. The sole conflict remains mutable-char `_M_assign_dispatch`.
  The newly landed mutable append provider justified revisiting the older
  dependency finding. A declaration-only specialization still produces
  VC7.1 C1001 at `_string.h:629`. Direct dispatch from the cached-grouping
  helper, preserving the false-type temporary, produces the same ICE at
  the call site. Sources restored; scoped byte gate 11/11 passes.
* `MapCacheClearUnseenMaps_Rva0030469e.cpp`: baseline 0/322 bytes, sole
  conflict implicit `pair<const AsciiString, MapMetaData>` destructor versus
  MapUtil's first copy. An explicit destructor declaration neither before
  nor after the tree specialization suppresses its emitted copy. The early
  declaration requires moving the existing complete metadata definition
  first. An imported forceinline empty destructor specialization preserves
  all 7 rowed bodies but introduces an unresolved `__imp_` destructor and
  a non-retail erase-one copy. No gain; original source restored and 7/7
  byte gate passes. Needs destructor/provider or erase-one visibility repair.

## Read-only leads

* Constructor shard `Rva002C60E4Ctor_Rva002C60E4.cpp` remains 0/203 bytes.
  The unresolved base `v1` is a private-view defect. Base provider506B1B has
  a deleting destructor and two pure virtual slots. Retail table C004E4 has
  three entries: 2C65EB, 2C6779, 2C61AF. The shard instead emits two slots
  and an empty derived destructor. The middle native entry is already rowed
  as TacticalAI::rva002C6779; the deleting destructor calls pin-only6354.
  Reconcile the owner and destructor before editing this table. The helper
  506B2F is a nonvirtual flag-gated dispatch, not the missing virtual method.
* Current previews already link ArmySummaryCopy, narrow string substr and
  narrow money-put string. Those are inherited changes, not session gains.
* Hashable providers and several other top-ranked families have foreign
  claims. Formation's CameraMarker element-size issue, DX8Skin's folded
  vector table, count-map ctor, DamageFX erase identity, FlightDeck helper
  visibility, and wide-bool range identity retain recorded prerequisites.
  Do not repeat the existing failed suppressions merely from the rank list.
* `rehome_rows.py --limit 3` cannot run without the published census.log;
  this is an artifact failure, not an exhausted repair queue.

## Reference freshness / restart

BFME1 remains clean at verified pointer96c88c73. Official upstream fetched
to f5140c1cff6a58e16276fd6de6788186286953d4; the game-input diff has nine
source files and no header/layout change. Existing donor-linking evidence
was reviewed; no pointer advancement or successful freshness stamp is made.

The single old-input full baseline waited 11 minutes on the shared
`~/.cache/open-bfme-build.lock` before any function verification. Only this
seat's waiting process was terminated. The lock and its external holder were
untouched. Resume the old/new reference verification once that resource is
available; do not launch another census. The published index and 22,838
objects were successfully fetched. `check_csv.py` passes; scoped restored
sources pass 18/18 bodies in total. `progress.py origin/master` reports +0
authored C++ and +0 exact bytes.
