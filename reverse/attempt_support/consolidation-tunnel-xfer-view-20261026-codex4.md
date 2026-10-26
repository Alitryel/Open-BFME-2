# TunnelContain Xfer composition prerequisite, 2026-10-26

Allocated destination: `Code/GameEngine/Source/GameLogic/Object/Contain/TunnelContain.cpp`
(family A, codex4 shard 1/2; runner check-tu accepted). This follows the
list-getter prerequisite in 0b9e0be64e. No merge is applied: compatible donors
are left for Luna. The current Contain planner's original-path packets,
alternatives, include/compiler prerequisites and unresolved placements were
reviewed; the committed TU map is untouched.

## Repair and evidence

The preceding normal merge trial accepted only the seed and primary getter:
12 rows / 645 retail bytes. Its next concrete refusal was Xfer: composition
hoisted BfmeXfer.h ahead of its required operand declarations, and its private
single-vptr/padded TunnelContain layout conflicted with the seed's multiple
inheritance hierarchy.

TunnelContainXferPrefix.h keeps the exact existing operand forward declarations
with BfmeXfer.h. Xfer now includes the same TunnelContainView.h as the seed and
getter. Primary slot 3 and the protected base/derived Xfer declarations retain
the existing ledger names. The shared view's two bytes at +0x9E4/+0x9E5 are
bools, as already required by the matched Xfer overload calls; seed writes are
still byte writes of zero or one. Existing placeholder member names remain;
this does not assert an external donor's names or layout as BFME 2 source.
The seed's existing multiple inheritance subobjects retain all offsets. The
constructor, mixed/protected donors and other receiver views are untouched.

## Verified standalone checks

- `./build.sh` on TunnelContain.cpp, TunnelContainContainedList.cpp and
  TunnelContainXfer.cpp: 13/13 matched, string/float/import checks pass.
- `find_declared_unmatched.py` on all three: all defined functions matched.
  `class_gate.py` accepts the changed view, Xfer source and prefix header.
- Before/after snapshots using allowed_symbols._object_defs and
  data_check.object_facts are identical for all 13 rows: seed 17 definitions
  (six selectable COMDATs), getter two definitions (one COMDAT), Xfer one
  definition, every undefined symbol and both data references unchanged.
  No unread object; Xfer still has exactly two undefined external names.
- `allowed_symbols.py --source` on all three: 35 owner references, zero wrong
  bindings. The before/after scoped audit reports agree.
- `data_check.py --converged`: three sources, ten addresses, zero second names,
  zero unjudged rows. EH: zero EH-bearing rows or missing objects.
- `link_check.py --new-variants` on all three exits zero. It uses the fetched
  published census index; no census or ownership gain is claimed.

The first standalone Xfer trial exposed its missing STLport compile marker:
ContainmentListView uses the existing _STL namespace. Xfer now retains that
marker and the seed's _STLP_USE_STATIC_LIB setting. Its .drectve consequently
names stlport_vc7_static.lib alongside the existing CRT default libraries;
current census/link-cycle commands use /NODEFAULTLIB. No linker was run.
An early data check while the build was incomplete reported one stale object;
the completed-build rerun above has zero unjudged rows. The planner refused
its first scan after the flag correction changed Code during that scan; the
final fresh scan and currency check pass. No stale snapshot authorizes work.

Local receipts: build/codex4-tunnel-xfer-build.txt, -defs-before.json,
-defs-after.json, -bindings-after.txt, -data.txt, -eh.txt, -link-check.txt,
-planner-final.txt and -currency-final.txt.

## Composition and publication audit

The final normal `tu_skeleton.py --merge <destination> --dry-run` exits zero
and accepts exactly the seed, Xfer and primary getter: **13 rows / 716 retail
bytes**, compared with 12 / 645 after the first repair and no accepted group
before either repair. This demonstrates one more compatible donor and 71 more
retail bytes in the accepted group; it is not newly recovered C++.

The composed object `build/tu_skeleton/f4ceef3a9f7a8107.obj` has all nineteen
definitions identical to the donor union, including fingerprints, sizes and
COMDAT selection. Its twenty-seven undefined symbols equal that union after
internal resolution. Both data references retain the same real globals and
addresses. No changed provider body or consumer binding is hidden by the
composition. Receipts: build/codex4-tunnel-xfer-trial.txt and
build/codex4-tunnel-xfer-composition-evidence.txt. The normal trial still
reports the constructor/receiver prerequisites and mixed/protected exclusions
listed below.

Audited the complete pending batch (origin/master c85d92855d23928fc5fbabcb6de858f966e259be,
outgoing 0b9e0be64e plus this staged prerequisite) before commit/publish.
The reverse upstream diff includes newer unrelated work; the merge-base-to-HEAD
and outgoing log isolate our actual batch. No source paths move or disappear.
No register, ledger, routing map, fold proof, tool, hook, workflow or build
registry needs repointing. Combined basename/path searches across active tools,
hooks, workflows, includes, build inputs, doxygen and protected registers find
only the three intended shared-header consumers (all built together), the
prefix's Xfer include, and retained historical comments. Code/data/header/
MS-header/gate/hatch/duplicate registers contain no key for an affected source.
No debt key is dropped or retired. Historical EA paths are retained.
Local audit receipt: build/codex4-tunnel-xfer-path-consumers.txt.

## Wider identity warning: handoff, not a retirement

The first prerequisite's hook reported divergent inline
`?getBodyModule@Object@@QBEPAVBodyModuleInterface@@XZ`. Scoped before/after
object snapshots prove the repair did not change that definition. A read-only
allowed_symbols inventory finds two existing seven-byte COMDAT bodies:
`489e997541f4` loads +0x254, including the selected ActiveBody.cpp provider
and TunnelContain.cpp; `64d450fcd07b` loads +0x194, including FlightDeckBehavior,
ParkingPlaceBehavior, WorkerAIUpdate, Locomotor, OpenContain, GarrisonContain,
AssaultTransportAIUpdate and PhysicsUpdate. There are no undefined external
referrers to this symbol in that inventory. No identity register key exists
for this symbol or the changed sources. This wider private-layout discrepancy
needs its owners' scoped evidence and claims; removing TunnelContain's correct
unused copy would merely hide the local warning. No debt is retired here.
Local receipt: build/codex4-body-provider-before.txt.

## Remaining work and claims

The constructor still conflicts with the native MI hierarchy; other rejected
receivers lack removeFromContain, getAI/template, rider/list/delete/scatter
members. Three mixed and three protected donors remain untouched. Earlier
BridgeScaffoldBehavior and ShipSlowDeathBehavior prerequisites were already
published; their unchanged constructor/private-view blockers were inspected
without new claims or repeated builds. RiderChangeContain's planner still
shows native Xfer/AsciiString/DamageInfo versus full-reference header conflicts;
no edit or trial was started there.

Retain file claims for TunnelContain.cpp, TunnelContainContainedList.cpp,
TunnelContainView.h, TunnelContainXfer.cpp and TunnelContainXferPrefix.h until
publication is confirmed; retain the twelve RVAs listed in the first handoff.
If the publisher holds the batch, the next session must release the file claims
and settle landed RVAs after landing.

File reduction: zero. Identity debt retired: zero. Recovered C++ bytes: zero.
The C++ TU count is unchanged; two private headers have been added across the
batch. A dry-run acceptance is a prerequisite unblock, not a Luna landing,
census increase or ownership receipt.
