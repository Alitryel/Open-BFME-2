# Link seat follow-up, 2026-10-23

Inputs: BFME2 b8572a618d, published census b711de3634 (retail-truth-4),
BFME1 verified 96c88c73a5cd1a58fc2f8db691beea50acd996db. No source change
survived; no new linked, self-strict or closed-strict bytes are claimed.

## New bounded trial

`stlport_narrow_ios_imbue.cpp`: current scoped legacy preview 0/325 B;
sole blocking COMDAT is public `_M_assign_dispatch<char*>`. After the upstream
append repair, tested declaration-only specialization of that member template:
VC7.1 C1001 at `_string.h:629`. Calling dispatch directly from the local grouping
helper with a named default-initialized `__false_type` instead of the `assign`
wrapper also C1001 at the direct call. Two failed compiles; original source
restored, normal `build.sh` passes 10/10 rows, including all funclets and EH
handler. File and ten RVA claims released. The attempt log records the blocker.
A next attempt needs a different compiler-safe provider arrangement, not the
same declaration-only or wrapper-bypass trial.

## Current previews versus the stale rank

- ArmySummaryCopyBFME2 already links 803 B; FireLogicSystemObjects already links
  5,463 B; these are existing improvements, not gains from this seat.
- Rva00801CB0 now has only a Member2C vtable conflict. Do not equalize its bogus
  inherited `handle` slot: prior target evidence says that slot is a scalar
  deleting destructor (663430). Needs real class/provider reconciliation.
- LivingWorldRegionConstructor needs the newly rowed DynamicPortalLinkVector
  provider, absent from this census. A stale-provider refresh is not an authored
  repair and needs current provider evidence for a strict measurement.
- Assetmanager still has three blocking helper families: uint vector overflow,
  Rva001408C0Target tree node creation, Q1ReceiverHashPayload iterator skip.
- Partitionmanager still selects three wrong FlightDeckInfo helpers from the
  FlightDeckBehavior provider; known declaration-only trials change caller shape.
- SunRays setup needs the RefCountPtr-reference SegmentedLine Set_Texture ABI,
  while the current provider is spelled TextureClass-pointer, plus four undefined
  coordinate arrays. Requires supported provider and data ownership repair.
- W3DFontLibraryDestructor (116 B), W3DRopeDrawDtor (128 B), DebugDestructorThunk
  (99 B), each has a single private-vtable conflict. FontLibrary has prior
  incompatible complete-table evidence; Debug retail table is 46 slots, so
  copying its one-slot destructor view cannot prove the native table.
- ConstIntGettersAddr/ConstIntGetters5Addr still have hard-coded-address debt;
  their data providers need independent ownership repair.

## Lanes and infrastructure

`check_csv.py`: OK. Ran link_rank top30, near2 and near6; class_views --blockers;
repair_queue link; reviewed the current BFME1 linking leads and previous handoffs.
Live file/RVA claims were consulted. Several promising larger units are held
by other seats. `name_globals.py --dry-run`: zero edits.
`rehome_rows.py --limit 12` cannot run: published index exists but
`build/link_census/census.log` is missing. No matching cycle/data-back artifact
is available, so no data-back ranking was manufactured. The authenticated
cycle-artifact path needs unavailable gh (runner forbids running gh); direct
GitHub API fallback was blocked by proxy 403 Filtered. No census build, link
cycle, nightly or smoke runner was started.

Follow-up requires the runner to supply the matching census log/current artifact,
or an independently supported new class/helper repair. Existing follow-up notes
remain applicable; do not replay their unchanged trials.
