# RepairDockUpdate transfer prerequisite — 2026-10-26 codex

Allocated family A, shard 0/2 destination:
`Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RepairDockUpdate.cpp`.
The current runner queue authorizes investigation; no merge or split is applied.
Inherited commits through b7655fb3a1 were confirmed on origin/master before new
work, and their fourteen file scopes were released. The earlier constructor,
module-data and mixed-donor evidence is preserved in
[the Luna handoff](consolidation-repairdock-provider-prerequisite-20261026.md).

## Bounded repair and demonstrated acceptance

The DockUpdate-parent planner and then the broader Update-prefix planner were
read: original paths, alternatives, conflicting receiver views, data/hatch
registers, mixed routing and compiler differences remain prerequisites, not
approval. `tu_skeleton.py --plan` rebuilt current routing in memory: nine
approved rows, six direct donors and two mixed files. No TU map is committed.
Baseline dry-run accepts parse, pool and module-data constructor: four rows,
137 bytes. Behavior construction fails C2511, transfer fails C2061 for
Snapshot in BfmeXfer.h, and action fails C2039 for buildFieldParse.

RepairDockUpdateView.h shares the existing transfer receiver with the pool-key
consumer, keeping the measured +0x88 ObjectID and +0x8C float and all used
method signatures. Operand forward declarations precede BfmeXfer.h inside the
same include guard. No constructor, action interface, vtable slot identity,
name, pin or compiler option is recovered or changed. Neither consumer creates
a RepairDockUpdate object. Full object equality below proves no vtable is added.

Ordinary post-repair `tu_skeleton.py --merge <TU> --dry-run` accepts all four
compatible donors, **five rows / 203 bytes**, including the 66-byte transfer.
This demonstrates one additional accepted donor/body for Luna; it is not a
confirmed downstream merge or new recovered code. Constructor C2511 and action
C2039 remain. Both mixed files stay behind. A future merge still needs its
printed data/hatch transfers and the normal composition binding comparison.

## Verification and binding evidence

- Baseline `./build.sh` over all five parse, module-data ctor, action, transfer
  and pool sources passes 6/6 rows, one data row, one string and one float.
  Edited transfer/pool sources pass 3/3 rows after the repair.
- `find_declared_unmatched.py` passes before/after; `class_gate.py` passes for
  both consumers and the new header. No registered class is copied.
- Supported allowed_symbols.Obj, _object_defs and census COMDAT APIs show all
  non-debug section bytes, normalized relocations, section flags, COMDAT
  policies, external code/data definitions, undefined references and aliases
  equal across all five baseline objects. The two edited units keep one code
  definition each (two and eight non-debug sections). Thus provider candidates,
  selection order/policies and all consumer references are unchanged.
- Paired allowed_symbols.scan results retain every one of 11 reference facts,
  without an addition/removal. data_check.object_facts definitions/bindings
  also agree. Existing pool/data debt is preserved in its registers.
- `link_check.py --prepare-current <transfer> <pool>` passes 3/3 rows and
  strict reusable receipts. The first attempt overlapped the read-only merge
  trial's temporary source creation and correctly refused moved preparation
  inputs; after the trial ended the sequential preparation passed. Complete
  object/reference/data equality is repeated on those strict objects.
- `link_check.py --new-variants --paths-from
  build/codex-repairdock-sources.txt` exits zero for all five sources.
  `data_check.py --converged <transfer> <pool>` passes two sources/ten addresses,
  zero second names and zero unjudged rows. No census, nightly, smoke, link
  cycle or ownership recorder is run. No link/ownership increase is claimed.

Scratch receipts use build/codex-repairdock-{before,after}.txt,
*-build-{before,after}.txt, *-before-objects/, *-object-proof.json,
*-reference-delta.json, *-data-delta.json, *-strict.txt and *-link-variants.txt.
The current Update planner is regenerated after the edits and checked again.

## Publication audit and claims

The outgoing range plus staged repair contains no existing source path moves,
renames or deletions. Combined searches of active tools, hooks, workflows,
source includes, build inputs, source registries and header/MS-header/debt/data
registers find exactly the two intended new-header consumers. Historical EA
paths, ledger sources, data owners and protected keys stay unchanged. Recent
upstream tool edits visible in origin/master..HEAD are distinguished from this
seat's outgoing changes by the common ancestor. Audit receipt:
build/codex-repairdock-path-audit.txt. The pre-push batch audit still runs once
at actual publication; carry inconclusive freshness to the next census.

Keep the destination, five inspected donor, shared-header, obstacle-register
and this handoff file claims until publication is confirmed. The unused
RepairDockUpdateModuleDataView.h claim is released; that header is not created.
Then release file scopes and run claims.py release --landed.

Source-file reduction: zero. Registered identity/data debt retired: zero.
Recovered/authored C++ bytes: zero. One scoped header is added.
