# Typed tree-iterator ownership repair, 2026-10-14

Shroud interpolation, taint interpolation and online-room player refresh no
longer emit a conflicting external STLport tree-base operator!= copy. A local
typed iterator overload compares the same node pointers. Every caller keeps
its existing inlined comparison. No ledger, pins, shared headers, baselines
or verifier rules change.

## Controlled result

Base checkout ec57ceff6690968c78b28adb07665b2145686486. The preserved runner
index measures 147cfae2cb at 2026-10-14 07:27; context.json records its hash.
Committed link_status.csv measures de7bb30890 and was used only to discover
leads. Both preview phases deep-copy the same runner index and replace only
the three explicit, strictly prepared current consumer objects in memory.

| Consumer | Retained identical COMDATs | Legacy findings | Legacy linked bytes |
| --- | ---: | ---: | ---: |
| W3DShroudInterpolate.cpp | 47 | 4 -> 3 | 0 -> 0 |
| W3DTaintInterpolate.cpp | 47 | 4 -> 3 | 0 -> 0 |
| ChatWindowsOnlineRoom.cpp | 55 | 4 -> 3 | 0 -> 0 |

The only external binding removed from each object is
`??9_Rb_tree_base_iterator@_STL@@QBE_NABU01@@Z`. All retained COMDAT bodies
and normalized relocation digests, all other nondebug sections and link
directives are identical. Each replacement is a static 12-byte helper with
no relocations; neither old nor new helper has a nondebug caller relocation.
The old external helper has 18 bytes. Object hashes and strict receipt
currency are recorded in object-proof.json. Before objects and dependency
receipts were saved after strict preparation in the ignored scratch folder.

Exactly the three tree-base comparison findings disappear; every other
finding is unchanged. Shroud and taint retain allocator<int> deallocation,
int allocator-proxy deallocation and wrong-selected vector<int> base
destruction. Online-room retains the allocator-proxy disagreement, a
nonretail PrereqUnitRec vector insert-overflow copy and the same selected
vector-base destructor. No authored-C++ growth, self-strict linked gain or
closed-strict linked gain is claimed. Strict receipts prove these three
objects current, not the closure of their dependencies. No full census or
maintainer-only verification runner was started.

## Acceptance

- Before and after strict preparation: 5/5 existing rows exact across three
  scoped, claimed sources; normal byte/string/float/import verification passes.
- Explicit ./build.sh gate: 5/5, four float literals, two named imports.
- EH verifier: 3/3 exact; no baseline use or missing objects.
- Data enforcement: zero findings. Converged data: eight addresses, zero
  second names or unjudged rows.
- Class gate, declared-definition check and new-variant check pass.
- Placement resweep: zero new bodies or pins.
- Prescribed local link_check preview returns 1 for the remaining blockers;
  the controlled paired comparison proves findings 12 -> 9 with no other change.
- check_csv and git diff --check pass; normal commit/push hooks are required.

The object and paired-link comparison scripts are preserved with the evidence.
They expect saved before objects in build/tree-iterator-link-20261014 and the
same runner index hash; raw objects and preparation backups are not published.

## Reference review and limits

BFME1 d3f9000fe08615a100e844adfff57fa4a39cd615 (TileData constructor
suppression) and de59a7e9f891b3ed2d4221d151ca881f4b75a583 (Apt isUndefined
unification) support removing incidental nonretail competing helpers while
preserving verified callers. Those specific dependencies do not apply here.
The typed node comparison follows existing BFME2 TerrainLogicWaypointLookups
and BuddyDefs overloads. Target object and retail gates establish preservation;
donor linkage alone supplies no target-byte proof.

The clean verified BFME1 gitlink a7c38d3b2597121f178ab5190b3062478823257d
is retained after an official-master fetch to cd81b435cca7677ebcdb4ed2ae45995a536c3512.
The outstanding pointer update needs comparative full-gate work with thousands
of stale TUs (2806 remained after the previous 21-minute baseline attempt).
This bounded repair does not repeat that unchanged blocker or mark freshness
successful. Downloading the published census index failed with a network
403 Filtered; the existing runner-built index remains available and unchanged.
