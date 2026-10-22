# canMake: allocation context and conflict observations

Continue only `AIBuildableWallSegment::canMake`, `0x00596e15`, retail 218 B
through RET4, next body at `0x00596eef`. The existing 216-byte bank remains
best: diagnostic fitness 0.945980, instruction difference count 6, relocation-
masked SHA256 `21a3f8f3243cb7b71022d189657993f03de236d0f2c6ca0516628a7e138820c9`.
It was independently recompiled from its portable home-relative includes;
its EH data verifies EXACT. It is not a byte-exact match or new C++ coverage.

Read the preceding `canmake-early-cleanup-20261022/readme.md` for the bank and
both regional alternatives. Remaining bank differences are unchanged: EBX
rather than ESI carries the failure return, status 7 precedes status 0, and
the omitted two-byte default jump shifts success cleanup and the epilogue.
Keep the separate-success 223-byte ESI control too; it still has five extra
bytes of conditional value arithmetic and the wrong cleanup placement.

## New observations

The preceding allocator tracer filtered conflict neighbours by name. This
session's `color-trace.py.txt` removes that filter and observes all neighbours,
including anonymous zero-related records, without writing compiler state.
`allocator-observations.json` retains the pertinent raw records and every
neighbour index at their allocation. Anonymous symbol identities and raw word
meanings remain partly inferred; the final objects establish the register
correlation, not a complete interpretation of c2's internal structures.

| Body / record | Round | Raw words 3 / 9 | Allowed at pop | Chosen register | Neighbour indices at colouring |
| --- | ---: | --- | --- | --- | --- |
| Bank receiver, index 3 | 1 | 37 / 6 | 4, 7, 8 | 7 (ESI) | 1, 2, 4, 5, 7, 8, 9 |
| Bank fixed-zero-related, index 1 | 1 | 35 / 11 | 4 | 4 (EBX) | 2, 4, 5, 7, 8, 9 |
| Bank return-related, index 10 | 2 | 8 / 6 | 4, 7, 8 | 4 (EBX) | none |
| ESI control return-related, index 11 | 1 | 36 / 8 | 4, 7, 8 | 7 (ESI) | 2 |
| ESI control fixed-zero-related, index 1 | 1 | 36 / 11 | 4 | 4 (EBX) | 2, 4, 5, 7, 9, 10 |
| Explicit shared-code local `selected`, index 5 | 2 | 6 / 5 | 1, 2, 3, 4, 7, 8 | 4 (EBX) | none |

Thus the observed return records do not conflict with the fixed-zero record.
The ESI control's record is coloured before that zero record; the bank's is
coloured in round 2. Simply naming a common failure variable does not move it
into round 1. This narrows the allocation/coalescing investigation; it does
not prove that a particular weight alone determines the result.

All three traced objects reproduce their ordinary masked hashes and verify
EH EXACT. The shared-code control is 216 B, hash
`f6340e4b297838550a3690c4d3a7d3821ab8fa8930f541695b92e3aae3f4c17f`.
The ESI control is 223 B, hash
`cee9ad3381596a8b9ccaf90853784474f08e8fba700151736cb48a163c332648`.

## Completed experiments: do not repeat unchanged

There were 4,434 final source trials, zero compiler errors, and zero exact
candidates. The inline family has 144 unresolved helper-call variants because
MSVC declines some requested inlines; these are diagnostics, not admissible
matches. All other families have no unresolved main-body relocations. An
initial inline-generator enum conversion error was corrected before its final
324-trial run. `receipt.json` records extents, hashes and totals.

| Family | Trials | New interaction and result |
| --- | ---: | --- |
| `inline` | 324 | Both new 216 B cleanup shapes and the old ESI control, six extraction boundaries, scalar/enum/pair helper returns, pointer/reference quote inputs, accessors and inline attributes. No improvement. |
| `late-weight` | 1,470 | Selected return values with 1..32 redundant, path-proved uses, seven use forms, individual/all failure sites and local/function scope. New 216 B shapes stay unchanged. The third base is a status-7-first selector control, not the byte-identical old 223 B control. |
| `loop-weight` | 960 | Twelve immediate-return loop forms, nesting 1..4, individual/all failures and repeated predicates, two status forms. No improvement. These loops are evaluated only where their entry predicate is already true. |
| `temp-context` | 648 | Both 216 B shapes with POD/non-POD/empty-destructor Coord3D, expression/named/reference position temporaries, local scopes, three failure types, actual noinline quote-destructor visibility and position accessors. Eight emitted bodies; none improves the bank. |
| `read-priority` | 384 | Both cleanup shapes, actual ZH Money headers, and independently qualified failure/status/funds/cost reads, following the new per-read qualification recipe. Twenty-one bodies; none has the required early ESI return. Volatile variants are diagnostic source experiments, with no asserted volatile target contract. |
| `shared-code` | 648 | Explicit failure-code PHI through common goto/return, two label positions, three declaration positions, initializers and assignment forms, two status forms, three funds/success forms and signed/unsigned code. Seven bodies, all worse. Naming the code does not produce the needed first-round allocation. |

The WB twin was read again. Its position return temporary has a nested EH
state around `quoteWall`; its empty destructor emits no call. This motivated
the new temporary-lifetime matrix, rather than repeating the old 204 B context
alone. Its inline Money/cost/setter argument homes remain evidence for source
shape, not proof of a full target Player layout. The reconstructed real-header
prefix is byte-identical to the previously inspected prefix; Money size 12 and
the established target member offset are checked. No missing include directory
was substituted. The donor pointer is recorded in the receipt.

Reproduce a family from the repository root:

```sh
python3 reverse/attempt_support/canmake-priority-context-20261022/replay.py.txt --list
python3 reverse/attempt_support/canmake-priority-context-20261022/replay.py.txt temp-context
```

Each compiles eight private scratch objects at a time through the project's
compiler command. Nothing uses `build.compile_source` or the shared production
object cache. The shared scorer freezes its original 204 B input at commit
`69526d2ae11afc4582e85371b0ff60dbd293e616`; no deleted scratch input is required.
The tracer accepts an input `.cpp` and private output `.obj`. Obtain the bank
and ESI inputs with the preceding handoff's `funds_after` and `esi` replay modes.

## Checks and continuation

Pull/rebase, `check_csv.py` (98,068 functions, 15,856 symbols, 2,128 data rows),
published link-index fetch and the home's declared-definition check passed.
`./build.sh AIBuildableWallSegment.cpp` passes 2/2 existing bodies plus source,
string, float and import checks. No production C++, row, pin, header, gate or
class contract changed. No maintainer-only runner was started.

BFME1 remains at verified pointer `42bba2ddbd5cb895d99293583891d3b7315fa49e`.
Freshness was due, but the live foreign update lock belongs to `claudec2`;
the runner instructs this seat to skip the concurrent update. No success
timestamp was written. The assigned lane overrides broad sweeps and queues.

The claim is released after recording this attempt. Reclaim the same target
next session. No missing callee has been established as a prerequisite.
An untested next investigation is to observe construction/splitting of the
return record before first colouring, comparing the 223 B ESI selector against
the bank. Identify the pass that removes or preserves its value dependence;
do not repeat the already-folded redundant-use, loop, scope or shared-variable
families above. Preserve the best bank and regional winners while doing so.
