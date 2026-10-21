# Camera first-SSE cost attribution

Read-only compiler trace: no decisions or values were changed. The traced target body and relocation tuples equal the ordinary bank compile over its complete 4254-byte extent.

Each cost write was observed before execution. Four write sites account for every final long-candidate cost exactly: source benefit 0x82692, definition benefit 0x84C3E, split reload charge 0x8281C, split store charge 0x8CB73. First SSE Spillcosts is call #2; call #1 is the earlier x87 pass.

| Component | Glob | References | Cost |
|---|---:|---:|---:|
| sourcePos.X | 161 | 13 | -1 |
| sourcePos.Y | 165 | 13 | -1 |
| sourcePos.Z | 169 | 17 | +11 |
| targetPos.X | 170 | 14 | +10 |
| targetPos.Y | 172 | 14 | +10 |
| targetPos.Z | 174 | 6 | -7 |

## Target X and Y ledger

The components have equal arithmetic. Relative line numbers are the compiler function-relative source lines, not physical file lines.

| Source operation | Net cost per component |
|---|---:|
| Initial target XY translation (L51) | +6 |
| Split reload after findObjectByID (L52) | -3 |
| Live target XY translation (L58) | +6 |
| Split reload at realZoom join (L76) | -3 |
| realZoom source X pitch division/add (L79) | +2 |
| Else source X pitch division/add (L93) | +2 |
| Live pitch XY distance (L85) | +1 |
| Split reload after live-pitch tan call (L89) | -3 |
| Position-hold target translation (L99) | -1 |
| Final source/target copies to input context (L103) | +3 |

## What causes the large positive XY cost

At each initial/live translation, the candidate contains a position-load temporary as well as the target component: temporary definition +3, temporary ADDSS use +3, target ADDSS definition +3, pseudo-store 619 -3 = +6. The temporary definition tuple does not mention targetPos, but its operand is already assigned to that component's global register candidate. Thus the +12 from two translations is direct evidence of lifetime coalescing before Spillcosts, not merely counting target field references.

The two pitch arms each add +2 from SUBSS/ADDSS reads. The live-distance read adds +1, position-hold read/definition/store contributes -1, the final view copy adds +3, and three split reloads deduct 9. Total: 12 + 4 + 1 - 1 + 3 - 9 = 10.

Target Z starts with a foldable definition followed by a store (1 - 3 = -2), pays two reloads (-6), gains net -1 from vertical pitch and -1 from hold translation, then +3 from the final copy: -7. Source Z retains +11 because its ground translation and zoom scaling each contribute +6 through merged arithmetic temporaries.

CmdSubCost returns 1 for observed camera scalar uses/definitions; LoadCost returns 3. Pseudo reload 618 and pseudo store 619 each cost 3. The cost formula is consistent with size optimization and the observed EBP-availability flag of 0. The separate ref-count investigation confirms all block multipliers are 1.

## Next diagnostic implication

A legitimate explanation must alter which temporaries join a camera component, or where a real call/alias boundary splits that lifetime, while preserving retail operations. Changing branch weights is unsupported here. Root owns forced-cost sufficiency probes and source trials; this artifact proposes no artificial loads, dummy uses, escaping callees or compiler patches. Single-direct and bank already have identical target XY cost +10 despite different source XY candidate partitions, so removing addXY alone does not resolve the target partition.

Reproduce with `python build/camera-causal-20261021/trace_component_costs.py`, then `python build/camera-causal-20261021/component_costs/summarize.py`. `ledger.json` contains every cost event grouped by source operation; `bank.trace.json` retains detailed decoded operands.
