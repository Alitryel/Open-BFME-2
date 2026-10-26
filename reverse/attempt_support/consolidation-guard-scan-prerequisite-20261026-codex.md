# AITNGuard scan receiver prerequisite — 2026-10-26 codex

Allocated family A shard 0/2 destination:
`Code/GameEngine/Source/GameLogic/AI/AITNGuard.cpp`.
The current runner queue and check-tu authorize this target. The scoped AI
planner's original-path alternatives, stale-map hints, incomplete EH routing,
compiler settings, duplicate views and protected registers were reviewed.
Same-spelling Zero Hour/path hits remain leads, not target identity proof.
Current tu_skeleton routing rebuilds the map in memory: 33 approved rows,
ten donor files, five mixed sources, none refused. No map is committed.

## Repair and demonstrated unblock

The seed's Object view exposes ID/body/AI/team at +0x74/+0x254/+0x258/+0x304;
the scan donor exposes position at +0x38. Composition selected the seed view
and refused TunnelNetworkScan because Object has no m_pos. Share the existing
accessed fields and enum/method declarations in AITNGuardObjectView.h, replacing
only the seed's corresponding padding with the measured Coord3D triple.
Both direct consumers include that same view. Receiver extent, later offsets,
virtual contracts, globals, callees and compiler flags stay the same. This is
an accessed prefix, not a complete Object layout recovery. Shared global
GameLogic and Coord3D declarations come from their existing headers unchanged.

Before, ordinary `tu_skeleton.py --merge <TU> --dry-run` exits 2 and accepts
nothing. After, it exits 0 and accepts **AITNGuard.cpp and AITNGuardScan.cpp**
under /DNDEBUG /MD /EHsc: **6 existing matched rows / 595 retail bytes**.
Those comprise the seed's 28-byte ctor and 395-byte target search plus the
scan's 146-byte body, 10-byte handler and two 8-byte cleanup rows. This is a
demonstrated prerequisite unblock; no merge or subsequent Luna landing is
claimed. Leave the compatible donor for Luna.

## Acceptance and provider/consumer evidence

- Before and after `./build.sh <seed> <scan>`: **6/6**, plus the seed's one
  matched data row; string, float and import checks pass. Frozen-file and
  class gates pass for both consumers; no private canonical class is added.
- `link_check.py --prepare-current --paths-from build/codex-guard-scan-sources.txt`:
  **2 strict current receipts**. New-variant scan passes, no findings.
- Supported allowed_symbols object readers/census COMDAT policy readers retain
  **24/13 external code definitions** and **27/21 non-debug sections** for
  seed/scan. Undefined references, aliases, external data and code facts are
  identical. Scan section bytes/flags/relocations/policies are identical;
  seed differences are solely COFF section numbering. Normalizing sections by
  external identity/content yields no added or removed sections or changed
  data. Provider candidates, selected bodies and consumer bindings are kept.
- `data_check.object_facts` is identical before/after; converged data check:
  2 sources, 10 addresses, no second names or unjudged rows. No identity/data
  debt is retired or transferred and no source disappears.
- `eh_verify.py <seed> <scan>`: **1 EXACT**, no missing objects or baseline
  entries. The two ledger cleanup labels are already stale in the baseline
  object and renumber again after the shared include. The raw identity scan
  sees 21 versus 20 references, dropping one stale-label observation; this is
  not identity improvement. Using supported build.located_funclet and the
  parent's exact EH graph to resolve only those labels in memory yields
  **22 reference facts before and after**, zero added or removed. The ledger,
  checker and debt registers remain unchanged. The whole normalized EH/code
  sections and relocation destinations also agree.

Scratch receipts: build/codex-guard-scan-{before/after-build.txt,
strict-current.txt,variants.txt,before/after-trial.txt,before-files/,
before-objects/,object-proof.json,section-delta.json,reference-delta.json,
reference-eh-located-delta.json,data-delta.json,planner-final.txt}.
No hand compilation, link cycle, smoke/nightly run or census update.

## Remaining prerequisites

The same current dry-run still rejects eight donors. Xfer lacks StateMachine's
xfer member; state/inner/aggressor/machine constructors need StateMachine
visible before AIUpdateInterface; HasAttackedMeCondition needs consistent
getBodyModule/getClearableLastAttacker views; ReturnStateOnEnter needs TAiData
before AI. Their layouts, emitted tables and any later byte failures still
need dedicated evidence. The five mixed files and protected/hatch/data rows
stay intact. This commit does not add placeholder methods or guess a virtual
contract. Do not repeat these unchanged failures without a new hypothesis.

## Complete pending-batch compatibility audit

Audit covers local 44c8f8f4cb..e99d78dd3d plus this staged repair. Independent
incoming origin commits are excluded using merge-base/history. No source path
moves, renames or disappears. One scoped header is added, with exactly its two
intended direct consumers, verified by combined searches of Code, tools,
hooks and workflows. Existing build discovery and registries need no path
repoint; canonical includes resolve at their existing locations. No active
consumer points at a deleted source. Original EA strings and prior evidence
are preserved. All existing code/data identity, header/MS-header, hatch and
pin keys remain accounted for; only e99d78dd3d's separately accepted header
queue row is retired in this batch. Read the eventual pre-push batch audit's
selected-provider and freshness findings.

Source-file reduction **0**; one scoped header added; identity/data/header
queue debt retired by this repair **0**; recovered C++ bytes **0**; no new
census LINKED/LINKING or ownership gain claimed.

The prior prerequisite commit e99d78dd3d is pending the runner batch threshold.
Keep all nine batch scope claims until confirmed publication: the default-exit
seed/donor, reverse/header_queue.tsv, docs/linking_obstacles.md and its handoff;
plus the guard seed/scan/header and this handoff. The next seat should confirm
landing, release those file claims, and settle RVAs with claims.py release
--landed. No additional body claim is held.

## Other allocated targets assessed this session

AssaultTransport and BridgeTower retain broad legacy layout/frozen-source
prerequisites; no speculative edit or claim. RepairDock, SpecialPowerCreate,
Keyboard and HeaderTemplate have existing verified repairs or structural
handoffs, so their unchanged failures were not repeated. RankInfo has different
constructor/destructor string/vector lifetime declarations. FireSpread remains
a legacy-layout/snapshot interface task. PlayerList's private transfer uses a
different virtual-slot contract, so its queued canonical adoption is not a
forward-declaration-only fix. These read-only reviews created no source edits
or claims. TheMessageStream naming decision (issue #116) is left to maintainers.
