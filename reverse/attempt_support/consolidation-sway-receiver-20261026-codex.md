# Sway receiver prerequisite (2026-10-26, codex)

Allocated family-A shard 0/2 target:
`Code/GameEngine/Source/GameClient/Drawable/Update/SwayClientUpdate.cpp`.
This continues the include-order repair in
`consolidation-sway-prefix-20261025-codex.md`; it does not repeat that repair.

## Blocker and repair

The ordinary baseline `tu_skeleton.py --merge TU --dry-run` accepted no donors.
The pool-key donor failed C2039 because the seed lacked getModuleNameKey. The
transfer donor failed because xfer was absent, ObjectModule was not a seed
base, and its private member spellings differed. The constructor independently
failed C2511 and remains outside this repair.

The seed, pool-key and transfer now include SwayClientUpdateView.h. It retains
the seed's receiver hierarchy and measured fields (+0x0C through +0x28), and
declares the existing pool-key and transfer methods. The transfer uses those
same fields and explicitly calls its existing unadjusted ObjectModule::xfer
entry through a view cast. This preserves that symbol without asserting an
ObjectModule base in the drawable hierarchy. The header is a partial receiver
view, not recovery of the full retail virtual-slot order; no constructor or
destructor is defined through it. No flags, row names, source paths or ledger
ownership change.

## Evidence and verification

The scoped planner was run under the allocated target's parent directory with
output `build/consolidation/codex-sway`. Its packets preserve the verified
retail updateSway path operand at 0x004C916C, the same-path ZH hints, and the
pool-key's unresolved EH placement. The stale-map warning is not approval:
the ordinary TU tool rebuilds routing in memory. No map was committed. The
mixed ConstIntGetters4.cpp donor and opaque constructor were not edited.

- Before and after, `./build.sh` on the seed, pool-key and transfer passes all
  **6 matched rows / 1,218 retail bytes**, including the pool-key EH handler.
  String (2), float (4), import and frozen-file checks pass.
- `class_gate.py` passes for all three sources and the new header.
- Paired object inspection uses the upstream allowed_symbols COFF reader,
  link_census COMDAT policies and link_check alias reader. All three objects
  preserve every non-debug section's bytes, flags, COMDAT policy and normalized
  relocation, all external definitions and undefined references, external data,
  and aliases. External code definition counts remain 17 / 1 / 1; non-debug
  section counts remain 22 / 8 / 2. No provider body or binding changed.
- Paired `allowed_symbols.Identity` / `scan` results preserve all **22**
  reference facts, with no additions or removals. Paired `data_check.object_facts`
  results are identical. Thus unchanged external consumers see the same provider
  symbols, bodies and policies; there is no changed binding to excuse.
- Supported `link_check.py --prepare-current` passes for all three explicit
  providers: normal gates reuse three strict-current receipts. The following
  `link_check.py --new-variants --paths-from build/codex-sway-sources.txt`
  passes without a new variant. The fetched diagnostic index is `763dc8759f`
  (2026-10-26 00:54); it is not a new census or a closed-strict result.
- `data_check.py --converged` passes for 3 sources / 10 addresses, with no
  second names or unjudged rows. Object section equality was checked again
  after supported strict preparation completed.
- Scratch evidence: `build/codex-sway-{object-proof,reference-delta,data-delta}.json`,
  `build/codex-sway-{build-before,build-after}-20261026.txt`, and
  `build/codex-sway-before-20261026.txt`.

The pool-key's pre-existing wrong-name findings remain: the current names at
0x00A04328 and 0x00A0432C differ from the historical data ledger/baseline names.
The register key and owners remain untouched. There are no scoped canonical
class, header-queue, ms-header-queue or identity-baseline keys to transfer.
No identity or data debt is claimed retired.

## Composition, publication and handoff

The post-repair ordinary merge dry run now accepts the seed, pool-key and
transfer: **6 rows / 1,218 bytes across 3 current sources**, where the baseline
accepted none. That is a demonstrated unblock, not a confirmed Luna landing.
It still rejects Rva004C908BCtor.cpp with C2511; the mixed ConstIntGetters4.cpp
row stays behind. It prints transfers of one data-baseline key and two
data-ledger entries for a future merge. Preserve those debts through the
tool's printed transfer trailer; do not count them retired. Local receipt:
`build/codex-sway-after-20261026.txt`.

No merge is applied in this prerequisite commit. Luna must verify selected
providers and consumers again after actual
composition; identical prerequisite objects do not certify a future merged TU.

The outgoing audit covers inherited unpublished `92faf73b14` and this repair
against merge-base `73ffc391c4`. Neither changes any existing source path.
Combined path/basename searches cover active tools, hooks, workflows, source
includes, build.sh, source registries, canonical/header queues and doxygen.
Only the three intended new header includes and existing doxygen seed input
need active resolution; the builds and dry run verify them. Original EA #line
and BFME 1 donor path evidence remain intact. No protected register or TU map
is staged. The planner was regenerated after the source change and rechecked
its inputs before writing; no concurrent composition trial ran during it.

Other allocated investigations: AssaultTransportAIUpdate and
SupplyWarehouseDockUpdate plans were read; prior Xfer/GameLogic/private-view
and legacy-layout blockers remain and were not retried. GameMemory's plan
has mixed memory_pool.cpp/block-slot rows plus a vendored ZLib refusal and a
Libraries allocator donor; no cross-family donor was claimed or changed.

Keep the four source/header file claims and this handoff claim until confirmed
publication. The inherited docs/linking_obstacles.md and
consolidation-sol-prerequisites-20261026-codex.md claims also await that push.

Recovered C++ bytes: 0. Source files removed: 0. Identity debt retired: 0.
Matched coverage is preserved; no linked-byte or ownership improvement is
claimed from a preview or from an old census.
