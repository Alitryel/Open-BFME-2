# RayEffect shared-view prerequisite — 2026-10-26, codex4

## Scope and result

Allocated destination: `Code/GameEngine/Source/GameClient/System/RayEffect.cpp`.
The runner allocation and upstream planner were checked before taking the
destination and constructor/init donor claims. No merge was applied.

The seed's BFME 1 `coord.h`/`ray_effect.h` includes collided with the
constructor/init donor's canonical BFME 2 Coord3D and SubsystemInterface
includes. Before repair, `tu_skeleton.py --merge TU --dry-run` accepted no
donors, reporting Coord3D and StringBase redefinitions. Both sources now use
one TU-local `RayEffectView.h`, retaining the constructor/init donor's existing
class definitions, layout, virtual functions and inline bodies. The seed's
three existing nonvirtual methods are declared there. No guessed destructor
recovery, additional virtual slot or donor path attribution is implied.

The post-repair dry-run accepts both sources: six existing matched rows,
325 retail bytes. This is a demonstrated composition unblock for Luna, not a
confirmed subsequent merge. Recovered C++ bytes: zero. File reduction: zero.
Identity debt retired: zero. Existing global and row ownership is unchanged.

## Verification

- `./build.sh Code/GameEngine/Source/GameClient/System/RayEffect.cpp
  Code/GameEngine/Source/GameClient/System/RayEffectSystemInit.cpp`: before
  and after, all six rows exact and one data item verified.
- `find_declared_unmatched.py` on both sources passes; two pre-existing
  RayEffectData empty constructor/destructor markers moved with their bodies
  to the private header. `hatch_counters.py --update` transfers those two
  occurrence keys without changing any hatch total; no admission was used.
- `name_lane.py consolidate --under Code/GameEngine/Source/GameClient/System/`
  and its snapshot currency check pass. Its routing/original-path evidence
  was reviewed; only the upstream dry-run, not the planner, establishes the
  accepted composition.
- `allowed_symbols.py --source`, scoped `data_check.py`, converged data check
  and EH verification: zero wrong owners, zero data findings/second names,
  one EH row exact and none missing or inexact.
- `build/codex4-ray/proof.py`, using the supported object readers and row
  binding analysis, compares saved pre-edit objects to the official post-edit
  build and dry-run composed object `build/tu_skeleton/b124b59fda74eb62.obj`.
  All external code definitions, digests, sizes, exclusivity, selected COMDATs,
  data definitions/relocations and unresolved references are unchanged.
  Composition equals their union: ten code definitions, two external data
  definitions and nine unresolved references. All six row DIR32 data-binding
  sets agree before, after and composed. No changed provider binding remains
  to justify through a maintainer-only link cycle.

Local receipts: `build/codex4-ray-{plan,trial-before,trial-after,proof,identity,
data,converged,eh}.txt`, `build/codex4-ray-build-{before,after}.txt` and saved
pre-edit sources/objects under `build/codex4-ray/`.

## Batch compatibility audit and remaining prerequisites

The complete unpublished batch (inherited EyeTower/Energy prerequisites and
this repair) contains no source deletion, rename or row repoint. Active tools,
hooks, workflows, includes, build inputs and registries retain their paths.
The new private headers have only the intended five inherited consumers plus
these two RayEffect consumers. No historical EA path string was changed.
The pending-path and include receipts are
`build/codex4-ray-pending-paths.txt` and
`build/codex4-ray-header-consumers.txt`. Existing identity/data debt keys and
header queues were checked; none belongs to these RayEffect sources. The
scoped Microsoft-header queue refresh preserves its existing clean result.

The opaque `Code/GameEngine/Source/Common/Rva002CEE1BDtor.cpp` remains
unmodified and rejected by the dry-run (its private AsciiString/StringBase
view collides). It needs its own evidence-backed reconciliation; this change
does not claim a recovered destructor or its layout. Header adoption into the
retail public header is also outside this private-view prerequisite.

Other allocated probes this pass were left unchanged: FloatUpdate and
LocomotorSetUpgrade require hierarchy/member reconciliation; INIWater still
has allocator/vector conflicts and an Assign byte mismatch;
ProcessAnimateWindow's remaining slide donors have private-field/canonical
coordinate conflicts. ModelConditionUpgrade's prior provider repair is
already present. Existing EyeTower ctor/Xfer STL blockers and TerrainRoads
bridge composition blocker retain their earlier handoffs. No new claims were
taken on those unchanged blockers.

## Publication and census-audit handoff

Published prerequisite batch: EyeTower `a241937940`, Energy `7aba500dff`,
TerrainRoads blocked evidence `67d2cc6ea3`, recovery checks `62c0424090` and
RayEffect `eb9580bfc9`. The push gate verified 50/50 rows across eight affected
sources, five exact EH records, two data rows, 11 literals, five empty-string
references and 15 float literals. All 35 inherited/new prerequisite claims
were released after the confirmed push.

The outgoing `link_batch_audit.py` reported an **inconclusive** baseline:
index `763dc8759f`, outgoing base `4d0d99ee1f3e6e3e4b7c26e2d616f829cedc33cc`;
eight source objects lacked current receipts, first `Energy.cpp`. Thus the
independent standalone/composed provider comparisons above remain the scoped
acceptance evidence, while census selection and any lost linked bytes await
the next current census/index. No census gain or cleared LINK-017 is claimed.
`docs/linking_obstacles.md` already records this stale-index obstacle as
LINK-017; its file claim was held by another worker, so this is the scoped
handoff for that register's owner. Include Energy, the three EyeTower consumers,
the two RayEffect sources and the dependent Eva unit in the next batch audit.

Final `python3 tools/progress.py origin/master`: BYTE-MATCHED 7,978,500 (100%),
LINKING 7,370,962 (98.11%), LINKED 7,614,012 (98.75%), all deltas zero. The
linking figures are the 2026-10-26 08:28 census at `47e030bafc`, not a new
measurement of these prerequisites.

Recovery check (2026-10-26, codex4): clean tracked working tree, upstream
pull already current, and `python3 tools/check_csv.py` passed (98,273 rows).
Only this evidence commit remained unpublished; no source paths or bindings
changed in the recovery range. The prior scoped verification remains the
acceptance evidence; no additional census result is asserted.
