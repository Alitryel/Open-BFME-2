# Link-repair seat handoff

Starting tree: 366b5b63b5. Published census: c2c5ac8c27,
2026-10-18 11:36 UTC. No new production repair is claimed by this session.
Only the two new blocked-attempt records and these notes are retained.

## LightPointSystem

The 353 non-padding bytes in LightPointSystem.cpp are held out by the
unsigned-vector allocator's constructor and destructor copies. Declaration-only
lifetime specializations change both the 46-byte constructor and 297-byte
parser. Keeping their bodies visible with dllimport/forceinline preserves the
parser but inlines away the constructor's native vector-base call. Moving the
existing base-destructor declaration before instantiation fixes C2908 only;
it does not fix that byte mismatch. Both approaches were discarded.

Restored-source acceptance: three function rows and one data row pass the
ordinary byte gate. Scratch evidence is build/lightpoint-link-20261018.
Do not repeat without evidence for preserving the original inline decisions.

## Narrow-record family

See readme.md for the two rejected approaches. Restored-source acceptance:
five function rows pass. The stronger fold proof refuses the apparently exact
86-byte destructor because its DIR32 exception graph is not established as
the native owner's graph. Neither the isolated 370-byte provider preview nor
the 374-byte consumer preview is an accepted repair. All claims were released.

## Queue screening

The sole/name rankings and near-two-blocker units were checked against current
objects and existing attempt records. Current-provider checks clear the old
mesh-shader selection blocker after refreshing dx8renderer in an in-memory
index; MeshClassRender and MeshModelClassGetSortFlagsPass already link. Likewise
GeometryInfoCalcBoundingStuff, FlammableUpdateDtor, StlportTreeKeyRangeVector,
StrategicInGameUIArmyUnitSwapperValidation and UpgradeCenterFindUpgradeByKey
already pass their current legacy previews. These are existing upstream gains.
The stdio showmanyc provider is also already rowed in stlport_stdio_streambuf.

The beacon-map member-template helper has two existing failed declaration and
import trials; the RenderObj constructor/copy family has a recorded matrix
visibility dependency. Neither was retried. Other top candidates depend on
unrowed callees, shared cleanup/ABI reconciliation or documented codegen
blockers. class_views.py --blockers continues to rank broad class work;
repair_queue.py link uses the same old census and re-serves those blockers.
name_globals.py --dry-run keeps zero rewrites. No matching link-cycle data-back
artifact is available here; no data-back ranking or full link cycle was run.
rehome_rows.py --limit 100 checks 100 proposed source pairs and reports zero
movable units. check_csv.py passes 96,663 functions, 15,999 symbols and 961
data rows. progress.py origin/master reports zero byte-matched, authored-C++
and census-linked deltas. No closed-strict or self-strict link gain is claimed.

BFME1 remains at verified pointer 64d369b90170. Official master was fetched
(8619c4c56d73), but the already documented full-gate Rva0007DF07 vtable identity
conflict prevents an accepted freshness update. No success stamp, submodule
pointer, verifier or baseline was changed. Preserve the existing preparation
backup ref and unrelated stash identified in runner metadata.
