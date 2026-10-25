# Linking target checklist

Recorded 2026-10-25 from the linking handoff. The census snapshot is
`ef9c691284`, **2026-10-25 18:23 UTC**, recorded in
[link_status.csv](../reverse/link_status.csv) and
[link_census_history.csv](../reverse/link_census_history.csv).
All 50 named units and their blocker categories were checked against the
committed status. Bytes and difficulty/attempt groupings preserve the handoff's
reported values; they describe leads rather than verified current failures.

Before selecting a target, read the [obstacle register](linking_obstacles.md),
resolve its current source after renames/consolidation, check claims and prior
attempts, and verify the blocker against current inputs. When working a row,
update its follow-up with the date, revision, result, evidence link and remaining
dependency. Record cleared scope and census confirmation separately; retain the
snapshot bytes and history. Add newly encountered causes to the obstacle register.

## One blocker: fresh candidates

The handoff found no earlier served-queue entry for these 16 units. Follow-up:
**Open / current-input verification pending** for each row.

| Unit | Matched bytes | Census blocker | Follow-up |
| --- | ---: | --- | --- |
| `urlBuilder.cpp` | 942 | COMDAT losers | Open |
| `stlport_narrow_stringbuf_overflow_setbuf.cpp` | 567 | COMDAT losers | Open |
| `stlport_pair_asciistring_twins.cpp` | 395 | Wrong selected | Open |
| `MeshModelReadVertexMaterials.cpp` | 271 | Wrong selected | Open |
| `stlport_narrow_string_erase_count.cpp` | 130 | Unresolved | Open |
| `ElementStrideWalks.cpp` | 90 | Unresolved | Open |
| `VectorRangeEraseRva003F6975.cpp` | 80 | Unresolved | Open |
| `Rva00541913CopyCtor.cpp` | 76 | Wrong selected | Open |
| `StlportNarrowAppendCStr.cpp` | 58 | COMDAT losers | Open |
| `GrantUpgradeCreate.cpp` | 42 | Unresolved | Open |
| `PartitionData_friendUpdateCellsTouched.cpp` | 37 | Wrong selected | Open |
| `StlSweepW5Rva0042830DAssignTwin.cpp` | 33 | Unresolved | Open |
| `StlportVectorClearRva00475F2A.cpp` | 30 | Unresolved | Open |
| `Weapon_getName_Thunk.cpp` | 26 | Wrong selected | Open |
| `Rva000FDCD7Get.cpp` | 26 | Unresolved | Open |
| `ConstIntGetters2Addr.cpp` | 6 | Addresses | Open |
| **Total: 16 units** | **2,809** | | |

## One blocker: previously worked

The handoff reports earlier solved, converted or landed work for these 16 units.
Follow-up: **Recheck the existing repair and its prerequisites** before retrying.

| Unit | Matched bytes | Census blocker | Follow-up |
| --- | ---: | --- | --- |
| `MeshLoadContextAddLegacyMaterial.cpp` | 2,828 | Wrong selected | Recheck repair |
| `stlport_float_format.cpp` | 2,620 | COMDAT losers | Recheck repair |
| `MaterialCollectorDestructor.cpp` | 1,686 | Wrong selected | Recheck repair |
| `MaterialCollectorCollectMaterials.cpp` | 1,506 | Wrong selected | Recheck repair |
| `PositionStartSpots.cpp` | 994 | Wrong selected | See LINK-006 map-metadata subset |
| `SkirmishMapStartSpots.cpp` | 703 | Wrong selected | See LINK-006 map-metadata subset |
| `stlport_narrow_string_substring_ctor.cpp` | 363 | Unresolved | Recheck repair |
| `meshmdlio.cpp` | 352 | Wrong selected | Recheck repair |
| `GameInfoSetMapSize.cpp` | 343 | Wrong selected | See LINK-006 map-metadata subset |
| `stlport_narrow_string_substr.cpp` | 277 | Unresolved | Recheck repair |
| `Rva001ECF66Finish.cpp` | 96 | Unresolved | Recheck repair |
| `RtcStack.cpp` | 90 | Duplicates | Recheck repair |
| `w3d_dep.cpp` | 47 | Unresolved | Recheck repair |
| `Rva003BBAF0Ctor_Rva003FD199.cpp` | 44 | Unresolved | LINK-011: preview cleared; census pending |
| `SpecialPowerModule.cpp` | 36 | Unresolved | Recheck repair |
| `GapBodiesSeat10O1_Rva00525E00.cpp` | 22 | Wrong selected | Recheck repair |
| **Total: 16 units** | **12,007** | | |

## One blocker: harder obstacles

Each row retains the handoff's investigation lead alongside the census category.

