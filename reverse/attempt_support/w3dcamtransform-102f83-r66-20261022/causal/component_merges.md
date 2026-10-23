# Camera translation coalescing proof

`proof.json` preserves the relevant before/after IR and actual descriptor writes,
ordinary compiler commands, input hashes and whole-body byte/relocation checks.
The read-only traced bank is 4254 bytes; the existing both_xy candidate is 4300
bytes. Neither trace changes compiler decisions.

The responsible helper is `@SubsumePseudos@4`, native C2 RVA 0x97082 (SP1 PDB
RVA 0x87AE9), called at 0x96DCB from `@InitialSplitPoints@16`. Identity was
established by corresponding native/SP1 control flow and caller targets.
`SubsumeGlobregs` removes integer pointer copies here, not the SSE chains.

For the bank, four target translation copies at relative lines 51 and 58
(X and Y each) select a class-3 temporary source and a class-2 target global
destination. The helper rewrites ADDSS source descriptors at 0x970BB and
ADDSS/load destination descriptors at 0x96FDF, then removes the final copy.
The result is the target field's global candidate owning the entire
position-load + ADDSS chain. The signed-cost ledger in `../component_costs/`
proves that each chain contributes +6 to the field: two chains are +12.

In the already-existing both_xy source, real helper arguments x/y are used for
both source and target translations. InitialSplitPoints sees global value
candidates for those shared arguments. Its earlier global-to-temporary copy
is subsumed in the other direction: the shared value global owns the ADDSS.
The later copy to the target field remains. Its source is now descriptor class
2, so it cannot pass the class-3 requirement at 0x96E77. No target-translation
consider/accept event occurs, while the remaining target field copy appears
in the after snapshot. This is copy processing order and candidate ownership,
not a new alias/type rejection. Target XY costs become -6, proven separately
in `../decode/paired_live/`.

This explains a useful source mechanism but not the original retail source:
both_xy shares position loads while retail reloads them for each translation.
A genuine by-value result aggregate or copy boundary is the next supported
way to give arithmetic a separate candidate while keeping separate input
loads; arbitrary dummy uses or compiler changes are not proposed.

## Separate returned-vector boundary

The `value_reference` trace (4286-byte complete body equal to its ordinary
compile, including relocations) shows that the separate translated() calls
make anonymous 12-byte aggregates own the load/ADDSS candidates.
Their component symbols originate in aggregate IDs 1141 and 1147;
the final result.X/Y-to-sourcePos/targetPos copies remain separate. This
explains both the desirable negative field costs and the delayed stores:
each vector value is calculated before its component copies. Optimized symbol
names are absent, so this trace alone does not distinguish the copied parameter
object from the returned result object.

One next discriminator is consuming only one returned component per statement:
`sourcePos.X=translated(sourcePos,v->pos).X;` then the analogous source Y,
target X, target Y statements. This retains the same useful translation
operation, requests fresh position loads, and avoids assigning an entire vector
at each step. It differs from the already-tested per-axis whole-vector returns.
The key question is whether the return aggregate boundary survives extraction
of one component. If it does not, a plain scalar helper has no established
reason to provide the needed separate arithmetic owner. Parent owns this trial.

Reproduce traces with `python build/camera-causal-20261021/trace_component_merges.py bank both_xy value_reference`,
then `python build/camera-causal-20261021/component_merges/summarize.py`.
The larger raw traces and the scoped native disassembly remain in this directory.
