# DefaultProductionExitUpdate Xfer prerequisite — 2026-10-26 codex

Allocated family A shard 0/2 target:
`Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/DefaultProductionExitUpdate.cpp`.
The scoped ProductionExitUpdate planner's original-path leads, alternatives,
compiler flags, mixed donor and declaration blockers were reviewed. Current
in-memory routing approves seven rows across four donor files, with one mixed
source. Planner hints are not provenance or merge approval. No move is applied.

## Verified prerequisite

The transfer/door donor carried a private Xfer interface whose Coord3D operand
prevented canonical-header adoption. It now includes the existing BfmeXfer.h
and Coord3DBase.h, and passes the same 12-byte rally-point triple through the
canonical Coord3DBase operand. No virtual slot, receiver layout, callee, global,
compiler setting or shared header changes. The explicit view cast avoids an
additional out-of-line asBase COMDAT found during the first local trial.

`header_adopt_lane.py accept --class Xfer <donor>` passes and retires exactly
**one header-queue row** through the supported acceptance path. Three existing
rows remain exact: xfer (0x0048805B, 62 bytes), exitObjectViaDoor (0x00488099,
463 bytes), and its EH handler (0x0078C2E9, 10 bytes).

## Acceptance and identity

- Before/after `./build.sh <donor>`: **3/3**; string, float and import checks
  pass. Frozen-file checks pass for both donor and seed; the seed's four
  pre-existing marked definitions are unchanged. Class gate passes.
- `link_check.py --prepare-current --paths-from build/codex-default-exit-sources.txt`:
  one strict current receipt. New-variant scan passes with no findings.
- Supported allowed_symbols object readers and census COMDAT policy readers
  compare preserved baseline and strict current objects: **37 external code
  definitions and 42 non-debug sections on each side**, identical code facts,
  section bytes/flags/relocations/COMDAT policies, external data, undefined
  references and directive aliases. Thus this repair changes no provider
  candidate, selected body or consumer binding. It does not prove unrelated
  pre-existing bindings correct.
- Paired allowed_symbols.scan preserves all **17** code-reference findings,
  zero added/removed; data_check.object_facts preserves every code/data fact.
  Converged data check passes: 10 addresses, no second names or unjudged rows.
  `eh_verify.py <donor>`: **1 EXACT**, no missing objects or EH debt.
- `check_csv.py` passes. No functions, TU-map, data/identity debt, hatch or pin
  entry changes. No debt key disappears with a source path.

Scratch evidence is under build/codex-default-exit-* (source/object snapshots,
object-proof.json, reference-delta.json, data-delta.json, strict-current.txt,
header-accept-final.txt, before/after-trial.txt and planner-final.txt). Proofs
use supported readers; no hand compilation into the match cache, link cycle,
smoke test, nightly runner or index/census update was used.

## Composition and next work

Before and after, the normal `tu_skeleton.py --merge <TU> --dry-run` exits 2
with **accepted: []**. The seed still lacks pool member rva000487F82 and ctor
field m_secondary20. The transfer donor still meets the seed's incompatible
Coord3D and legacy Xfer definitions after directive lifting. Reconcile those
receiver/include contracts separately, preserving their ABI and provider
facts; the mixed deleting-destructor donor remains untouched. No complete
composition unblock or later Luna landing is demonstrated by header adoption.
Do not rerun the unchanged failures without new structural evidence.

## Complete batch audit

The outgoing local range begins at 44c8f8f4cb plus this staged prerequisite.
At audit time origin/master had advanced independently to e2e042148e; the common
ancestor was 44c8f8f4cb. There are **no local source moves, renames, deletions or
new headers**. Combined path searches across active tools, hooks, workflows,
source includes, build inputs and registries find only the seed's two existing
provenance mentions of this donor; no path consumer needs repointing. Both
included canonical headers already exist and are unchanged. Original EA paths
and surviving debt owners are preserved. Read the pre-push batch audit's
selected-provider and freshness report when this commit is published.

File reduction **0**; header debt retired **1**; identity/data debt retired
**0**; recovered C++ bytes **0**; no census linking or ownership gain claimed.
Keep donor, seed, header-queue, obstacle-register and this handoff's file claims
until publication is confirmed; release them afterward. If the publisher's
shared slot defers the batch, the runner publishes it and the next seat must
release those claims after confirming landing.