| Unit | Matched bytes | Census blocker | Follow-up / prerequisite |
| --- | ---: | --- | --- |
| `Rva0056616BCopyDeferred.cpp` | 481 | Wrong selected | Missing destructors and selected copy |
| `stlport_narrow_ostringstream_dtor.cpp` | 429 | COMDAT losers | STL conflicts; compiler C1001 |
| `vector_class_vector3_ctor.cpp` | 218 | Wrong selected | Vtable/destructor mismatch |
| `Rva001F9524Concat.cpp` | 185 | COMDAT losers | Symbol identity debt |
| `stlport_narrow_string_copy.cpp` | 152 | Unresolved | Missing callee address |
| `DebugDestructorThunk.cpp` | 113 | COMDAT losers | Vtable slot-count mismatch |
| `stlport_pod28_vector_resize_value.cpp` | 73 | Wrong selected | Extra emitted COMDAT |
| `DebugStatisticsTextureShutdown.cpp` | 10 | Unresolved | Destructor inlining |
| **Total: 8 units** | **1,661** | | |

## Two blockers: largest identified candidates

| Unit | Matched bytes | Census blockers | Follow-up / prerequisite |
| --- | ---: | --- | --- |
| `PointGroupClassRva0017A890.cpp` | 12,000 | COMDAT + wrong selected | Recheck shared VertexLoc ownership evidence |
| `pointgr.cpp` | 10,695 | COMDAT + wrong selected | Coordinate with the VertexLoc owner |
| `MmxIDct.asm` | 7,686 | Two address issues | Recheck LINK-007 storage repairs |
| `DX8SkinClearVisibleList.cpp` | 1,630 | COMDAT + wrong selected | Current-provider verification pending |
| `StlportVectorDtorDeferred.cpp` | 461 | Two unresolved | Current-provider verification pending |
| `Rva00066A9ABody.cpp` | 371 | Two unresolved | Two global providers |
| `Rva007B7280Siblings.cpp` | 354 | COMDAT + wrong selected | Current-provider verification pending |
| `LargeGroupAudioKeyMapBfmeAddKey.cpp` | 324 | Two unresolved | Global records and vector resize |
| `FXListStoreCtor.cpp` | 280 | COMDAT + wrong selected | Current-provider verification pending |
| `PolygonTriggerCtor.cpp` | 186 | Unresolved + COMDAT | LINK-011 preview cleared 157 authored bytes; reconcile scope |
| **Total: 10 units** | **33,987** | | |

Point-group ownership evidence:
[VertexLoc handoff](../reverse/attempt_support/vertexloc-ownership-20261024/readme.md).
LINK-011 records 157 authored bytes for PolygonTriggerCtor; this checklist retains
the handoff's 186 matched bytes. Compare the measured scopes when updating it.

## Broader workstreams

These scopes can overlap the targets above. Their verification and remaining
prerequisites are maintained in the [obstacle register](linking_obstacles.md).

| Workstream | Reported bytes | Latest recorded scope/status |
| --- | ---: | --- |
| LINK-001: WeightInfo graphics units | 45,204 | 30 units cleared in ordinary preview; census pending |
| LINK-007: VP6 storage | 17,413 | Landed; fixed-comparison closed-strict gain |
| LINK-007: filter adjacency | 2,369 | Landed; fixed-comparison closed-strict gain |
| LINK-007: scaler coefficients | 1,739 | Landed; fixed-comparison closed-strict gain |
| LINK-009: split-identity destructors | 661 | Trial proven; identity merge or admission decision pending |
| LINK-011: four units | 297 | Ordinary preview cleared; census pending |

The INI repair [0c7ebc35a7](https://github.com/Open-BFME/Open-BFME-2/commit/0c7ebc35a7)
is tracked under LINK-004: 2,989 authored bytes cleared in a bounded ownership
diagnostic, with census confirmation pending. It sits outside the 50-unit list.

## Snapshot totals

| Category | Units | Reported matched bytes |
| --- | ---: | ---: |
| Fresh one-blocker candidates | 16 | 2,809 |
| Previously worked one-blocker candidates | 16 | 12,007 |
| Harder one-blocker candidates | 8 | 1,661 |
| Listed two-blocker candidates | 10 | 33,987 |
| **Explicitly listed** | **50** | **50,464** |

The committed census contains **85 units with one or two blockers** (40 with
one, 45 with two). The handoff reports **55,142 matched bytes** for that wider
set, leaving 35 units / 4,678 reported bytes outside this checklist.
The three largest listed targets total **30,381 bytes**, about **60.2%** of the
listed bytes. Size ranks investigation opportunities; current evidence and
shared-provider dependencies determine the next repair.
