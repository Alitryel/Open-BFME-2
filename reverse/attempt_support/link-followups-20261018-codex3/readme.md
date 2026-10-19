Link-repair follow-ups at 4f19d60487, 2026-10-18

All predictions below use the published c2c5ac8c27 census index (11:36 UTC)
and current objects. They are legacy scoped predictions, not closed-strict
or a new census. The separate Snapshot repair predicts +48 B; none of the
following rejected trials is counted as progress. All source trials were
restored and their claims released.

AutoResolve: LivingWorldAutoResolveBattle.cpp, 2,441 unique matched bytes

Paired before-check included StlportAutoResolveUnitRange.cpp (373 B) and
StlportVectorInsertOverflowFamily.cpp (9,375 B). All three remain unlinked.
The home unit emits a duplicate __destroy_aux<Element*> plus nonretail
_M_range_insert and _M_insert_overflow copies. Whole-byte providers now
exist at 4F72ED, 4F7EE9 and 4F823B, motivating a new declaration-only trial.
The provider units have independent blockers; no gain was inferred from
their presence alone. The allocator fold at 211E58 was held by another
seat and its code and ledger entry were untouched.

Trial 1 used typedef UnitVector for member specializations. MSVC 7.1
rejected the member-template spelling with C2768/C2244. Trial 2 spelled
vector<Element, allocator<Element> > and template<> template<> explicitly;
the compiler crashed with C1001 at vendor/stlport/stl/_vector.h:384,
P2/main.c:148. Stop here rather than repeat compiler-binding guesses.
Scratch: build/seat-autoresolve-{before,byte1,byte2}.txt and
build/seat-autoresolve-specialization-ice.cpp. A future attempt needs a
compiler-safe binding and must preserve every parent and EH row.

InstantDeathBehaviorModuleDataDtor.cpp, 105 unique matched bytes

Before: duplicate and first-copy conflict on inline DestroyDieModuleData
destructor. dllimport plus forceinline preserves both matched code rows,
but its EH cleanup still references __imp_??1DestroyDieModuleData@@UAE@XZ.
The scoped prediction therefore remains 0 -> 0 B. No import/pin workaround
was retained. Reconcile the real base destructor and EH provider instead.
Scratch: build/seat-instantdeath-{before,byte1,after1}.txt.

After restoring both sources, build.sh verifies 40/40 matched rows,
including parent-owned label rebinding, literals, floats and imports.

Fallback review

* link_rank --top 30 / --near 2 and repair_queue.py link still prioritize
  missing real callees, known compiler/layout blockers and stale providers.
* class_views --blockers prioritizes MilesAudioManager, DX8Wrapper,
  AptActionInterpreter and Pathfinder; no unsupported private layout was
  substituted for a canonical class repair.
* name_globals.py --dry-run finds zero files and zero edits.
* Current Snapshot cohort: 20/29 units link, 2,685 -> 2,733 B, exactly the
  separately verified +48 B repair. Other consumers have independent
  unresolved bodies, class/vtable conflicts or the recorded concrete-base
  Snapshot blocker.
* The address-only ranking includes the already recorded false positive
  for FadeInTextRender's RGB immediate DCF0FA. No source workaround.
* Rehome candidate 4F6318 matches its AutoResolve home, but that home still
  cannot link. View::getPosition at 8BB27 matches View.cpp; both current
  units already link (819 -> 819 B), so moving it is not credited repair.
* BFME1 pointer/freshness and reviewed donor repairs retain the blockers
  recorded in bfme1-freshness-20261018 and the Snapshot repair evidence.
  No stale donor results were credited.
