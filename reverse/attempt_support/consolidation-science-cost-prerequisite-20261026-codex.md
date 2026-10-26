# Science purchase-cost GameLogic prerequisite — 2026-10-26 codex

Allocated family A shard 0/2 target:
`Code/GameEngine/Source/Common/RTS/Science.cpp`.
The Common/RTS planner's original-path leads, alternatives, mixed donors,
compiler settings and duplicate declarations were reviewed. The planner does
not approve a move; the ordinary current-map plan approves the cost donor.
No merge, split, row movement or name change is applied.

## Verified improvement

The queued GameLogic adoption for Rva001FF3DCFinish.cpp fails on its private
`m_gameMode` spelling. Replace that private class with the canonical
GameLogicObjectLookupView.h, reading its existing measured `m_110` field. Both
views read the same native +0x110 word, and retain the existing
isInMultiplayerGame call and TheGameLogic global type. No canonical header,
receiver extent, mode meaning, global or body control flow is changed.

`header_adopt_lane.py accept --class GameLogic <donor>` passes and retires
**one header-queue row** through its acceptance path. The 86-byte purchase-cost
row verifies before/after. This is a completed prerequisite with measurable
queue reduction, even though no new C++ bytes or complete merge is claimed.

## Acceptance and bindings

- Before build of seed, NameDescription, inverse-name query and purchase-cost
  donor: **14/14**. After build of the changed donor: **1/1**; frozen-file
  check passes and class adoption acceptance passes.
- Supported allowed_symbols object/definition and census COMDAT readers compare
  preserved before objects and current verified objects. Every non-debug,
  non-directive section byte, flag, normalized relocation and COMDAT policy is
  identical, as are external code definitions, undefined references and the
  directive-alias union. Counts (seed/name/inverse/cost): 42/1/2/1 definitions
  and 46/1/2/1 sections. No provider candidate, selected body or consumer
  binding changes.
- Paired allowed_symbols.scan preserves **27 reference facts**, zero added or
  removed; data_check.object_facts preserves all code/data facts. The changed
  donor's direct allowed_symbols scan has three owner references and no wrong
  binding. Strict current receipt preparation, new-variant and converged data
  checks pass. No identity/data baseline or hatch key changes or disappears.

Scratch evidence: build/codex-science-cost-{sources.txt,before-files/,
before-objects/,object-proof.json,reference-delta.json,data-delta.json,
adopt-strict.txt,before-dryrun.txt,planner.txt}. No match-cache compilation by
hand, index update, link cycle or smoke/nightly runner.

## Remaining composition blockers

The current full baseline dry-run does **not** reproduce the older 13-row
accepted composition: after its greedy trials it refuses the final accepted
set with allocator/vector redefinition. The tool leaves `accepted: []` and
writes nothing. Retain this newer result rather than claiming the historical
13-row result is still current. The cost donor also lacks the +0x28/+0x2C
cost fields in the shared ScienceInfo view; this repair intentionally stops
at the independently accepted GameLogic prerequisite. Those two fields,
STL declaration/flag reconciliation, parser/Overridable methods, template
byte failures, mixed donors and identity debt require separate work.

No full dry-run unblock or subsequent Luna landing is demonstrated. Do not
repeat the unchanged final allocator/vector failure without a new explanation.

## Complete batch audit and measurements

Audited pending 36240d337d (RepairDock), de88735255 and 7c09838b8e (Keyboard),
plus this staged adoption. No source paths move, rename or disappear. The
canonical GameLogic header is unchanged. Combined searches cover active tools,
hooks, workflows, source includes, build inputs, queues and registries: the
new Keyboard/RepairDock headers have only their intended consumers, and this
existing canonical-header include needs no path repointing. Original EA paths
and all surviving debt owners remain. Incoming remote changes in the two-dot
diff are distinguished from local outgoing commits using history/merge-base.
Read the eventual pre-push audit's freshness/selected-provider report.

File reduction **0**; header-queue debt retired **1**; identity/data debt retired
**0**; new C++ bytes **0**. No census linked/ownership gain is claimed. Keep the
changed donor, handoff and queue file claims until publication is confirmed;
other unused Science file claims can be released immediately.
