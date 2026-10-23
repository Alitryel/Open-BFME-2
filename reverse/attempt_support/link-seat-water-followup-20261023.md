# Water link repair follow-up, 2026-10-23

Seat yasinschroeder-codex3, gpt-6.1-sol, HEAD f231cfc352. The six-unit
water-interface repair is complete: paired current-object legacy preview
0 -> 1692 B, 60/60 byte rows and one data row verified, six reusable strict
receipts. Details and the separate shadow identity diagnostic are in
`water-interface-link-20261023.md`. No closed-strict closure gain is claimed.

Read-only follow-up evidence (no source experiments or new claims):

- Rva005746AF's destructor at 0x005746D2 remains a vtable conflict. Retail
  C6E3B0 contains 574B68,57473A,5DAA6C,5CB9FF,5CB9FF,5CB9FF,3B810;
  the constructor/destructor views instead make slots 2..5 pure. Derived
  C6E3CC contains 574B84,57473A,5DAA6C,574365,5CB9FF,5CB9FF,5747F9,
  while Rva005747DACtor declares only a destructor. `vtable_owner.py`
  confirms both consecutive tables. Matching two incomplete private views
  would not establish the native table: real slot signatures and folded
  providers must be reconciled first. Existing 104-byte destructor remains
  unchanged; no new alias or pin was attempted.
- Rva001E86D0.cpp remains 0/105 B linked because its Rva001E7087 table
  differs. Its own retained target evidence describes native BDE950 as
  deleting destructor, empty no-argument callback, LocomotorSet name getter,
  and a 413-byte worker. The private Snapshot-derived view does not prove
  those signatures or the inheritance. Do not fix this by copying another
  guessed purecall table. Allocator diagnostics in this preview are explicitly
  unreferenced and are not blockers under retail-truth-2.
- Rva00510CC3Constructor plus its current destructor already link 414 B;
  the constructor's 335 B is inherited progress, not a repair here.
  FormationTemplate still needs its correctly typed 24-byte container
  teardown; previous isolation trial 82478 remains applicable. The region
  constructor's Gen_uwm cleanup now has a provider upstream (82449), so check
  that provider together rather than rediscovering or crediting its repair.
- Current previews reconfirm zero gain for DebugDestructorThunk (99 B),
  Rva00340BDCDtor (103 B), EvacuateDamagePoolKey (161 B),
  Rva00534A2AMapSubscript (150 B), vector_class_vector3_ctor (160 B).
  Existing records 77801,77799,81952,82473,81405 respectively describe the
  class/provider/compiler prerequisites. Debug's first kept 35-slot donor
  table is itself not proof of retail: native slot order includes deleting
  destructor 39920 after stream callbacks, unlike that donor view.

Selection/acceptance audit: link_rank --top30 and --near2, class_views
--blockers, and repair_queue link were revisited against the published
0393df10e2 census index. Larger ranked items were already repaired upstream,
foreign-claimed, or have the unchanged prerequisites recorded in earlier
link-seat handoffs (notably money-put range construction, mutable string
assignment, CreateAHeroData identity and DynamicVectorClass wrappers).
No further bounded repair was identified for this seat.

`name_globals.py --dry-run` proposed zero edits. The rehome_rows read-only
probe was stopped without applying anything: census.log is dated October 12,
whereas the index is from October 23, so its candidates cannot support a new
gain claim. No matching data-back measurement artifact was available; no
ranking was manufactured. The verified BFME1 pointer and reviewed donor
evidence are unchanged from the prior handoffs; the previously diagnosed
full-gate baseline failures still prevent a verified donor pointer update.

`progress.py origin/master` reports +0 authored C++ and +0 census-linked B,
as expected for a source-only repair with no new census. Its frozen count
does not replace the paired current-object measurement above. No census,
full link cycle, nightly, boot runner, or verifier/baseline modification ran.
All owned claims are released at handoff; unrelated untracked files remain.
