# Link audit and classic-locale provider handoff, 2026-10-23

Wind-down ended this read-only link-repair audit. No source edits, claims,
new recovery or new linked bytes are retained. BFME2 HEAD was 88983ceb42;
published census 456ce161c5 (2026-10-23 06:28), fetched with link_check.
All byte counts below are scoped legacy predictions, not strict closure or
an executable link. Do not credit inherited fixes as this session's work.

## Concrete next task: the classic locale handle

Current link_check of stlport_locale.cpp is 0/182 B, with its sole unresolved
name `_STL::_Stl_loc_classic_locale`. Its rowed classic() at RVA 71B0 returns
VA DA6214. The independently inventoried datum there is four bytes, containing
VA DDE118 in the retail image. This is the existing 24-byte `_S_classic_locale`
aligned buffer owned by stlport_classic_locale.cpp, not a null handle or a new
implementation object. That provider already links 1369 B unchanged.

The other native reference to DA6214 is RVA 7B6890: load the handle's implementation
pointer, then tail-call virtual slot 2. Its current neutral singleton view calls
the same address g_pRva007B6890 and is separately unresolved (11 B). The code
shape agrees with the locale implementation's _M_decr slot. Reconcile it to the
real global and a narrow implementation view; do not define another datum.

No definition was tried before wind-down. Resolve how to statically initialize
the four-byte handle to the existing buffer while preserving its storage owner,
class ABI and lifecycle. The buffer is TU-static; adding a second external
buffer would be wrong. The full vendor locale class declares constructors and
a destructor, so blindly defining a default locale adds initialization rather
than reproducing the retail pointer. The recovered locale.cpp class has the
same pointer member and likewise has a nontrivial default constructor. Preserve
the retail initialized value and verify its relocation with data_rows.

Possible cohort: stlport_locale.cpp, stlport_classic_locale.cpp and
Common/Rva007B6890SingletonFwd.cpp. Baseline logs are ignored build artifacts:
build/link-seat-probe5.log and build/link-seat-locale-providers.log. No claims
were held on these files in the checked snapshot; recheck before work.

## Other newly inspected prerequisites

W3DShaderManager's Rva00066A9ABody.cpp remains 0/371 B: two missing roots at
DB43A4 and DB43AC. Retail roots contain one shader list and nine filter lists,
respectively; this differs from the donor's seven/four. Nested list entries:

* DB439C: DB5A34, null (shader root DB43A4).
* DB4348: DB5BD4, null.
* DB4364: DB5B54, DB5B5C, null.
* DB4350: DEC1F0, null.
* DB4394: DB5A64, null.
* DB4370: DEC140, DEC174, null.
* DB437C: DEC0E0, null.
* DB4358: DEC1CC, DEC1DC, null.
* DB4384: DEC080, null.
* DB438C: DEC018, null.

Filter root DB43AC orders those nine lists as listed. Existing DEC* storage
must be reused. DB5A34 currently has a char provider, DB5A64 is the existing
screenCrossFadeFilter, DB5B54/5C are the unresolved BW filter objects, and
DB5BD4 has only a getter's incomplete object view. Defining roots alone would
leave object and vtable prerequisites. Preserve these identities rather than
copying the donor lists or adding duplicate storage.

MultiplayerSettingsCtor remains 0/159 B. Besides the nonvirtual base-dtor
spelling, it needs the table at C191B8. Retail's first entry is 781277, currently
rowed as a QAE scalar deleting destructor; the complete destructor is also
rowed QAE. A canonical virtual class would change those names. Reconcile class
identity and the actual table before attempting a base-only edit for zero gain.

Rva003FD4DA's private views disagree on its seven-slot interface. Native table
BFE1B0 is also owned by the BfmeRectVNH view; its slot-2 getter names
DelayedWorldTextEventModule. This needs class-identity reconciliation rather
than replacing the pure entries by arbitrary declarations. No source trial.

## Checked lanes and unchanged blockers

link_rank --top 100, --near 2, class_views --blockers and repair_queue link
were inspected. name_globals --dry-run found zero edits. rehome_rows --limit 3
found no successful placement in the first twelve tested candidates; its
read-only scan was interrupted, so that lane is not exhausted. No matching
data-back artifact was available; no ranking was manufactured.

Current-object probes establish inherited linking in the three particle-emitter
units (1713 B), HordeContainRva00475F61 (1671 B), Win32GameEngineFactories
(528 B), and Snapshot-table consumers Rva003F2D03Dtor/Rva001DF057Dtor/
Rva002DAB18Finish (1476 B). No new repair is needed in these units.

Still blocked: Eva's documented compiler summaries, wrong selected narrow
string/hash copies, AIStatCollector's hash-map constructor, CreateAHero class
identity, planning-phase views, unconverted queueSupplyTruck, Version's patched
provider, and the VP6 cohort's missing provider in this census. Existing banks
and tracked evidence were read; unchanged failed trials were not repeated.
The VP6 clean-room restrictions were observed. No full census, link cycle,
nightly or boot runner was started.

BFME1 was clean at committed 138757e9. Tracked paired-gate evidence dated
today establishes its freshness despite the stale ignored timestamp. Fetched
upstream HEAD was 38cba658; the verified pointer was retained. Reviewed donor
linking commits c20e733a1, 54493f975 and 0a12ba59d: inline StringBase wrappers,
destructors and /MD changes. No supported new BFME2 transfer was established.
